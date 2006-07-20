//---------------------------------------------------------------------------

#ifndef DebuggerThreadH
#define DebuggerThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>


//---------------------------------------------------------------------------
class TDebuggerThread : public TThread {
private:
protected:
  void __fastcall Execute();
  void __fastcall Stop(TObject* Sender);

  DEBUG_EVENT* DebugEvent;

public:
  __fastcall TDebuggerThread(const AnsiString* AppName, char* Params, const char* CurrDir);
  virtual __fastcall ~TDebuggerThread(void);



  bool bRunning;
  const AnsiString* appName;
  char* params;
  char* currDir;

  STARTUPINFO* StartupInfo;
  PROCESS_INFORMATION* ProcessInfo;
};
//---------------------------------------------------------------------------
#endif
