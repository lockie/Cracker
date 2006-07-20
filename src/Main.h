//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <sysutils.hpp>
#include <windows.hpp>
#include <sysutils.hpp>
#include <classes.hpp>
#include <graphics.hpp>
#include <controls.hpp>
#include <forms.hpp>
#include <dialogs.hpp>
#include <stdctrls.hpp>
#include <buttons.hpp>
#include <extctrls.hpp>
#include <menus.hpp>
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>


#include "CrackerEngine.h"

// TODO : Disassembler!


//---------------------------------------------------------------------------

class TMainForm : public TForm
{
__published:   
	TMainMenu *MainMenu;
	TMenuItem *WindowTileItem;
	TMenuItem *WindowCascadeItem;
	TMenuItem *WindowArrangeItem;
	TMenuItem *HelpContentsItem;
	TMenuItem *HelpAboutItem;
	TOpenDialog *OpenDialog;
	TSaveDialog *SaveDialog;
	TPanel *SpeedBar;
	TSpeedButton *SpeedButton1;  // &Open...
	TSpeedButton *SpeedButton2;  // &Tile
	TSpeedButton *SpeedButton3;  // &Cascade
	TSpeedButton *SpeedButton4;  // &Arrange All
	TSpeedButton *SpeedButton5;  // &Contents
	TSpeedButton *SpeedButton6;  // &About...
	TSpeedButton *SpeedButton7;
        TMenuItem *View1;
        TMenuItem *Options;
        TMenuItem *Modules1;
        TMenuItem *CallStack1;
        TMenuItem *Disassembly1;
        TMenuItem *Hooks;
        TMenuItem *File;
        TMenuItem *Openexe;
        TMenuItem *N1;
        TMenuItem *Savedump;
        TMenuItem *N2;
        TMenuItem *CloseFile;
        TMenuItem *Exit;
        TMenuItem *Log1;
        TMenuItem *Run2;
        TMenuItem *Run1;
        TMenuItem *Pause1;
        TMenuItem *Stop1;
        TMenuItem *N4;
        TMenuItem *Stepover1;
        TMenuItem *Traceinto1;
        TMenuItem *Runtocursor1;
        TMenuItem *Rununtilreturn1;
        TMenuItem *Parameters1;
        TMenuItem *Symbols1;
	void __fastcall WindowTile(TObject *Sender);
	void __fastcall WindowCascade(TObject *Sender);
	void __fastcall WindowArrange(TObject *Sender);
	void __fastcall HelpContents(TObject *Sender);
	void __fastcall HelpSearch(TObject *Sender);
	void __fastcall HelpHowToUse(TObject *Sender);
        void __fastcall HelpAboutItemClick(TObject *Sender);
        void __fastcall ExitClick(TObject *Sender);
        void __fastcall SpeedButton7Click(TObject *Sender);
        void __fastcall Modules1Click(TObject *Sender);
        void __fastcall OpenexeClick(TObject *Sender);
        void __fastcall Log1Click(TObject *Sender);
        void __fastcall CallStack1Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall Disassembly1Click(TObject *Sender);
        void __fastcall CloseFileClick(TObject *Sender);
        void __fastcall Run1Click(TObject *Sender);
        void __fastcall Parameters1Click(TObject *Sender);
        void __fastcall SpeedButton6Click(TObject *Sender);
        void __fastcall Stop1Click(TObject *Sender);
        void __fastcall Symbols1Click(TObject *Sender);
private:        // private user declarations
public:         // public user declarations
  virtual __fastcall TMainForm(TComponent* Owner);
  virtual __fastcall ~TMainForm(void);

  void __fastcall UpdateModuleList(void);


  TStringList* log;  // TODO : Use here stack or vector with ostream !

  TCrackerEngine* Eng;

  char* parameters;
  char* currdir;
};
//---------------------------------------------------------------------------
extern TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
