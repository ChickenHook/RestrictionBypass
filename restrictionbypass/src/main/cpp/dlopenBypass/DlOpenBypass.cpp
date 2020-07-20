//
// Created by Sascha Roth on 05.12.19.
//
#include "DlOpenBypass.h"
#include <unistd.h>
#include <sys/mman.h>
#include <vector>
#include <sys/vfs.h>

// extern "C" while debugging
static void *lokalFakeHook(void *dlopenaddr, const char *__filename, int __flag) {
    return ((void *(*)(const char *__filename, int __flag)) dlopenaddr)(__filename,
                                                                        __flag);
}

extern "C" bool updatePermissions(void *addr, int permissions) {
    size_t pagesize = (size_t) sysconf(_SC_PAGESIZE);
    void *lowerBoundary = (void *) ((long long) addr - ((long long) addr % pagesize));

    if (mprotect(lowerBoundary, pagesize, permissions) != 0) {
        return false;
    }
    return true;
}

void *DlOpenBypass::install(JNIEnv *env) {
    void *fake_dlopen_addr = (void *) env->functions->FatalError;
    if (fake_dlopen_addr == nullptr) {
        // log() << "DlOpenBypass [-] " << "Error while obtaining fatal error";
        return nullptr;
    }
    // log() << "DlOpenBypass [+] " << "sys_dlopen [+] " << "Change permission";

    if (!updatePermissions((void *) &lokalFakeHook, PROT_EXEC | PROT_READ | PROT_WRITE)) {
        // log() << "DlOpenBypass [-] " << "Error while change permission";
        return nullptr;
    }
    // log() << "DlOpenBypass [+] " << "sys_dlopen [+] " << "Change permission of fake dlopen";

    if (!updatePermissions(fake_dlopen_addr,
                           PROT_EXEC | PROT_READ | PROT_WRITE)) {
        // log() << "DlOpenBypass [-] " << "Error while change permission";
        return nullptr;
    }
    // log() << "DlOpenBypass [+] " << "sys_dlopen [+] " << "Copy data";
#ifdef __x86_64__
    memcpy((void *) env->functions->FatalError, (void *) &lokalFakeHook,
           48); // TODO architecture dependend
#elif __i386__
    memcpy((void *) env->functions->FatalError, (void *) &lokalFakeHook, 79); // TODO architecture dependend
#elif __aarch64__
    memcpy((void *) env->functions->FatalError, (void *) &lokalFakeHook, 144); // TODO architecture dependend
#elif defined(__ARM_ARCH_5TE__) || defined(__ARM_ARCH_7A__)
    memcpy((void *) env->functions->FatalError, (void *) &lokalFakeHook, 79); // TODO architecture dependend
#else
#error "UNSUPPORTED ARCHITECTURE"
#endif
    // log() << "DlOpenBypass [+] " << "sys_dlopen [+] " << "Exec fake_dlopen "
    //      << fake_dlopen_addr;

//    void *val = ((void *(*)(void *, const char *__filename, int __flag)) fake_dlopen_addr)(
//            (void *) &dlopen,
//            libName,
//            RTLD_LAZY);
//    // log() << "DlOpenBypass [+] " << "sys_dlopen [+] " << "fake dlopen returned <" << val << ">";
//    if (val == nullptr) {
//        // log() << "Error while call dlopen <" << dlerror() << ">";
//    }
    return fake_dlopen_addr;
}
