#include "MinimalPlugin.hpp"
#include "Console.hpp"
#include "Debug.hpp"

MinimalPlugin plugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(MinimalPlugin, IServerPluginCallbacks,
                                  INTERFACEVERSION_ISERVERPLUGINCALLBACKS,
                                  plugin);

MinimalPlugin::MinimalPlugin() { DebugLog("MinimalPlugin constructor called"); }

bool MinimalPlugin::Load(CreateInterfaceFn interfaceFactory,
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

void MinimalPlugin::Unload() {
  DebugLog("Unload() called");
  if (console)
    console->Msg("Unloaded\n");

  if (console) {
    delete console;
    console = nullptr;
  }
}

const char *MinimalPlugin::GetPluginDescription() {
  DebugLog("GetPluginDescription() called");
  return PLUGIN_SIGNATURE;
}

// Unused callbacks - stub implementations
void MinimalPlugin::Pause() {}
void MinimalPlugin::UnPause() {}
void MinimalPlugin::LevelInit(char const *pMapName) {}
void MinimalPlugin::ServerActivate(void *pEdictList, int edictCount,
                                   int clientMax) {}
void MinimalPlugin::GameFrame(bool simulating) {}
void MinimalPlugin::LevelShutdown() {}
void MinimalPlugin::ClientFullyConnect(void *pEdict) {}
void MinimalPlugin::ClientActive(void *pEntity) {}
void MinimalPlugin::ClientDisconnect(void *pEntity) {}
void MinimalPlugin::ClientPutInServer(void *pEntity, char const *playername) {}
void MinimalPlugin::SetCommandClient(int index) {}
void MinimalPlugin::ClientSettingsChanged(void *pEdict) {}
int MinimalPlugin::ClientConnect(bool *bAllowConnect, void *pEntity,
                                 const char *pszName, const char *pszAddress,
                                 char *reject, int maxrejectlen) {
  return 0;
}
int MinimalPlugin::ClientCommand(void *pEntity, const void *&args) { return 0; }
int MinimalPlugin::NetworkIDValidated(const char *pszUserName,
                                      const char *pszNetworkID) {
  return 0;
}
void MinimalPlugin::OnQueryCvarValueFinished(int iCookie, void *pPlayerEntity,
                                             int eStatus, const char *pCvarName,
                                             const char *pCvarValue) {}
void MinimalPlugin::OnEdictAllocated(void *edict) {}
void MinimalPlugin::OnEdictFreed(const void *edict) {}
