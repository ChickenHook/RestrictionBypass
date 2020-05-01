# RestrictionBypass
Android API restriction bypass for all Android Versions

## Description

Small library to access hidden API restricted by https://developer.android.com/distribute/best-practices/develop/restrictions-non-sdk-interfaces

## Supported Android Versions

Android API 19 - 30


## Integration

Just take the maven repository:

```kt
allprojects {
        repositories {
            jcenter()
            maven { url "https://jitpack.io" }
        }
   }
   dependencies {
        implementation 'com.github.ChickenHook:RestrictionBypass:1.0'
   }```

Or take the prebuilt aar library: [restrictionbypass.aar](prebuild/restrictionbypass.aar)


## Examples

#### getDeclaredField(...)

Original reflection call

```kt
        Class.forName("android.app.ActivityThread").getDeclaredField(
            "mResourcesManager"
        )
```

Call with RestrictionBypass

```kt
            RestrictionBypass.getDeclaredField(
                Class.forName("android.app.ActivityThread"),
                "mResourcesManager"

            )
```

#### getMethod(...)

Original reflection call


```kt
        Class.forName("android.app.ActivityThread").getMethod(
            "getPackageInfo", String::class.java, Class.forName("android.content.res.CompatibilityInfo"), Integer.TYPE
        )
```
Call with RestrictionBypass

```kt
            RestrictionBypass.getMethod(
                Class.forName("android.app.ActivityThread"),
                "getPackageInfo", String::class.java, Class.forName("android.content.res.CompatibilityInfo"), Integer.TYPE
            )
```

#### getDeclaredMethod(...)
Original reflection call

```kt
        Class.forName("android.app.ActivityThread").getDeclaredMethod(
            "getPackageInfo", String::class.java, Class.forName("android.content.res.CompatibilityInfo"), Integer.TYPE
        )
```
Call with RestrictionBypass

```kt
            RestrictionBypass.getDeclaredMethod(
                Class.forName("android.app.ActivityThread"),
                "getPackageInfo", String::class.java, Class.forName("android.content.res.CompatibilityInfo"), Integer.TYPE
            )
```

## Troubleshooting