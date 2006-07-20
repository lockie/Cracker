//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
#include <vcl.h>
#include <SyncObjs.hpp>

#include "Main.h"
#include "fLog.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TLog *Log;

//---------------------------------------------------------------------------
__fastcall TLog::TLog(TComponent* Owner)
        : TForm(Owner)
{
  Height = 480;
  Width = 640;
  mLog->Lines->Assign(MainForm->log);
}
//---------------------------------------------------------------------------
TCriticalSection* TraceSect = new TCriticalSection;

void __cdecl Trace(const char* format, ...) {
  TraceSect->Acquire();
  __try {
    va_list arglist;
    va_start(arglist, format);
    AnsiString s;
    s.vprintf(format, arglist);
    va_end(arglist);
    if( Log )  Log->mLog->Lines->Add(s);
    MainForm->log->Add(s);
  }
  __finally {
    TraceSect->Release();
  };
};
//---------------------------------------------------------------------------
void __fastcall Clear() {
  MainForm->log->Clear();
  Log->mLog->Lines->Clear();
};
//---------------------------------------------------------------------------
void __fastcall TLog::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree;
  Log = NULL;         
}
//---------------------------------------------------------------------------

void __fastcall TLog::Savelog2fileClick(TObject *Sender)
{
  if( SaveDialog->Execute() )  MainForm->log->SaveToFile(SaveDialog->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TLog::Clear1Click(TObject *Sender)
{
  Clear();
}
//---------------------------------------------------------------------------

