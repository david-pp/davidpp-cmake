#ifndef _PLUGIN_ENTRY_H
#define _PLUGIN_ENTRY_H

#include <stdint.h>

extern "C" {

typedef int32_t (*PluginInitFunction)();
typedef int32_t (*PluginFiniFunction)();
typedef int32_t (*PluginUpdateFunction)();

//int32_t PluginInit();
//int32_t PluginFini();
//int32_t PluginUpdate();
}

#endif //_PLUGIN_ENTRY_H
