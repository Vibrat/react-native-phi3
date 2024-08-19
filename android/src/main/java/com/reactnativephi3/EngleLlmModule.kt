package com.reactnativephi3

import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactContextBaseJavaModule
import com.facebook.react.bridge.ReactMethod
import com.facebook.react.bridge.Promise
import com.facebook.react.bridge.WritableMap
import com.facebook.react.bridge.Arguments

class EngleLlmModule(reactContext: ReactApplicationContext) :
  ReactContextBaseJavaModule(reactContext) {

  override fun getName(): String {
    return NAME
  }

  // Methods that are loaded via JNI
  private external fun nativeMultiply(a: Double, b: Double): Double
  private external fun nativeInit(path: String): Boolean
  private external fun nativeInfer(text: String): String

  @ReactMethod
  fun init(path: String, promise: Promise) {
    var success = nativeInit(path)
    if (success) {
      promise.resolve(success)
    } else {
      var error: WritableMap = Arguments.createMap().apply {
        putString("errorWithDomain", "com.reactnativephi3.initialization")
        putInt("code", 1002)
        putString("errMessage", "Could not load the model")
      }
      promise.reject("IncorrectModel",  "An exception was raised when loading model", error)
    }
  }

  @ReactMethod
  fun infer(text: String, promise: Promise) {
    var reply = nativeInfer(text)
      promise.resolve(reply)
  }

  companion object {
    const val NAME = "EnglePhi3"

    init {
      System.loadLibrary("react-native-phi3")
    }
  }
}
