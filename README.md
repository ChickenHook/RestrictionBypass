# RestrictionBypass
Android API restriction bypass for all Android Versions

## Description

Small library to access hidden API restricted by https://developer.android.com/distribute/best-practices/develop/restrictions-non-sdk-interfaces

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
        implementation 'com.github.ChickenHook:RestrictionBypass:1.0'
   }
```
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

Please create a bug report if you find any issues. This chapter will be updated then.