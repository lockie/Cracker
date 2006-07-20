//---------------------------------------------------------------------------

#ifndef fCallStackH
#define fCallStackH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TCallStack : public TForm
{
__published:	// IDE-managed Components
        TListBox *lbCallStack;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TCallStack(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCallStack *CallStack;
//---------------------------------------------------------------------------
#endif
