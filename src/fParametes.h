//----------------------------------------------------------------------------
#ifndef fParametesH
#define fParametesH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <Dialogs.hpp>
//----------------------------------------------------------------------------
class TParameters : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
        TLabeledEdit *CmdLine;
        TButton *Browse1;
        TLabeledEdit *WorkDir;
        TButton *Browse2;
        TOpenDialog *OpenDialog;
        void __fastcall Browse1Click(TObject *Sender);
        void __fastcall Browse2Click(TObject *Sender);
        void __fastcall OKBtnClick(TObject *Sender);
private:
public:
	virtual __fastcall TParameters(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TParameters *Parameters;
//----------------------------------------------------------------------------
#endif    
