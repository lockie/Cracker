//---------------------------------------------------------------------------

#ifndef fSymbolsH
#define fSymbolsH
//---------------------------------------------------------------------------

#include <windows.h>
#include <dbghelp.h>


#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TSymbols : public TForm
{
__published:	// IDE-managed Components
        TComboBox *cbModules;
        TLabel *Label1;
        TListBox *lbSymbols;
        TLabel *Label2;
        TLabel *InfoLabel;
        void __fastcall cbModulesChange(TObject *Sender);
        void __fastcall cbModulesDropDown(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations

public:		// User declarations
  __fastcall TSymbols(TComponent* Owner);

  void __fastcall UpdateModules(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TSymbols *Symbols;
//---------------------------------------------------------------------------
#endif
