//
// Created by Sascha Roth on 05.12.19.
//

#pragma once


#include <jni.h>
#include <string>

/**
 * On latest Android versions dlopen of system libraries is forbidden.
 *
 * This module bypasses this by using ChickenHook and jni.
 * See also: [bypass classname]
 *
 *
 */
class DlOpenBypass {
public:

    static void * install(JNIEnv *env);
private:


};
