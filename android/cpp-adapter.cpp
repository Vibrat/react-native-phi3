#include <jni.h>
#include "engle_onnx.h"

extern "C" JNIEXPORT jboolean JNICALL
Java_com_reactnativephi3_EngleLlmModule_nativeInit(JNIEnv *env, jclass type, jstring path)
{
    const char *cPath = env->GetStringUTFChars(path, nullptr);
    std::string strPath(cPath);
    env->ReleaseStringUTFChars(path, cPath);
    return EngleOnnx::init(strPath);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_reactnativephi3_EngleLlmModule_nativeInfer(JNIEnv *env, jclass type, jstring message)
{
    const char *cMessage = env->GetStringUTFChars(message, nullptr);
    const std::string strMessage(cMessage);
    env->ReleaseStringUTFChars(message, cMessage);
    auto &instance = EngleOnnx::getInstance();
    std::string reply = instance.infer(strMessage);
    jstring replyJavaString = env->NewStringUTF(reply.c_str());
    return replyJavaString;
}
