//
//  Generated file. Do not edit.
//

#include "generated_plugin_registrant.h"

#include <clipboard_plugintest/clipboard_plugintest_plugin.h>

void fl_register_plugins(FlPluginRegistry* registry) {
  g_autoptr(FlPluginRegistrar) clipboard_plugintest_registrar =
      fl_plugin_registry_get_registrar_for_plugin(registry, "ClipboardPlugintestPlugin");
  clipboard_plugintest_plugin_register_with_registrar(clipboard_plugintest_registrar);
}
