#ifndef _PLUGIN_CLASS_H
#define _PLUGIN_CLASS_H

class PluginClass {
public:
    PluginClass();
    void ShowMe();

    int value = 0;
};

extern "C" {
PluginClass *CreatePluginClass();
void Destroy(PluginClass *);
}

#endif //_PLUGIN_CLASS_H
