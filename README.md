# RestrictionBypass
Android API restriction bypass for all Android Versions

## Description

Small library to access hidden API restricted by https://developer.android.com/distribute/best-practices/develop/restrictions-non-sdk-interfaces

More technical details can be found: https://wordpress.com/stats/day/androidreverse.wordpress.com?tab=visitors

## Supported Android Versions

Android API 19 - 30


## Integration

Just include the maven repository

1) In your root build.gradle:
```groovy
allprojects {
        repositories {
            [..]
            jcenter()
            maven { url "https://jitpack.io" }
        }
   }
```
2) In your library/build.gradle add:
```groovy
   dependencies {
        implementation 'com.github.ChickenHook:RestrictionBypass:2.2'
   }
```
## Usage

### Java

Just include the library as explained in the Integration chapter.
The BypassProvider will automatically unseal your process and allow you to access hidden api.

### C/C++

The native restriction bypass will be installed automatically via the Content Provider and will give
you the power to load any system library.

No header or linked library is needed, just follow this example:

```c
void *(*_dlopen)(void *, const char *__filename, int __flag) = nullptr; // will be used to store the function to the new dlopen function

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

```

This bypass replaces the env->functions->FatalError function with instructions telling to jump to the original dlopen function. This let the VM think that
this call is invoked from libart itself and not from you're library.

If you find any bugs please create an issue in this project and provide logs as well as an coding example!

## Troubleshooting

Please create a bug report if you find any issues. This chapter will be updated then.


## Donate

If you're happy with my library please order me a cup of coffee ;) Thanks.

[![Donate with PayPal](https://raw.githubusercontent.com/stefan-niedermann/paypal-donate-button/master/paypal-donate-button.png)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=8UH5MBVYM3J36)

or

bc1qvll2mp5ndwd4sgycu4ad2ken4clhjac7mdlcaj

## Other Projects

| Project | Description |
|---------|-------------|
| [ChickenHook](https://github.com/ChickenHook/ChickenHook) | A linux / android / MacOS hooking framework  |
| [BinderHook](https://github.com/ChickenHook/BinderHook) | Library intended to hook Binder interface and manipulate events |
| [RestrictionBypass](https://github.com/ChickenHook/RestrictionBypass) |  Android API restriction bypass for all Android Versions |
| [AndroidManifestBypass](https://github.com/ChickenHook/AndroidManifestBypass) |  Android API restriction bypass for all Android Versions |
| .. | |
