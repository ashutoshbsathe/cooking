#pragma once

#ifdef _WIN32
#include <windows.h>
#else
#include <cstring>
#include <dlfcn.h>
#include <link.h>
#include <string>
#endif

#include "../Utils/Debug.hpp"
#include <vector>

namespace Memory {
struct ModuleInfo {
  char name[256];
  uintptr_t base;
  uintptr_t size;
  char path[4096];
};

extern std::vector<ModuleInfo> moduleList;

inline bool TryGetModule(const char *moduleName, ModuleInfo *info) {
  // Build module list if empty
  if (moduleList.empty()) {
    DebugLog("Building module list...");
#ifdef _WIN32
    // Windows implementation would go here
#else
    dl_iterate_phdr(
        [](struct dl_phdr_info *info, size_t, void *) {
          auto temp = std::string(info->dlpi_name);
          auto index = temp.find_last_of("\\/");
          temp = temp.substr(index + 1, temp.length() - index);

          for (int i = 0; i < info->dlpi_phnum; ++i) {
            // Look for executable segments
            if (info->dlpi_phdr[i].p_flags & 1) {
              ModuleInfo module;
              module.base = info->dlpi_addr + info->dlpi_phdr[i].p_vaddr;
              module.size = info->dlpi_phdr[i].p_memsz;
              std::strncpy(module.name, temp.c_str(), sizeof(module.name));
              std::strncpy(module.path, info->dlpi_name, sizeof(module.path));
              moduleList.push_back(module);

              // Debug: log each module found
              char debugMsg[512];
              snprintf(debugMsg, sizeof(debugMsg),
                       "Found module: name='%s' path='%s'", module.name,
                       module.path);
              DebugLog(debugMsg);
              break;
            }
          }
          return 0;
        },
        nullptr);
#endif
  }

  // Debug: log what we're searching for
  char searchMsg[256];
  snprintf(searchMsg, sizeof(searchMsg), "Searching for module: '%s'",
           moduleName);
  DebugLog(searchMsg);

  // Find module by name
  for (ModuleInfo &item : moduleList) {
    if (!std::strcmp(item.name, moduleName)) {
      if (info) {
        *info = item;
      }
      char foundMsg[256];
      snprintf(foundMsg, sizeof(foundMsg), "Module '%s' FOUND at path: %s",
               moduleName, item.path);
      DebugLog(foundMsg);
      return true;
    }
  }

  DebugLog("Module NOT found in list");
  return false;
}

inline void *GetModuleHandleByName(const char *moduleName) {
  auto info = ModuleInfo();
#ifdef _WIN32
  return (TryGetModule(moduleName, &info)) ? GetModuleHandleA(info.path)
                                           : nullptr;
#else
  return (TryGetModule(moduleName, &info))
             ? dlopen(info.path, RTLD_NOLOAD | RTLD_NOW)
             : nullptr;
#endif
}

inline void CloseModuleHandle(void *moduleHandle) {
  if (!moduleHandle)
    return;
#ifdef _WIN32
  FreeLibrary((HMODULE)moduleHandle);
#else
  dlclose(moduleHandle);
#endif
}

template <typename T = void *>
T GetSymbolAddress(void *moduleHandle, const char *symbolName) {
#ifdef _WIN32
  return (T)GetProcAddress((HMODULE)moduleHandle, symbolName);
#else
  return (T)dlsym(moduleHandle, symbolName);
#endif
}
} // namespace Memory
