#pragma once
#include <fstream>

static inline void DebugLog(const char *msg) {
  std::ofstream f("/tmp/minimal_plugin_debug.txt", std::ios::app);
  f << msg << "\n";
  f.close();
}
