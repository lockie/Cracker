//---------------------------------------------------------------------------
#ifndef CrackerEngineH
#define CrackerEngineH
//---------------------------------------------------------------------------

#include <vcl.h>

#include "DebuggerThread.h"



class TCrackerEngine {
friend class TDebuggerThread;
private:
  TCrackerEngine(const TCrackerEngine&) {};  // disallowed

  void __fastcall Stopped();  // program ended
  DWORD __fastcall OnDebugEvent(const DEBUG_EVENT* DebugEvent);

  HANDLE hFile;
  HANDLE hMapping;
  char* lpView;

  TDebuggerThread* DebuggerThread;


public:
  TCrackerEngine();
  ~TCrackerEngine();

  bool __fastcall OpenEXEFile(const char* filename);

  bool __fastcall Run(char* Parameters, const char* CurrDir);

  bool __fastcall Stop(void);

  HANDLE __fastcall GetProcessHandle();

  void __fastcall UpdateModuleList(void);

  AnsiString* ExeName;

  bool bFirstBP;

  TStringList* moduleList; // TODO : Use here map class!
  TStringList* _moduleList;
};



extern TCrackerEngine* CrackerEngine;






//---------------------------------------------------------------------------
#endif
