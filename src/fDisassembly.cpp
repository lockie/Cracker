//---------------------------------------------------------------------------
#include <vcl.h>

#include "fDisassembly.h"

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TDisassembly *Disassembly;

//---------------------------------------------------------------------------
__fastcall TDisassembly::TDisassembly(TComponent* Owner)
        : TForm(Owner)
{
  Height = 480;
  Width = 640;
}
//---------------------------------------------------------------------------
void __fastcall TDisassembly::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action = caFree;
  Disassembly = NULL;
}
//---------------------------------------------------------------------------
