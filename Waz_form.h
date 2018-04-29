//---------------------------------------------------------------------------
#ifndef Waz_formH
#define Waz_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Componentsvoid
    TPopupMenu *PopupMenu1;
    TMenuItem *Gra;
    TMenuItem *Zamknij;
    TMenuItem *Opcje;
    TMenuItem *Pauza;
    TMenuItem *Stop;
    TMenuItem *Start;
    TMenuItem *Mapka;
    TMenuItem *N121;
    TMenuItem *N111;
    TMenuItem *N101;
    TMenuItem *N91;
    TMenuItem *N81;
    TMenuItem *N71;
    TMenuItem *N61;
    TMenuItem *N51;
    TMenuItem *N41;
    TMenuItem *N31;
    TMenuItem *N21;
    TMenuItem *N11;
    TMenuItem *About;
    void __fastcall FormKeyDown(TObject *Sender, WORD &key,TShiftState Shift);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormPaint(TObject *Sender);

    void __fastcall N11Click(TObject *Sender);
    void __fastcall N21Click(TObject *Sender);
    void __fastcall N31Click(TObject *Sender);
    void __fastcall N41Click(TObject *Sender);
    void __fastcall N51Click(TObject *Sender);
    void __fastcall N61Click(TObject *Sender);
    void __fastcall N71Click(TObject *Sender);
    void __fastcall N81Click(TObject *Sender);
    void __fastcall N91Click(TObject *Sender);
    void __fastcall N101Click(TObject *Sender);
    void __fastcall N111Click(TObject *Sender);
    void __fastcall N121Click(TObject *Sender);
    void __fastcall PauzaClick(TObject *Sender);
    void __fastcall OpcjeClick(TObject *Sender);
    void __fastcall StartClick(TObject *Sender);
    void __fastcall StopClick(TObject *Sender);
    void __fastcall AboutClick(TObject *Sender);
    void __fastcall ZamknijClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
    private:	// User declarations
    void __fastcall Zbieraj(void);
    void __fastcall Load(AnsiString a_plik_name);
    void __fastcall Ruch(void);
    void __fastcall GrajFunk(void);
    void __fastcall Sound(AnsiString a_plik_name);
    bool gram,pauza,stop;
public:		// User declarations
HINSTANCE hInst;
    __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
