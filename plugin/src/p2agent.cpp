#include "CommandBuffer.h"
#include "eiface.h"
#include "interface.h"
#include "iserverplugin.h"

IVEngineServer *engine = nullptr;

class P2AgentPlugin final : public IServerPluginCallbacks {
public:
  bool Load(CreateInterfaceFn interfaceFactory,
            CreateInterfaceFn gameServerFactory) override {
    engine = (IVEngineServer *)interfaceFactory(INTERFACEVERSION_VENGINESERVER,
                                                nullptr);

    if (engine) {
      engine->LogPrint("[p2agent] Hello from native plugin\n");
    }

    return true;
  }

  void Unload() override {}
  void Pause() override {}
  void UnPause() override {}
  const char *GetPluginDescription() override {
    return "p2agent native plugin";
  }

  void LevelInit(char const *) override {}
  void ServerActivate(edict_t *, int, int) override {}
  void GameFrame(bool) override {}
  void LevelShutdown() override {}

  void ClientActive(edict_t *) override {}
  void ClientDisconnect(edict_t *) override {}
  void ClientPutInServer(edict_t *, char const *) override {}
  void SetCommandClient(int) override {}
  void ClientSettingsChanged(edict_t *) override {}

  PLUGIN_RESULT ClientConnect(bool *, edict_t *, char const *, char const *,
                              char *, int) override {
    return PLUGIN_CONTINUE;
  }

  PLUGIN_RESULT ClientCommand(edict_t *pEntity, const CCommand &args) override {
    if (engine && args.ArgC() > 0) {
      engine->LogPrint("[p2agent] ClientCommand received\n");
    }
    return PLUGIN_CONTINUE;
  }

  PLUGIN_RESULT NetworkIDValidated(char const *, char const *) override {
    return PLUGIN_CONTINUE;
  }

  void OnQueryCvarValueFinished(QueryCvarCookie_t, edict_t *,
                                EQueryCvarValueStatus, char const *,
                                char const *) override {}

  // REQUIRED in Portal 2
  void OnEdictAllocated(edict_t *) override {}
  void OnEdictFreed(const edict_t *) override {}
};

P2AgentPlugin g_P2Agent;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(P2AgentPlugin, IServerPluginCallbacks,
                                  INTERFACEVERSION_ISERVERPLUGINCALLBACKS,
                                  g_P2Agent);
