//---------------------------------------------------------------------------
#include <stdio.h>
#include <time.h>

#include <windows.h>
#include <dbghelp.h>
#include <psapi.h>
#include <winver.h>

#include <vcl.h>

#include "CrackerEngine.h"
#include "fModules.h"
//---------------------------------------------------------------------------
#pragma comment(lib, "dbghelp.lib")
#pragma resource "*.dfm"
TModules *Modules;

#define VER_BUFF_SIZE 4096
static char v[VER_BUFF_SIZE];
#define BUFF_SIZE 1024
static char Buffer[BUFF_SIZE];
static VS_FIXEDFILEINFO* ver;

static DWORD dwTemp;

//---------------------------------------------------------------------------
__fastcall TModules::TModules(TComponent* Owner)
        : TForm(Owner)
{
  Height = 480;
  Width = 640;
  UpdateList();
}
//---------------------------------------------------------------------------


void __fastcall TModules::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree;
  Modules = NULL;
}
//---------------------------------------------------------------------------

// GetSymbolsType
//
const char* GetSymbolsType(SYM_TYPE type) {
  switch(type) {
    case SymCoff :
      return "COFF      ";
    case SymCv :
      return "CodeView  ";
    case SymDeferred :
      return "<Deferred>";
    case SymDia :
      return "DIA       ";
    case SymExport :
      return "Export    ";
    case SymNone :
      return "<None>    ";
    case SymPdb :
      return "PDB       ";
    case SymSym :
      return "sym       ";
    default:
      return "<Unknown> ";
  };
};

// GetModuleVersion
//
unsigned long __fastcall GetModuleVersion(const char* szFileName, const char* buff) {
  dwTemp = GetFileVersionInfoSize((char*)szFileName, &dwTemp);
  if (dwTemp==0) return 0;
  if (VER_BUFF_SIZE < dwTemp) return 0;

  if (!GetFileVersionInfoA((char*)szFileName, NULL, dwTemp, v)) return 0;
  if (!VerQueryValueA(v, "\\", (void**)&ver, (unsigned int*)&dwTemp ) ) return 0;

  return sprintf((char*)buff, "version %lu.%lu.%lu.%lu", HIWORD(ver->dwFileVersionMS),
    LOWORD(ver->dwFileVersionMS), HIWORD(ver->dwFileVersionLS), LOWORD(ver->dwFileVersionLS) );
};


void __fastcall TModules::UpdateList(void) {
  if( !this )  return;
  // first, get the longest DLL name
  long len = 0;
  for( long i=0; i < CrackerEngine->moduleList->Count; i++ ) {
    long l = ExtractFileName(CrackerEngine->moduleList->Strings[i]).Length();
    if( len < l )  len = l;
  };
  if( len<4 ) len=4;
  MODULEINFO modinfo;
  IMAGEHLP_MODULE* mod;
  AnsiString s, name;
  lbModules->Clear();
  for( long i=0; i < CrackerEngine->moduleList->Count; i++ ) {
    mod = (IMAGEHLP_MODULE*)CrackerEngine->moduleList->Objects[i];
    name = ExtractFileName(CrackerEngine->moduleList->Strings[i]);

    s.printf("%s", name.data());
    s=s + AnsiString::StringOfChar(0x20, len+2-name.Length());

    if (!GetModuleInformation(CrackerEngine->GetProcessHandle(), (void*)mod->BaseOfImage,
      &modinfo, sizeof(MODULEINFO)) )  return;

    s.cat_sprintf("%p - %p, entrypoint at %p, ", modinfo.lpBaseOfDll,
      (unsigned long)modinfo.lpBaseOfDll + modinfo.SizeOfImage, modinfo.EntryPoint);

    s.cat_printf("Symbols type %s, ", GetSymbolsType(mod->SymType) );

    dwTemp = GetTimestampForLoadedLibrary(modinfo.lpBaseOfDll);
    if( dwTemp!=0 ) {
      tm* Tm = localtime((time_t*)&dwTemp); //f*ck!
      strftime(Buffer, BUFF_SIZE, "timestamp %c, ", Tm);
      s.cat_printf(Buffer);
     } else {
      s.cat_printf("<image not timestamped>    , ") ;
    };

    dwTemp = GetModuleVersion(CrackerEngine->moduleList->Strings[i].c_str(), Buffer);
    if (dwTemp == 0) {
      s.cat_printf("%-24.24s", "version <Unknown>" );
     } else {
      s.cat_printf("%-24.24s", Buffer);
    };
    s.cat_printf("; %s", CrackerEngine->moduleList->Strings[i].data());

    lbModules->Items->Add(s);
  };
  lbModules->Refresh();
};
