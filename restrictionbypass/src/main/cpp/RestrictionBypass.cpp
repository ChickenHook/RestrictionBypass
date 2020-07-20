#include <jni.h>
#include <android/log.h>
#include <thread>
#include <future>
#include <dlfcn.h>
#include "dlopenBypass/DlOpenBypass.h"

/////////////////// HELPERS
JavaVM *_vm;

JNIEnv *attachCurrentThread() {
    JNIEnv *env;

    int res = _vm->AttachCurrentThread(&env, nullptr);
    __android_log_print(ANDROID_LOG_DEBUG, "native", "Found attached %d", res);
    return env;
}

void detachCurrentThread() {
    _vm->DetachCurrentThread();
}

void printClassName(jobject obj, JNIEnv *env) {
    jclass cls = env->GetObjectClass(obj);

// First get the class object
    jmethodID mid = env->GetMethodID(cls, "getClass", "()Ljava/lang/Class;");
    jobject clsObj = env->CallObjectMethod(obj, mid);

// Now get the class object's class descriptor
    cls = env->GetObjectClass(clsObj);

// Find the getName() method on the class object
    mid = env->GetMethodID(cls, "getName", "()Ljava/lang/String;");

// Call the getName() to get a jstring object back
    jstring strObj = (jstring) env->CallObjectMethod(clsObj, mid);

// Now get the c string from the java jstring object
    const char *str = env->GetStringUTFChars(strObj, NULL);

// Print the class name
    __android_log_print(ANDROID_LOG_DEBUG, "native", "Calling class is: %s\n", str);
// Release the memory pinned char array
    env->ReleaseStringUTFChars(strObj, str);
}
///////////////////////////////////////////////////////////////////////
///////////////////////////// THE EXPLOIT /////////////////////////////
///////////////////////////////////////////////////////////////////////

/////////////// GET DECLARED METHOD ///////////////
static jobject getDeclaredMethod_internal(
        jobject clazz,
        jstring method_name,
        jobjectArray params) {
    JNIEnv *env = attachCurrentThread();
    printClassName(clazz, env);
    jclass clazz_class = env->GetObjectClass(clazz);
    jmethodID get_declared_method_id = env->GetMethodID(clazz_class, "getDeclaredMethod",
                                                        "(Ljava/lang/String;[Ljava/lang/Class;)Ljava/lang/reflect/Method;");

    jobject res = env->CallObjectMethod(clazz, get_declared_method_id,
                                        method_name, params);
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
    jobject global_res = nullptr;
    if (res != nullptr) {
        global_res = env->NewGlobalRef(res);
    }
    detachCurrentThread();
    return global_res;
}

static jobject Java_getDeclaredMethod(
        JNIEnv *env,
        jclass interface,
        jobject clazz,
        jstring method_name,
        jobjectArray params) {
    auto global_clazz = env->NewGlobalRef(clazz);
    jstring global_method_name = (jstring) env->NewGlobalRef(method_name);
    int arg_length = env->GetArrayLength(params);
    jobjectArray global_params = nullptr;
    if (params != nullptr) {
        for (int i = 0; i < arg_length; i++) {
            jobject element = (jobject) env->GetObjectArrayElement(params, i);
            jobject global_element = env->NewGlobalRef(element);
            env->SetObjectArrayElement(params, i, global_element);
        }
        global_params = (jobjectArray) env->NewGlobalRef(params);
    }

    auto future = std::async(&getDeclaredMethod_internal, global_clazz,
                             global_method_name,
                             global_params);
    auto result = future.get();
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
    return result;
}

/////////////// GET METHOD ///////////////
static jobject getMethod_internal(
        jobject clazz,
        jstring method_name,
        jobjectArray params) {
    JNIEnv *env = attachCurrentThread();
    printClassName(clazz, env);
    jclass clazz_class = env->GetObjectClass(clazz);
    jmethodID get_declared_method_id = env->GetMethodID(clazz_class, "getMethod",
                                                        "(Ljava/lang/String;[Ljava/lang/Class;)Ljava/lang/reflect/Method;");
    jobject res = env->CallObjectMethod(clazz, get_declared_method_id,
                                        method_name, params);
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
    jobject global_res = nullptr;
    if (res != nullptr) {
        global_res = env->NewGlobalRef(res);
    }

    detachCurrentThread();
    return global_res;
}

static jobject Java_getMethod(
        JNIEnv *env,
        jclass interface,
        jobject clazz,
        jstring method_name,
        jobjectArray params) {
    auto global_clazz = env->NewGlobalRef(clazz);
    jstring global_method_name = (jstring) env->NewGlobalRef(method_name);
    int arg_length = env->GetArrayLength(params);
    jobjectArray global_params = nullptr;
    if (params != nullptr) {
        for (int i = 0; i < arg_length; i++) {
            jobject element = (jobject) env->GetObjectArrayElement(params, i);
            jobject global_element = env->NewGlobalRef(element);
            env->SetObjectArrayElement(params, i, global_element);
        }
        global_params = (jobjectArray) env->NewGlobalRef(params);
    }
    auto future = std::async(&getMethod_internal, global_clazz,
                             global_method_name,
                             global_params);
    auto result = future.get();
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
    return result;
}

/////////////// GET DECLARED FIELD ///////////////
static jobject getDeclaredField_internal(
        jobject object,
        jstring field_name) {

    JNIEnv *env = attachCurrentThread();


    printClassName(object, env);
    jclass clazz_class = env->GetObjectClass(object);
    jmethodID methodId = env->GetMethodID(clazz_class, "getDeclaredField",
                                          "(Ljava/lang/String;)Ljava/lang/reflect/Field;");
    jobject res = env->CallObjectMethod(object, methodId, field_name);
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
    jobject global_res = nullptr;
    if (res != nullptr) {
        global_res = env->NewGlobalRef(res);
    }

    detachCurrentThread();
    return global_res;
}

static jobject Java_getDeclaredField(
        JNIEnv *env,
        jclass interface,
        jobject object,
        jstring field_name) {
    auto global_object = env->NewGlobalRef(object);
    jstring global_field_name = (jstring) env->NewGlobalRef(field_name);
    auto future = std::async(&getDeclaredField_internal, global_object,
                             global_field_name);
    auto result = future.get();
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
    return result;
}




////////// JNI STUFF


static const JNINativeMethod gMethods[] = {
        {"getDeclaredMethod", "(Ljava/lang/Object;Ljava/lang/String;[Ljava/lang/Class;)Ljava/lang/reflect/Method;", (void *) Java_getDeclaredMethod},
        {"getMethod",         "(Ljava/lang/Object;Ljava/lang/String;[Ljava/lang/Class;)Ljava/lang/reflect/Method;", (void *) Java_getMethod},
        {"getDeclaredField",  "(Ljava/lang/Object;Ljava/lang/String;)Ljava/lang/reflect/Field;",                    (void *) Java_getDeclaredField},
};
static const char *classPathName = "org/chickenhook/restrictionbypass/NativeReflectionBypass";

static int registerNativeMethods(JNIEnv *env, const char *className,
                                 JNINativeMethod *gMethods, int numMethods) {
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == nullptr) {
        __android_log_print(ANDROID_LOG_DEBUG, "registerNativeMethods",
                            "Native registration unable to find class '%s'", className);
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        __android_log_print(ANDROID_LOG_DEBUG, "registerNativeMethods",
                            "Native registration unable to register natives...");
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

int installDlopenBypass(JNIEnv *env) {
    if (DlOpenBypass::install(env) != nullptr) {
        return 1;
    }
    return 0;
}

void *(*_dlopen)(void *, const char *__filename, int __flag) = nullptr;

void test(JNIEnv *env) {
    // place address of the new dlopen function
    _dlopen = (void *(*)(void *, const char *__filename, int __flag)) env->functions->FatalError;

#if __x86_64__ || __aarch64__
    void *val = _dlopen((void *) &dlopen, "/system/lib64/libssl.so",
                        RTLD_LAZY);
#else
    void *val = _dlopen((void *) &dlopen, "/system/lib/libssl.so",
                        RTLD_LAZY);
#endif
    if (val != nullptr) {
        __android_log_print(ANDROID_LOG_INFO, "RestrictionBypass",
                            "Install dlopen bypass test successful! have fun!");
    } else {

        __android_log_print(ANDROID_LOG_INFO, "RestrictionBypass",
                            "Install dlopen bypass test NOT SUCCESSFUL! Please provide logs!");
    }
}

jint JNI_OnLoad(JavaVM *vm, void * /*reserved*/) {
    _vm = vm;
    JNIEnv *env = nullptr;
    if (vm->GetEnv((void **) (&env), JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }


    if (!registerNativeMethods(env, classPathName,
                               (JNINativeMethod *) gMethods,
                               sizeof(gMethods) / sizeof(gMethods[0]))) {
        return -1;
    }

    if (installDlopenBypass(env) == 1) {
        __android_log_print(ANDROID_LOG_INFO, "RestrictionBypass",
                            "Install dlopen bypass successful.. starting test!");
    } else {
        __android_log_print(ANDROID_LOG_INFO, "RestrictionBypass",
                            "Install dlopen bypass NOT SUCCESSFUL !!");
    }
    test(env);

    return JNI_VERSION_1_4;
}