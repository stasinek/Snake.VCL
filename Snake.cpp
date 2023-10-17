//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USEFORM("Snake_form.cpp", MainForm);
USEFORM("Opc.cpp", OpcjeForm);
USEFORM("Unit1.cpp", Form1);
USERES("Snake.res");
USEFORM("..\..\FORM_TEMPLATES\About_frm.cpp", About_form);
//---------------------------------------------------------------------------
#include "..\..\FORM_TEMPLATES\About_frm.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->Title = "SSTSOFT.Snake.VCL 1.1";
                 Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->CreateForm(__classid(TOpcjeForm), &OpcjeForm);
         Application->CreateForm(__classid(TForm1), &Form1);
         Application->CreateForm(__classid(TAbout_form), &About_form);
         Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
