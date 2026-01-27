#include "P2Harness.hpp"
#include "SDK/Console.hpp"
#include "Utils/Debug.hpp"

P2Harness plugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(P2Harness, IServerPluginCallbacks,
                                  INTERFACEVERSION_ISERVERPLUGINCALLBACKS,
                                  plugin);

P2Harness::P2Harness() { DebugLog("P2Harness constructor called"); }

bool P2Harness::Load(CreateInterfaceFn interfaceFactory,
                     CreateInterfaceFn gameServerFactory) {
  DebugLog("Load() called");

  console = new Console();
  DebugLog("Console created");

  if (!console->Init()) {
    DebugLog("Console Init() FAILED");
    return false;
  }

  DebugLog("Console Init() SUCCESS");
  console->Msg("Loaded\n");
  DebugLog("Msg() called");
  return true;
}

void P2Harness::Unload() {
  DebugLog("Unload() called");
  if (console)
    console->Msg("Unloaded\n");

  if (console) {
    delete console;
    console = nullptr;
  }
}

const char *P2Harness::GetPluginDescription() {
  DebugLog("GetPluginDescription() called");
  return PLUGIN_SIGNATURE;
}

// Unused callbacks - stub implementations
void P2Harness::Pause() {}
void P2Harness::UnPause() {}
void P2Harness::LevelInit(char const *pMapName) {}
void P2Harness::ServerActivate(void *pEdictList, int edictCount,
                               int clientMax) {}
void P2Harness::GameFrame(bool simulating) {}
void P2Harness::LevelShutdown() {}
void P2Harness::ClientFullyConnect(void *pEdict) {}
void P2Harness::ClientActive(void *pEntity) {}
void P2Harness::ClientDisconnect(void *pEntity) {}
void P2Harness::ClientPutInServer(void *pEntity, char const *playername) {}
void P2Harness::SetCommandClient(int index) {}
void P2Harness::ClientSettingsChanged(void *pEdict) {}
int P2Harness::ClientConnect(bool *bAllowConnect, void *pEntity,
                             const char *pszName, const char *pszAddress,
                             char *reject, int maxrejectlen) {
  return 0;
}
int P2Harness::ClientCommand(void *pEntity, const void *&args) { return 0; }
int P2Harness::NetworkIDValidated(const char *pszUserName,
                                  const char *pszNetworkID) {
  return 0;
}
void P2Harness::OnQueryCvarValueFinished(int iCookie, void *pPlayerEntity,
                                         int eStatus, const char *pCvarName,
                                         const char *pCvarValue) {}
void P2Harness::OnEdictAllocated(void *edict) {}
void P2Harness::OnEdictFreed(const void *edict) {}
