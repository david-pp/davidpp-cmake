#include "plugin_class.h"
#include <iostream>

PluginClass::PluginClass() {
    value = 10;
    std::cout << __FILE__ << ":" << __PRETTY_FUNCTION__ << std::endl;
}

void PluginClass::ShowMe() {
    std::cout << __FILE__ << ":" << __PRETTY_FUNCTION__ << std::endl;
}

extern "C" {
PluginClass *CreatePluginClass() {
    return new PluginClass;
}

void Destroy(PluginClass *plugin) {
    delete plugin;
}
}