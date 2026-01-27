#include "Console.hpp"
#include "Debug.hpp"

bool Console::Init() {
  DebugLog("Console::Init() called");

  auto tier0 = Memory::GetModuleHandleByName(this->Name());
  DebugLog(tier0 ? "tier0 module found" : "tier0 module NOT found");

  if (tier0) {
    this->Msg = Memory::GetSymbolAddress<_Msg>(tier0, MSG_SYMBOL);
    DebugLog(this->Msg ? "Msg symbol found" : "Msg symbol NOT found");

    this->ColorMsg =
        Memory::GetSymbolAddress<_ColorMsg>(tier0, CONCOLORMSG_SYMBOL);
    DebugLog(this->ColorMsg ? "ColorMsg symbol found"
                            : "ColorMsg symbol NOT found");

    this->Warning = Memory::GetSymbolAddress<_Warning>(tier0, WARNING_SYMBOL);
    DebugLog(this->Warning ? "Warning symbol found"
                           : "Warning symbol NOT found");

    Memory::CloseModuleHandle(tier0);
  }

  bool result = tier0 && this->Msg && this->ColorMsg && this->Warning;
  DebugLog(result ? "Console::Init() returning true"
                  : "Console::Init() returning false");
  return result;
}

void Console::Shutdown() {}

Console *console;
