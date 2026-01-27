#include "ServerPlugin.hpp"
#include <cstring>

// Platform-specific DLL export
#ifdef _WIN32
#define DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define DLL_EXPORT extern "C" __attribute__((visibility("default")))
#endif

InterfaceReg *InterfaceReg::s_pInterfaceRegs = nullptr;

static void *CreateInterfaceInternal(const char *pName, int *pReturnCode) {
  InterfaceReg *pCur;

  for (pCur = InterfaceReg::s_pInterfaceRegs; pCur; pCur = pCur->m_pNext) {
    if (!std::strcmp(pCur->m_pName, pName)) {
      if (pReturnCode) {
        *pReturnCode = 0;
      }
      return pCur->m_CreateFn();
    }
  }

  if (pReturnCode) {
    *pReturnCode = 1;
  }
  return nullptr;
}

DLL_EXPORT void *CreateInterface(const char *pName, int *pReturnCode) {
  return CreateInterfaceInternal(pName, pReturnCode);
}
