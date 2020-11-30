#include <iostream>
#include <string>
#include <dlfcn.h>
#include "plugin_entry.h"
#include "plugin_class.h"
#include "x.h"

PluginInitFunction PInit;
PluginFiniFunction PFini;

void *so_handle = NULL;

bool loadPlugin(const std::string &path) {
    so_handle = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
    if (!so_handle) {
        std::cout << "dlopen failed: " << dlerror() << std::endl;
        return false;
    }

    PInit = (PluginInitFunction) dlsym(so_handle, "PluginInit");
    if (PInit == NULL) {
        std::cout << "dlsym failed: PluginInit : " << dlerror() << std::endl;
        return false;
    }

    PFini = (PluginFiniFunction) dlsym(so_handle, "PluginFini");
    if (PFini == NULL) {
        std::cout << "dlsym failed: PluginFini : " << dlerror() << std::endl;
        return false;
    }

    return true;
}

PluginClass *createPlugin() {
    if (so_handle) {
        typedef PluginClass *(*CreatePluginClassFunction)();

        CreatePluginClassFunction create = (CreatePluginClassFunction) dlsym(so_handle, "CreatePluginClass");
        if (create == NULL) {
            std::cout << "dlsym failed: CreatePluginClass : " << dlerror() << std::endl;
            return nullptr;
        }

        return create();
    }

    return nullptr;
}

void nevercall() {
//    ShowX("App-Call");
}

int main(int argc, const char *argv[]) {
    std::cout << "i am an application ..." << std::endl;
    loadPlugin("../plugins/libplugin_1.so");

    // Call plugin's function
    if (PInit) {
        PInit();
    }

    if (PFini) {
        PFini();
    }

    PluginClass *plugin = createPlugin();
    if (plugin) {
//        plugin->ShowMe();
        std::cout << "create plugin ok : " << plugin->value << std::endl;
    }

    ShowX("App-Call");

    return 0;
}