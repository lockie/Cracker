//---------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <assert.h>
#include <dir.h>

#include <windows.h>
#include <dbghelp.h>
#include <psapi.h>

#include <SyncObjs.hpp>

#include "fLog.h"
#include "fModules.h"
#include "CrackerEngine.h"

#pragma comment(lib, "dbghelp.lib")

//---------------------------------------------------------------------------

TCrackerEngine* CrackerEngine = NULL;

#define BUFF_SIZE 1024
static char Buffer[BUFF_SIZE];
static char Buff[BUFF_SIZE];  // 4 GetExceptionText



//---------------------------------------------------------------------------

const char* __fastcall GetExceptionText(DWORD code);

//---------------------------------------------------------------------------
TCrackerEngine::TCrackerEngine() {
  assert(CrackerEngine==NULL);
  ExeName = new AnsiString(NULL);
  hFile = INVALID_HANDLE_VALUE;
  hMapping = NULL;
  lpView = NULL;
  moduleList = new TStringList();
  moduleList->Capacity = 32;
  _moduleList = new TStringList();  
  _moduleList->Capacity = 32;
  DebuggerThread = NULL;
  bFirstBP = false;

  CrackerEngine = this;
};

//---------------------------------------------------------------------------

TCrackerEngine::~TCrackerEngine() {
  delete DebuggerThread;
  CrackerEngine = NULL;
  for(long i=0; i<moduleList->Count; i++) delete ((void*)moduleList->Objects[i]);
  delete moduleList;
  for(long i=0; i<_moduleList->Count; i++) delete ((void*)_moduleList->Objects[i]);
  delete _moduleList;
  CloseHandle(hMapping);
  CloseHandle(hFile);
  delete ExeName;
};

//---------------------------------------------------------------------------

bool __fastcall TCrackerEngine::OpenEXEFile(const char* filename) {
  hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL,
    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if( hFile == INVALID_HANDLE_VALUE ) return false;

  hMapping = CreateFileMapping(hFile, NULL, /*SEC_IMAGE*/ PAGE_READONLY, 0, 0, NULL);
  if( hMapping == NULL ) {
    CloseHandle(hFile);
    hFile = INVALID_HANDLE_VALUE;
    return false;
  };
  lpView = (char*)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
  if( lpView == NULL ) {
    CloseHandle(hFile);
    hFile = INVALID_HANDLE_VALUE;
    CloseHandle(hMapping);
    hMapping = NULL;
    return false;
  };

  ExeName->sprintf("%s", filename);
  return true;
};
//---------------------------------------------------------------------------

bool __fastcall TCrackerEngine::Run(char* Parameters, const char* CurrDir) {
  if( DebuggerThread ) {
    Application->MessageBox("Process already running. Stop it first!", "Error", MB_ICONERROR);
    return false;
  };
  DebuggerThread = new TDebuggerThread(ExeName, Parameters, CurrDir);
  return true;
};
//---------------------------------------------------------------------------

void __fastcall TCrackerEngine::Stopped() {
  bFirstBP = false;
};
//---------------------------------------------------------------------------

DWORD __fastcall TCrackerEngine::OnDebugEvent(const DEBUG_EVENT* DebugEvent) {
  DWORD dwRet = DBG_CONTINUE;
  LOAD_DLL_DEBUG_INFO* info;
  register DWORD base;
  switch( DebugEvent->dwDebugEventCode ) {
    case CREATE_PROCESS_DEBUG_EVENT :
      if( !SymInitialize( GetProcessHandle() , NULL, false) )  RaiseLastOSError();
      // Load main module - *.exe
      info = new LOAD_DLL_DEBUG_INFO;
      info->hFile = DebugEvent->u.CreateProcessInfo.hFile;
      info->lpBaseOfDll = DebugEvent->u.CreateProcessInfo.lpBaseOfImage;
      info->dwDebugInfoFileOffset = DebugEvent->u.CreateProcessInfo.dwDebugInfoFileOffset;
      info->nDebugInfoSize = DebugEvent->u.CreateProcessInfo.nDebugInfoSize;
      info->lpImageName = DebugEvent->u.CreateProcessInfo.lpImageName;
      info->fUnicode = DebugEvent->u.CreateProcessInfo.fUnicode;
      _moduleList->AddObject(NULL, (TObject*)info);
      Trace("Process Started : %s. ID=%x, base=%p", ExeName->c_str() ,
        DebugEvent->dwProcessId, DebugEvent->u.CreateProcessInfo.lpBaseOfImage);
      break;
    case CREATE_THREAD_DEBUG_EVENT :
      Trace("Thread Start, ID=%x", DebugEvent->dwThreadId);
      break;
    case EXIT_PROCESS_DEBUG_EVENT :
      for(long i=0; i<_moduleList->Count; i++) delete ((void*)_moduleList->Objects[i]);
      _moduleList->Clear();
      for(long i=0; i<moduleList->Count; i++) delete ((void*)moduleList->Objects[i]);
      moduleList->Clear();
      Trace("Process %x exited with exitcode=%x",
        DebugEvent->dwProcessId, DebugEvent->u.ExitProcess.dwExitCode);
      break;
    case EXIT_THREAD_DEBUG_EVENT :
      Trace("Thread %x exited with exitcode=%x",
        DebugEvent->dwThreadId, DebugEvent->u.ExitThread.dwExitCode);
      break;
    case LOAD_DLL_DEBUG_EVENT :
      // TODO : По идее, надо ещё и отлавливать вызовы LoadLibrary/GetProcAddress
      info = new LOAD_DLL_DEBUG_INFO;
      memcpy(info, &DebugEvent->u.LoadDll, sizeof(LOAD_DLL_DEBUG_INFO));
      _moduleList->AddObject(NULL, (TObject*)info);
      // DLL ещё не загружена, она только готовится =)
      UpdateModuleList();
      break;
    case UNLOAD_DLL_DEBUG_EVENT :
      base = (DWORD)DebugEvent->u.UnloadDll.lpBaseOfDll;
      for(long i=0; i<moduleList->Count; i++) {
        if( ((IMAGEHLP_MODULE*)moduleList->Objects[i])->BaseOfImage == base ) {
          Trace("Module UnLoad: %s", moduleList->Strings[i]);
          moduleList->Delete(i);
          break;
        };
      };
      break;
    case OUTPUT_DEBUG_STRING_EVENT :
      Trace("ODS : \"%s\"", DebugEvent->u.DebugString.lpDebugStringData );  // TODO : Unicode !
      break;
    case EXCEPTION_DEBUG_EVENT :
      // "First-chance exception in kernel32.dll : ACESS_VIOLATION at 00412345"
      if( DebugEvent->u.Exception.ExceptionRecord.ExceptionCode == EXCEPTION_BREAKPOINT ) {
        if( !bFirstBP ) bFirstBP = true;   // TODO : Here is the 1st breakpoint ("Break on load")
          else dwRet = DBG_EXCEPTION_NOT_HANDLED;
        break;
      };
      base = SymGetModuleBase(GetProcessHandle(), (DWORD)DebugEvent->u.Exception.ExceptionRecord.ExceptionAddress);
      if( base==0 ) {
        strcpy(Buffer, "<Unknown module>");
       } else {
        GetModuleBaseName(GetProcessHandle(), (HANDLE)base, Buffer, BUFF_SIZE);
      };
      Trace("%s exception in %s : %s at %p", DebugEvent->u.Exception.dwFirstChance!=0 ? "First-chance" : "Second-chance",
        Buffer, GetExceptionText(DebugEvent->u.Exception.ExceptionRecord.ExceptionCode),
        DebugEvent->u.Exception.ExceptionRecord.ExceptionAddress);
      dwRet = DBG_EXCEPTION_NOT_HANDLED;
      break;
    case RIP_EVENT :
      Trace("System debugging error : \"%s\"", GetExceptionText(DebugEvent->u.RipInfo.dwError));
      break;
    default :
      Trace("Unknown event");
  };
   UpdateModuleList();  // TODO : Иногда не работает!
  return dwRet;
};
//---------------------------------------------------------------------------

bool __fastcall TCrackerEngine::Stop(void) {
  if( !DebuggerThread )  return false;
  delete DebuggerThread;
//  DebuggerThread = NULL;
  return true;
};
//---------------------------------------------------------------------------

HANDLE __fastcall TCrackerEngine::GetProcessHandle() {
  if( !DebuggerThread ) return NULL;
  return DebuggerThread->ProcessInfo->hProcess;
};
//---------------------------------------------------------------------------
void __fastcall TCrackerEngine::UpdateModuleList(void) {

  assert(this);

  if( !DebuggerThread || !DebuggerThread->bRunning ) return;
  LOAD_DLL_DEBUG_INFO* info;
  char Buffer[MAX_PATH];
  long N = _moduleList->Count;
  for( long i=0; i < N; i++ ) {
    info = (LOAD_DLL_DEBUG_INFO*)_moduleList->Objects[i];
    if( GetModuleFileNameEx( GetProcessHandle(), info->lpBaseOfDll, Buffer, MAX_PATH ) ) {
      // что-то есть...
     fnsplit(Buffer, NULL, NULL, Buff, NULL);
     if( !SymLoadModule( GetProcessHandle(), info->hFile, Buffer, Buff, (DWORD)info->lpBaseOfDll, 0) )  continue; // DLL ещё не готова
      _moduleList->Delete(i);    i--;  N--;
      IMAGEHLP_MODULE* mod = new IMAGEHLP_MODULE;
      mod->SizeOfStruct = sizeof(IMAGEHLP_MODULE);
      if( !SymGetModuleInfo(GetProcessHandle(), (DWORD)info->lpBaseOfDll, mod) ) RaiseLastOSError();
      moduleList->AddObject(Buffer, (TObject*)mod);
      Trace("Module load : %s", ExtractFileName(Buffer));
    };
  };
  if( Modules!=NULL && Modules->lbModules->Count != moduleList->Count )  Modules->UpdateList();
};


//---------------------------------------------------------------------------

const char* __fastcall GetExceptionText(DWORD code) {
  switch ( code ) {
    case EXCEPTION_ACCESS_VIOLATION         :
      return ( _T ( "EXCEPTION_ACCESS_VIOLATION" ) ) ;
    case EXCEPTION_STACK_OVERFLOW           :
      return ( _T ( "EXCEPTION_STACK_OVERFLOW" ) ) ;
    case EXCEPTION_DATATYPE_MISALIGNMENT    :
      return ( _T ( "EXCEPTION_DATATYPE_MISALIGNMENT" ) ) ;
    case EXCEPTION_BREAKPOINT               :
      return ( _T ( "EXCEPTION_BREAKPOINT" ) ) ;
    case EXCEPTION_SINGLE_STEP              :
      return ( _T ( "EXCEPTION_SINGLE_STEP" ) ) ;
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED    :
      return ( _T ( "EXCEPTION_ARRAY_BOUNDS_EXCEEDED" ) ) ;
    case EXCEPTION_FLT_DENORMAL_OPERAND     :
      return ( _T ( "EXCEPTION_FLT_DENORMAL_OPERAND" ) ) ;
    case EXCEPTION_FLT_DIVIDE_BY_ZERO       :
      return ( _T ( "EXCEPTION_FLT_DIVIDE_BY_ZERO" ) ) ;
    case EXCEPTION_FLT_INEXACT_RESULT       :
      return ( _T ( "EXCEPTION_FLT_INEXACT_RESULT" ) ) ;
    case EXCEPTION_FLT_INVALID_OPERATION    :
      return ( _T ( "EXCEPTION_FLT_INVALID_OPERATION" ) ) ;
    case EXCEPTION_FLT_OVERFLOW             :
      return ( _T ( "EXCEPTION_FLT_OVERFLOW" ) ) ;
    case EXCEPTION_FLT_STACK_CHECK          :
      return ( _T ( "EXCEPTION_FLT_STACK_CHECK" ) ) ;
    case EXCEPTION_FLT_UNDERFLOW            :
      return ( _T ( "EXCEPTION_FLT_UNDERFLOW" ) ) ;
    case EXCEPTION_INT_DIVIDE_BY_ZERO       :
      return ( _T ( "EXCEPTION_INT_DIVIDE_BY_ZERO" ) ) ;
    case EXCEPTION_INT_OVERFLOW             :
      return ( _T ( "EXCEPTION_INT_OVERFLOW" ) ) ;
    case EXCEPTION_PRIV_INSTRUCTION         :
      return ( _T ( "EXCEPTION_PRIV_INSTRUCTION" ) ) ;
    case EXCEPTION_IN_PAGE_ERROR            :
      return ( _T ( "EXCEPTION_IN_PAGE_ERROR" ) ) ;
    case EXCEPTION_ILLEGAL_INSTRUCTION      :
      return ( _T ( "EXCEPTION_ILLEGAL_INSTRUCTION" ) ) ;
    case EXCEPTION_NONCONTINUABLE_EXCEPTION :
      return ( _T ( "EXCEPTION_NONCONTINUABLE_EXCEPTION" ) ) ;
    case EXCEPTION_INVALID_DISPOSITION      :
      return ( _T ( "EXCEPTION_INVALID_DISPOSITION" ) ) ;
    case EXCEPTION_GUARD_PAGE               :
      return ( _T ( "EXCEPTION_GUARD_PAGE" ) ) ;
    case EXCEPTION_INVALID_HANDLE           :
      return ( _T ( "EXCEPTION_INVALID_HANDLE" ) ) ;
    default :
      DWORD dwRet =
           FormatMessage( FORMAT_MESSAGE_IGNORE_INSERTS |
                          FORMAT_MESSAGE_FROM_SYSTEM,
                          NULL,
                          code,
                          0,
                          Buff,
                          BUFF_SIZE,
                          0 );
      if( dwRet==0 )  return( _T("<Unknown exception>") );
      Buff[dwRet-3] = 0;
      return Buff;
    };
};
