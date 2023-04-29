//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Waz_form.h"

#include "Opc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOpcjeForm *OpcjeForm;
//---------------------------------------------------------------------------
__fastcall TOpcjeForm::TOpcjeForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TOpcjeForm::Edit2KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key==13 || Key==27)
    OpcjeForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TOpcjeForm::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key==13 || Key==27)
    OpcjeForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TOpcjeForm::Edit3KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key==13 || Key==27)
    OpcjeForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TOpcjeForm::BitBtn1Click(TObject *Sender)
{
Close();    
}
//---------------------------------------------------------------------------

void __fastcall TOpcjeForm::BitBtn2Click(TObject *Sender)
{
Close();    
}
//---------------------------------------------------------------------------

