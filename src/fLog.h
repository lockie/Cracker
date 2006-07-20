//---------------------------------------------------------------------------

#ifndef f_LogH
#define f_LogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TLog : public TForm
{
__published:	// IDE-managed Components
        TMemo *mLog;
        TPopupMenu *PopupMenu;
        TMenuItem *Savelog2file;
        TMenuItem *N1;
        TMenuItem *Clear1;
        TSaveDialog *SaveDialog;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Savelog2fileClick(TObject *Sender);
        void __fastcall Clear1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TLog(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TLog *Log;
//---------------------------------------------------------------------------

extern void __cdecl Trace(const char* format, ...);
extern void __fastcall Clear();

//---------------------------------------------------------------------------
#endif
