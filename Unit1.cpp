//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Waz_form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

void __fastcall TForm1::Levele()
{
static struct TSearchRec plik_search;
static int plik_search_ret;
static struct { AnsiString Name;
} plik[113];
static struct { AnsiString Name; long Index;
} plik_current;

for (plik_search_ret = FindFirst("*.lev",faAnyFile,plik_search), plik_current.Index = 0; !plik_search_ret && plik_current.Index < 112; plik_search_ret = FindNext(plik_search))
    {
     ++plik_current.Index;
     if (ListBox1->Items->Count < plik_current.Index)
        {
         ListBox1->Items->Add(plik_search.Name);
         plik[plik_current.Index].Name = plik_search.Name;
	    }
    }

}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormShow(TObject *Sender)
{
Levele();    
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ListBox1DblClick(TObject *Sender)
{
if (this->ListBox1->ItemIndex==-1) return;
if (MainForm->gram==true) return;
mapa = this->ListBox1->ItemIndex+1;
MainForm->Load(plik[this->ListBox1->ItemIndex+1].Name);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
Close();    
}
//---------------------------------------------------------------------------


