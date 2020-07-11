#include "include/clipboard_plugintest/clipboard_plugintest_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>
#include <sys/utsname.h>

static constexpr char kTextKey[] = "text";

#define CLIPBOARD_PLUGINTEST_PLUGIN(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), clipboard_plugintest_plugin_get_type(), \
                              ClipboardPlugintestPlugin))

struct _ClipboardPlugintestPlugin {
  GObject parent_instance;
};

G_DEFINE_TYPE(ClipboardPlugintestPlugin, clipboard_plugintest_plugin, g_object_get_type())

static void send_response(FlMethodCall* method_call,
                          FlMethodResponse* response) {
  g_autoptr(GError) error = nullptr;
  if (!fl_method_call_respond(method_call, response, &error))
    g_warning("Failed to send method call response: %s", error->message);
}

// Called when clipboard text received.
static void clipboard_text_cb(GtkClipboard* clipboard,
                              const gchar* text,
                              gpointer user_data) {
  g_autoptr(FlMethodCall) method_call = (FlMethodCall *)user_data;

  g_autoptr(FlValue) result = nullptr;
  if (text != nullptr) {
    result = fl_value_new_map();
    fl_value_set_string_take(result, kTextKey, fl_value_new_string(text));
  }

  g_autoptr(FlMethodResponse) response =
      FL_METHOD_RESPONSE(fl_method_success_response_new(result));
  send_response(method_call, response);
}


// Called when a method call is received from Flutter.
static void clipboard_plugintest_plugin_handle_method_call(
    ClipboardPlugintestPlugin* self,
    FlMethodCall* method_call) {
  g_autoptr(FlMethodResponse) response = nullptr;

  const gchar* method = fl_method_call_get_name(method_call);

  if (strcmp(method, "getPlatformVersion") == 0) {
    struct utsname uname_data = {};
    uname(&uname_data);
    g_autofree gchar *version = g_strdup_printf("Linux %s", uname_data.version);
    g_autoptr(FlValue) result = fl_value_new_string(version);
    response = FL_METHOD_RESPONSE(fl_method_success_response_new(result));
  } else if (strcmp(method, "getData") == 0) {
    GtkClipboard* clipboard =
        gtk_clipboard_get_default(gdk_display_get_default());
    gtk_clipboard_request_text(clipboard, clipboard_text_cb,
                              g_object_ref(method_call));
                              return;
  } else {
    response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
  }

  fl_method_call_respond(method_call, response, nullptr);
}

static void clipboard_plugintest_plugin_dispose(GObject* object) {
  G_OBJECT_CLASS(clipboard_plugintest_plugin_parent_class)->dispose(object);
}

static void clipboard_plugintest_plugin_class_init(ClipboardPlugintestPluginClass* klass) {
  G_OBJECT_CLASS(klass)->dispose = clipboard_plugintest_plugin_dispose;
}

static void clipboard_plugintest_plugin_init(ClipboardPlugintestPlugin* self) {}

static void method_call_cb(FlMethodChannel* channel, FlMethodCall* method_call,
                           gpointer user_data) {
  ClipboardPlugintestPlugin* plugin = CLIPBOARD_PLUGINTEST_PLUGIN(user_data);
  clipboard_plugintest_plugin_handle_method_call(plugin, method_call);
}

void clipboard_plugintest_plugin_register_with_registrar(FlPluginRegistrar* registrar) {
  ClipboardPlugintestPlugin* plugin = CLIPBOARD_PLUGINTEST_PLUGIN(
      g_object_new(clipboard_plugintest_plugin_get_type(), nullptr));

  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                            "clipboard_plugintest",
                            FL_METHOD_CODEC(codec));
  fl_method_channel_set_method_call_handler(channel, method_call_cb,
                                            g_object_ref(plugin),
                                            g_object_unref);

  g_object_unref(plugin);
}
