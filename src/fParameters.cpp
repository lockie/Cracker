//---------------------------------------------------------------------------

#define NO_WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <shlobj.h>
#include <vcl.h>

#include "Main.h"
#include "fParameters.h"
//---------------------------------------------------------------------------

#pragma resource "*.dfm"
TParameters *Parameters;

//---------------------------------------------------------------------------
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
    CmdLine->Text = CmdLine->Text + " " + OpenDialog->FileName ;
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
}
//---------------------------------------------------------------------------
void __fastcall TParameters::CancelClick(TObject *Sender)
{
  Close();       
}
//---------------------------------------------------------------------------
void __fastcall TParameters::OKClick(TObject *Sender)
{
  MainForm->parameters = CmdLine->Text.c_str();
  MainForm->currdir = WorkDir->Text.c_str();

  Close();        
}
//---------------------------------------------------------------------------


void __fastcall TParameters::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if( Key==VK_ESCAPE ) Close();          
}
//---------------------------------------------------------------------------

