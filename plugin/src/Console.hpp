#pragma once
#include "Memory.hpp"
#include "SDK/Color.hpp"

// Platform-specific calling convention
#ifndef __cdecl
#define __cdecl __attribute__((__cdecl__))
#endif

#ifdef _WIN32
#define TIER0 "tier0"
#define CONCOLORMSG_SYMBOL "?ConColorMsg@@YAXABVColor@@PBDZZ"
#else
#define TIER0 "libtier0.so"
#define CONCOLORMSG_SYMBOL "_Z11ConColorMsgRK5ColorPKcz"
#endif

#define MSG_SYMBOL "Msg"
#define WARNING_SYMBOL "Warning"

class Console {
public:
  using _Msg = void(__cdecl *)(const char *pMsgFormat, ...);
  using _Warning = void(__cdecl *)(const char *pMsgFormat, ...);
  using _ColorMsg = void(__cdecl *)(const Color &clr, const char *pMsgFormat,
                                    ...);

  _Msg Msg = nullptr;
  _ColorMsg ColorMsg = nullptr;
  _Warning Warning = nullptr;

public:
  bool Init();
  void Shutdown();
  const char *Name() { return TIER0; }
};

extern Console *console;
