//#include "plugin_entry.h"
#include <iostream>
#include <stdint.h>
#include "x.h"
#include "y.h"

void DoSomeThing() {
    ShowX("Plugin-Call");
    DontShowX("Plugin-Call");
}

extern "C" {
int32_t PluginInit() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return 0;
}

int32_t PluginFini() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    DoSomeThing();
    return 0;
}

int32_t PluginUpdate() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return 0;
}
}
