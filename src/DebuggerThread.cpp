//---------------------------------------------------------------------------

#include <vcl.h>
#include <sysutils.hpp>

#include "fLog.h"
#include "CrackerEngine.h"
#include "DebuggerThread.h"
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TDebuggerThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TDebuggerThread::TDebuggerThread(const AnsiString* AppName,
  char* Params, const char* CurrDir) : TThread(false) {

  FreeOnTerminate = false;
  OnTerminate = Stop;
  Priority = tpHigher;

  appName = AppName;
  if( Params ) {
    params = new char[strlen(Params)+2];
    strcpy(params, Params);
  } else params = NULL;
  if( CurrDir ) {
    currDir = new char[strlen(CurrDir)+2];
    strcpy(currDir, CurrDir);
  } else currDir = NULL;


  StartupInfo = new STARTUPINFO;
  ProcessInfo = new PROCESS_INFORMATION;
  ZeroMemory( StartupInfo, sizeof(STARTUPINFO) );
  StartupInfo->cb = sizeof(STARTUPINFO);
  ZeroMemory( ProcessInfo, sizeof(PROCESS_INFORMATION) );

  DebugEvent = new DEBUG_EVENT;
  ZeroMemory(DebugEvent, sizeof(DEBUG_EVENT));
};
//---------------------------------------------------------------------------

__fastcall TDebuggerThread::~TDebuggerThread() {
  TerminateProcess(ProcessInfo->hProcess, 0);
    
};

//---------------------------------------------------------------------------

void __fastcall TDebuggerThread::Execute()
{
  //---- Place thread code here ----

  bRunning = CreateProcessA(
              appName->c_str(),
              params,
              NULL,
              NULL,
              false,
              /*CREATE_SUSPENDED | */ DEBUG_ONLY_THIS_PROCESS,
              NULL,
              currDir,
              StartupInfo,
              ProcessInfo );

  CloseHandle(ProcessInfo->hProcess);
  CloseHandle(ProcessInfo->hThread);

  if( !bRunning )  Trace("Unable to start new process! Error code %d", GetLastError());

  while( !Terminated && bRunning && WaitForDebugEvent(DebugEvent, INFINITE) ) {
    DWORD dwCont = CrackerEngine->OnDebugEvent(DebugEvent);
    if( DebugEvent->dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT )  break;
    if( Terminated ) break;
    ContinueDebugEvent(DebugEvent->dwProcessId, DebugEvent->dwThreadId, dwCont);
  };
  CrackerEngine->Stopped();
};
//---------------------------------------------------------------------------

void __fastcall TDebuggerThread::Stop(TObject* Sender) { // OnTerminate handler
  CloseHandle(ProcessInfo->hProcess);
  CloseHandle(ProcessInfo->hThread);

  delete ProcessInfo; ProcessInfo = NULL;
  delete StartupInfo; StartupInfo = NULL;

  delete DebugEvent;  DebugEvent  = NULL;
  
  CrackerEngine->DebuggerThread = NULL;
};
