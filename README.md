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

Just include the library as explained in the Integration chapter.
The BypassProvider will automatically unseal your process and allow you to access hidden api.

## Troubleshooting

Please create a bug report if you find any issues. This chapter will be updated then.


## Donate

If you're happy with my library please order me a cup of coffee ;) Thanks.

[![Donate with PayPal](https://raw.githubusercontent.com/stefan-niedermann/paypal-donate-button/master/paypal-donate-button.png)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=8UH5MBVYM3J36)