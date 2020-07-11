#import "ClipboardPlugintestPlugin.h"
#if __has_include(<clipboard_plugintest/clipboard_plugintest-Swift.h>)
#import <clipboard_plugintest/clipboard_plugintest-Swift.h>
#else
// Support project import fallback if the generated compatibility header
// is not copied when this plugin is created as a library.
// https://forums.swift.org/t/swift-static-libraries-dont-copy-generated-objective-c-header/19816
#import "clipboard_plugintest-Swift.h"
#endif

@implementation ClipboardPlugintestPlugin
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  [SwiftClipboardPlugintestPlugin registerWithRegistrar:registrar];
}
@end
