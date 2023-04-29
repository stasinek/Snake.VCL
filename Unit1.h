//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TListBox *ListBox1;
    TImage *Image1;
    TButton *Button1;
    TButton *Button2;
    TBevel *Bevel1;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ListBox1DblClick(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
    void __fastcall Levele();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
