//---------------------------------------------------------------------

#define NO_WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <shlobj.h>

#include <vcl.h>

#include "Main.h"
#include "fParametes.h"

//---------------------------------------------------------------------
#pragma resource "*.dfm"
TParameters *Parameters;

//---------------------------------------------------------------------
__fastcall TParameters::TParameters(TComponent* Owner)
        : TForm(Owner)
{
  CmdLine->Text = MainForm->parameters;
  WorkDir->Text = MainForm->currdir;
}
//---------------------------------------------------------------------------
void __fastcall TParameters::Browse1Click(TObject *Sender)
{
  if( OpenDialog->Execute() )
    CmdLine->Text = CmdLine->Text + " \"" + OpenDialog->FileName + "\" ";
}
//---------------------------------------------------------------------------

void __fastcall TParameters::Browse2Click(TObject *Sender)
{
  BROWSEINFO* bi = new BROWSEINFO;
  ZeroMemory(bi, sizeof(BROWSEINFO));
  bi->hwndOwner      = Handle;
  bi->pszDisplayName = new char[MAX_PATH];
  bi->lpszTitle      = "Select a working directory";
  bi->ulFlags        = BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS;

  LPITEMIDLIST l = SHBrowseForFolderA(bi);
  if( !l )  return;
  if( !SHGetPathFromIDList(l, bi->pszDisplayName) )  RaiseLastOSError();
  WorkDir->Text = bi->pszDisplayName;
  CoTaskMemFree(l);
  delete bi->pszDisplayName;
  delete bi;
};
//---------------------------------------------------------------------------

void __fastcall TParameters::OKBtnClick(TObject *Sender)
{
  MainForm->parameters = (char*)realloc(MainForm->parameters, CmdLine->Text.Length());
  MainForm->currdir = (char*)realloc(MainForm->currdir, WorkDir->Text.Length());
  strcpy(MainForm->parameters, CmdLine->Text.c_str()) ;
  strcpy(MainForm->currdir, WorkDir->Text.c_str());
}
//---------------------------------------------------------------------------

