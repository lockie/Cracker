//---------------------------------------------------------------------------
#ifndef fModulesH
#define fModulesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

//---------------------------------------------------------------------------
class TModules : public TForm
{
__published:	// IDE-managed Components
        TListBox *lbModules;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
  __fastcall TModules(TComponent* Owner);

  void __fastcall UpdateList(void);

};
//---------------------------------------------------------------------------
extern PACKAGE TModules *Modules;

extern const char* GetSymbolsType(SYM_TYPE type);

//---------------------------------------------------------------------------
#endif
