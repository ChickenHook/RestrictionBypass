# RestrictionBypass
[![Download](https://jitpack.io/v/ChickenHook/RestrictionBypass.svg)](https://jitpack.io/#ChickenHook/RestrictionBypass)

Android API restriction bypass for all Android Versions

## Description

** NEW VIDEO DESCRIPTION UPLOADED**

[![RestrictionBypass](https://img.youtube.com/vi/91aobT-RHzY/0.jpg)](https://www.youtube.com/watch?v=91aobT-RHzY "RestrictionBypass")


Small library to access hidden API restricted by https://developer.android.com/distribute/best-practices/develop/restrictions-non-sdk-interfaces

More technical details can be found: https://androidreverse.org/2023/02/21/android-api-restriction-bypass-for-all-android-versions/

## Supported Android Versions

Android API 19 - 33


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

Just include the library as explained in the Integration chapter.
The BypassProvider will automatically unseal your process and allow you to access hidden api.

## Troubleshooting

Please create a bug report if you find any issues. This chapter will be updated then.

## R8 / Proguard
The specific rules are [already bundled](restrictionbypass/consumer-rules.pro) into the aar which can be interpreted by R8 automatically.

## Donate

If you're happy with my library please order me a cup of coffee ;) Thanks.

[![Donate with PayPal](https://raw.githubusercontent.com/stefan-niedermann/paypal-donate-button/master/paypal-donate-button.png)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=8UH5MBVYM3J36)

or

bc1qvll2mp5ndwd4sgycu4ad2ken4clhjac7mdlcaj

## Other Projects

| Project                                                                                 | Description                                                                       |
|-----------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------|
| [ChickenHook](https://github.com/ChickenHook/ChickenHook)                               | A linux / android / MacOS hooking framework                                       |
| [BinderHook](https://github.com/ChickenHook/BinderHook)                                 | Library intended to hook Binder interface and manipulate events                   |
| [RestrictionBypass](https://github.com/ChickenHook/RestrictionBypass)                   | Android API restriction bypass for all Android Versions                           |
| [AndroidManifestBypass](https://github.com/ChickenHook/AndroidManifestBypass)           | Android API restriction bypass for all Android Versions                           |
| [AndroidSystemServicePenetration](https://github.com/ChickenHook/AndroidSystemServicePenetration) | A project where we document and list Exploits and Bugs of Android System services |
| ..                                                                                      |                                                                                   |
