//---------------------------------------------------------------------------
#ifndef OpcH
#define OpcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cspin.h"
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TOpcjeForm : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *BitBtn1;
    TEdit *Edit1;
    TBitBtn *BitBtn2;
    TUpDown *UpDown1;
    TTabControl *TabControl1;
    TUpDown *UpDown2;
    TEdit *Edit2;
    TUpDown *UpDown3;
    TEdit *Edit3;
    TBevel *Bevel1;
    TBevel *Bevel2;
    void __fastcall Edit2KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall Edit3KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TOpcjeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOpcjeForm *OpcjeForm;
//---------------------------------------------------------------------------
#endif
