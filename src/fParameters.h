//---------------------------------------------------------------------------

#ifndef fParametersH
#define fParametersH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TParameters : public TForm
{
__published:	// IDE-managed Components
        TLabeledEdit *CmdLine;
        TButton *Browse1;
        TOpenDialog *OpenDialog;
        TLabeledEdit *WorkDir;
        TButton *Browse2;
        TButton *OK;
        TButton *Cancel;
        void __fastcall Browse1Click(TObject *Sender);
        void __fastcall Browse2Click(TObject *Sender);
        void __fastcall CancelClick(TObject *Sender);
        void __fastcall OKClick(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TParameters(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TParameters *Parameters;
//---------------------------------------------------------------------------
#endif
