// You have generated a new plugin project without
// specifying the `--platforms` flag. A plugin project supports no platforms is generated.
// To add platforms, run `flutter create -t plugin --platforms <platforms> .` under the same
// directory. You can also find a detailed instruction on how to add platforms in the `pubspec.yaml` at https://flutter.dev/docs/development/packages-and-plugins/developing-packages#plugin-platforms.

import 'dart:async';

import 'package:flutter/services.dart';

class ClipboardPlugintest {
  static const MethodChannel _channel =
      const MethodChannel('clipboard_plugintest');

  static Future<String> get platformVersion async {
    final String version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }

  static Future<String> getData() async {
    final dynamic ret = await _channel.invokeMethod('getData');
    if (ret is Map) {
      return ret['text'] as String;
    }
    return null;
  }
}
