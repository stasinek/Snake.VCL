//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Waz.res");
USEFORM("Waz_form.cpp", MainForm);
USEFORM("About_f.cpp", AboutBox);
USEFORM("Opc.cpp", OpcjeForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->Title = "Staszek Snake 1.001";
        Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TOpcjeForm), &OpcjeForm);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
