import Flutter
import UIKit

public class SwiftClipboardPlugintestPlugin: NSObject, FlutterPlugin {
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "clipboard_plugintest", binaryMessenger: registrar.messenger())
    let instance = SwiftClipboardPlugintestPlugin()
    registrar.addMethodCallDelegate(instance, channel: channel)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
    result("iOS " + UIDevice.current.systemVersion)
  }
}
