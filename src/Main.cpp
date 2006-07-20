//---------------------------------------------------------------------------

#include <windows.h>
#include <dbghelp.h>

#include <objbase.h>

#include <vcl.h>

#include "fLog.h"
#include "fModules.h"
#include "fParameters.h"
#include "fModules.h"
#include "fSymbols.h"
#include "fCallStack.h"
#include "fDisassembly.h"
#include "About.h"
#include "Main.h"

//---------------------------------------------------------------------------

#pragma comment(lib, "dbghelp.lib")
#pragma resource "*.dfm"
TMainForm *MainForm;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner)
{
  Eng = new TCrackerEngine();
  log = new TStringList();
  if( CoInitialize(NULL)!=S_OK ) RaiseLastOSError();
  SymSetOptions( SYMOPT_LOAD_ANYTHING | SYMOPT_LOAD_LINES | SYMOPT_UNDNAME );
  log->Capacity = 100;
  Trace("Program loaded OK.");
  parameters = NULL;
  currdir = NULL;
};
//---------------------------------------------------------------------------

__fastcall TMainForm::~TMainForm(void) {
  delete Eng;
  
  free(parameters);
  free(currdir);
  CoUninitialize();
  delete log;
};
//---------------------------------------------------------------------------

void __fastcall TMainForm::WindowTile(TObject *Sender)
{
  Tile();
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::WindowCascade(TObject *Sender)
{
  Cascade();
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::WindowArrange(TObject *Sender)
{
  ArrangeIcons();
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::HelpContents(TObject *Sender)
{
  Application->HelpCommand(HELP_CONTENTS, 0);
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::HelpSearch(TObject *Sender)
{
  Application->HelpCommand(HELP_PARTIALKEY, Longint(""));
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::HelpHowToUse(TObject *Sender)
{
  Application->HelpCommand(HELP_HELPONHELP, 0);
}
//----------------------------------------------------------------------------

void __fastcall TMainForm::ExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton7Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton1Click(TObject *Sender)
{
  OpenexeClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Parameters1Click(TObject *Sender)
{
  TParameters* p = new TParameters(this);
  p->ShowModal();
  delete p;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::HelpAboutItemClick(TObject *Sender)
{
  TAboutBox* b = new TAboutBox(this);
  b->ShowModal();
  delete b;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Modules1Click(TObject *Sender)
{
  if( !Modules ) Modules = new TModules(this);
  Modules->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Log1Click(TObject *Sender)
{
  if( !Log )  Log = new TLog(this);
  Log->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CallStack1Click(TObject *Sender)
{
  if( !CallStack )  CallStack = new TCallStack(this);
  CallStack->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Symbols1Click(TObject *Sender)
{
  if( !Symbols ) Symbols = new TSymbols(this);
  Symbols->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Disassembly1Click(TObject *Sender)
{
  if( !Disassembly )  Disassembly = new TDisassembly(this);
  Disassembly->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenexeClick(TObject *Sender)
{
  if( OpenDialog->Execute() ) {
    if( !Eng->OpenEXEFile(OpenDialog->FileName.c_str()) ) {
      Trace("Unable to open \"%s\". Error code %d.", OpenDialog->FileName.c_str(), GetLastError());
      return;
    };
    Trace("\"%s\" loaded OK.", OpenDialog->FileName.c_str() );
  };
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CloseFileClick(TObject *Sender)
{
  delete Eng;
  Eng = new TCrackerEngine();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Run1Click(TObject *Sender)
{
  Eng->Run(parameters, currdir);         
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton6Click(TObject *Sender)
{
  HelpAboutItemClick(Sender);         
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Stop1Click(TObject *Sender)
{
  Eng->Stop();        
}



