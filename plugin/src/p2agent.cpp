#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __attribute__((visibility("default")))
#endif

#ifndef _WIN32
#include <dlfcn.h>
#endif
#include <cstring>

// --------------------------------------------------
// Minimal Source types
// --------------------------------------------------

typedef int bool32;

class IServerPluginCallbacks {
public:
  virtual bool32 Load(void *interfaceFactory, void *gameServerFactory) = 0;
  virtual void Unload() = 0;
  virtual void Pause() {}
  virtual void UnPause() {}
  virtual const char *GetPluginDescription() = 0;
  virtual void LevelInit(char const *pMapName) {}
  virtual void ServerActivate(void *pEdictList, int edictCount, int clientMax) {
  }
  virtual void GameFrame(bool simulating) {}
  virtual void LevelShutdown() {}
  virtual void ClientActive(void *pEntity) {}
  virtual void ClientDisconnect(void *pEntity) {}
  virtual void ClientPutInServer(void *pEntity, char const *playername) {}
  virtual void SetCommandClient(int index) {}
  virtual void ClientSettingsChanged(void *pEdict) {}
  virtual void ClientConnect(bool32 *bAllowConnect, void *pEntity,
                             const char *pszName, const char *pszAddress,
                             char *reject, int maxrejectlen) {}
  virtual void ClientCommand(void *pEntity) {}
  virtual void NetworkIDValidated(const char *pszUserName,
                                  const char *pszNetworkID) {}
  virtual void OnQueryCvarValueFinished(int iCookie, void *pPlayerEntity,
                                        int eStatus, const char *pCvarName,
                                        const char *pCvarValue) {}
  virtual void OnEdictAllocated(void *edict) {}
  virtual void OnEdictFreed(const void *edict) {}
};

// --------------------------------------------------
// Msg() import (tier0)
// --------------------------------------------------

typedef void (*MsgFn)(const char *fmt, ...);
MsgFn Msg = nullptr;

// --------------------------------------------------
// Plugin implementation
// --------------------------------------------------

class HelloPlugin : public IServerPluginCallbacks {
public:
  bool32 Load(void *interfaceFactory, void *gameServerFactory) override {
    // tier0 exports Msg, grab it dynamically
#ifdef _WIN32
    auto tier0 = GetModuleHandleA("tier0.dll");
    Msg = (MsgFn)GetProcAddress(tier0, "Msg");
#else
    Msg = (MsgFn)dlsym(RTLD_DEFAULT, "Msg");
#endif

    if (Msg) {
      Msg("[HelloPlugin] Hello World from Portal 2!\n");
    }
    return 1;
  }

  void Unload() override {
    if (Msg) {
      Msg("[HelloPlugin] Unloaded.\n");
    }
  }

  const char *GetPluginDescription() override {
    return "Minimal Hello World Plugin";
  }
};

// --------------------------------------------------
// Factory export
// --------------------------------------------------

HelloPlugin g_Plugin;

extern "C" DLL_EXPORT void *CreateInterface(const char *name, int *ret) {
  if (!std::strcmp(name, "ISERVERPLUGINCALLBACKS003")) {
    if (ret)
      *ret = 0;
    return &g_Plugin;
  }
  if (ret)
    *ret = 1;
  return nullptr;
}
