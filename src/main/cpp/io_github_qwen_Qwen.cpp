//
// Created by r on 23-10-15.
//
#include "io_github_qwen_Qwen.h"
#include "qwen.cpp/qwen.h"
#include "iostream"
#include "ObjectCache.h"

jobject qwen_model;
jobject qwen_param;
jfieldID qwen_model_id;

jfieldID qwen_param_max_length;
jfieldID qwen_param_max_context_length;
jfieldID qwen_param_do_sample;
jfieldID qwen_param_top_k;
jfieldID qwen_param_top_p;
jfieldID qwen_param_temperature;
jfieldID qwen_param_repetition_penalty;
jfieldID qwen_param_num_threads;

ObjectCache objectCache;

std::string jstringToStdString(JNIEnv* env, jstring jstr) {
    if (jstr == nullptr) {
        return "";
    }

    const char* nativeString = env->GetStringUTFChars(jstr, nullptr);
    std::string result(nativeString);
    env->ReleaseStringUTFChars(jstr, nativeString);

    return result;
}

jstring stdStringToJString(JNIEnv* env, const std::string& str) {
    return env->NewStringUTF(str.c_str());
}

qwen::GenerationConfig parse(JNIEnv* env, jobject param) {
    auto max_length = env->GetIntField(param, qwen_param_max_length);
    auto max_context_length = env->GetIntField(param, qwen_param_max_context_length);
    auto do_sample = env->GetBooleanField(param, qwen_param_do_sample);
    auto top_k = env->GetIntField(param, qwen_param_top_k);
    auto top_p = env->GetFloatField(param, qwen_param_top_p);
    auto temperature = env->GetFloatField(param, qwen_param_temperature);
    auto repetition_penalty = env->GetFloatField(param, qwen_param_repetition_penalty);
    auto num_threads = env->GetIntField(param, qwen_param_num_threads);

    return {
                max_length, max_context_length, static_cast<bool>(do_sample), top_k, top_p, temperature, repetition_penalty, num_threads
            };
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;

    if (JNI_OK != vm->GetEnv((void **) &env, JNI_VERSION_10)) {
        return JNI_ERR;
    }

    jclass qwen_class = env->FindClass("io/github/qwen/Qwen");
    jclass qwen_param_class = env->FindClass("io/github/qwen/QwenParam");

    qwen_model_id = env->GetFieldID(qwen_class, "modelId", "J");
    qwen_param_max_length = env->GetFieldID(qwen_param_class, "maxLength", "I");
    qwen_param_max_context_length = env->GetFieldID(qwen_param_class, "maxContextLength", "I");
    qwen_param_do_sample = env->GetFieldID(qwen_param_class, "doSample", "Z");
    qwen_param_top_k = env->GetFieldID(qwen_param_class, "topK", "I");
    qwen_param_top_p = env->GetFieldID(qwen_param_class, "topP", "F");
    qwen_param_temperature = env->GetFieldID(qwen_param_class, "temperature", "F");
    qwen_param_repetition_penalty = env->GetFieldID(qwen_param_class, "repetitionPenalty", "F");
    qwen_param_num_threads = env->GetFieldID(qwen_param_class, "numThreads", "I");

    qwen_model = env->NewGlobalRef(qwen_class);
    qwen_param = env->NewGlobalRef(qwen_param_class);

    return env->GetVersion();
}


JNIEXPORT void JNICALL Java_io_github_qwen_Qwen_load
        (JNIEnv *env, jobject instance, jstring model_path, jstring t_path) {
    auto p = std::make_unique<qwen::Pipeline>(jstringToStdString(env, model_path), jstringToStdString(env, t_path));
    auto id = objectCache.store(std::move(p));
    env->SetLongField(instance, qwen_model_id, id);
}

JNIEXPORT jstring JNICALL Java_io_github_qwen_Qwen_generate
        (JNIEnv *env, jobject instance, jstring prompt, jobject param) {

    auto value = env->GetLongField(instance, qwen_model_id);
    auto p = objectCache.get(value);
    auto pipeline = p.value().get();

    qwen::GenerationConfig config = parse(env, param);
    auto result = pipeline->chat({jstringToStdString(env, prompt)}, config, nullptr);
    return stdStringToJString(env, result);
}

JNIEXPORT void JNICALL Java_io_github_qwen_Qwen_delete
        (JNIEnv *env, jobject instance) {
    auto value = env->GetLongField(instance, qwen_model_id);
    objectCache.remove(value);
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;

    if (JNI_OK != vm->GetEnv((void **) &env, JNI_VERSION_10)) {
        return;
    }

    env->DeleteGlobalRef(qwen_model);
    env->DeleteGlobalRef(qwen_param);
}