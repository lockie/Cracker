//---------------------------------------------------------------------------
#include <vcl.h>

#include "fCallStack.h"

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TCallStack *CallStack;

//---------------------------------------------------------------------------
__fastcall TCallStack::TCallStack(TComponent* Owner)
        : TForm(Owner)
{
  Height = 480;
  Width = 640;
}
//---------------------------------------------------------------------------
void __fastcall TCallStack::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action = caFree;
  CallStack = NULL;
}
//---------------------------------------------------------------------------
