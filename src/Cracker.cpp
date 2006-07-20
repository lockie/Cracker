//---------------------------------------------------------------------------

#include <vcl.h>

#pragma comment(lib, "dbghelp.lib")

//---------------------------------------------------------------------------
USEFORM("Main.cpp", MainForm);
USEFORM("About.cpp", AboutBox);
USEFORM("fModules.cpp", Modules);
USEFORM("fLog.cpp", Log);
USEFORM("fCallStack.cpp", CallStack);
USEFORM("fDisassembly.cpp", Disassembly);
USEFORM("fParametes.cpp", Parameters);
USEFORM("fSymbols.cpp", Symbols);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Cracker";
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
