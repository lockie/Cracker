//---------------------------------------------------------------------------

#include <windows.h>
#include <dbghelp.h>

#include <vcl.h>

#include "fModules.h"
#include "fLog.h"
#include "CrackerEngine.h"
#include "fSymbols.h"

//---------------------------------------------------------------------------
#pragma comment(lib, "dbghelp.lib")
#pragma resource "*.dfm"
TSymbols *Symbols;

//---------------------------------------------------------------------------
__fastcall TSymbols::TSymbols(TComponent* Owner)
        : TForm(Owner)
{
  lbSymbols->Sorted = true;
  Height = 480;
  Width = 640;
  UpdateModules();
}
//---------------------------------------------------------------------------

DWORD SymCount;

BOOL __stdcall EnumerateCallback( char* SymbolName, DWORD SymbolAddress,
 ULONG SymbolSize, void* UserContext) {

  IMAGEHLP_SYMBOL* sym = (IMAGEHLP_SYMBOL*)new char[ strlen(SymbolName) + sizeof(IMAGEHLP_SYMBOL) ];
  sym->Address = SymbolAddress;
  sym->Size =  SymbolSize;
  sym->MaxNameLength = strlen(SymbolName);
  strcpy(sym->Name, SymbolName);

  Symbols->lbSymbols->AddItem(SymbolName, (TObject*)sym);

  SymCount++;
  return true;
};

void __fastcall TSymbols::cbModulesChange(TObject *Sender)
{
  IMAGEHLP_MODULE* mod = NULL;
  for(long i=0; i < cbModules->Items->Count; i++) {
    if( strcmpi( cbModules->Text.c_str(), cbModules->Items->Strings[i].c_str() ) == 0 ) {
      mod = (IMAGEHLP_MODULE*)cbModules->Items->Objects[i];
    };
  };
  if( !mod )  return;

  // clear symbol list
  for( long i=0; i < lbSymbols->Count; i++ )  delete (char*)lbSymbols->Items->Objects[i];
  lbSymbols->Clear();

  // TODO : Pre-cache this shit! or show table "Please wait" =) 
  SymCount = 0;
  if( !SymEnumerateSymbols( CrackerEngine->GetProcessHandle(), mod->BaseOfImage,
    EnumerateCallback, NULL) )  RaiseLastOSError();

  InfoLabel->Caption = IntToStr(SymCount) + " symbols, type " + GetSymbolsType(mod->SymType);
};
//---------------------------------------------------------------------------

void __fastcall TSymbols::UpdateModules(void) {
  cbModules->Clear();
  for( long i=0; i < CrackerEngine->moduleList->Count; i++ ) {
    cbModules->AddItem(ExtractFileName(CrackerEngine->moduleList->Strings[i]),
      CrackerEngine->moduleList->Objects[i]);
  };
};
void __fastcall TSymbols::cbModulesDropDown(TObject *Sender)
{
  UpdateModules();
}
//---------------------------------------------------------------------------
void __fastcall TSymbols::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree;
  Symbols = NULL;        
}
//---------------------------------------------------------------------------


