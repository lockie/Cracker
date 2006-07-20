//---------------------------------------------------------------------------
#ifndef fDisassemblyH
#define fDisassemblyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TDisassembly : public TForm
{
__published:	// IDE-managed Components
  TListBox *lbDisassembly;
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
  __fastcall TDisassembly(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TDisassembly *Disassembly;
//---------------------------------------------------------------------------
#endif
