package org.chickenhook.restrictionbypass.app

import junit.framework.Assert.assertNotNull
import org.chickenhook.restrictionbypass.RestrictionBypass
import org.junit.Test

class KotlinExamples {

    @Test(expected = NoSuchFieldException::class)  // will fail due to api restrictions
    fun accessResourcesManagerWithoutBypass() {
        Class.forName("android.app.ActivityThread").getDeclaredField(
            "mResourcesManager"
        )
    }

    @Test
    fun accessResourcesManagerWithBypass() {
        assertNotNull(
            RestrictionBypass.getDeclaredField(
                Class.forName("android.app.ActivityThread"),
                "mResourcesManager"

            )
        )
    }

    @Test(expected = NoSuchMethodException::class)  // will fail due to api restrictions
    fun invokeGetPackageInfoWithoutBypass() {
        Class.forName("android.app.ActivityThread").getMethod(
            "getPackageInfo", String::class.java, Class.forName("android.content.res.CompatibilityInfo"), Integer.TYPE
        )
    }

    @Test
    fun invokeGetPackageInfoWithBypass() {
        assertNotNull(
            RestrictionBypass.getMethod(
                Class.forName("android.app.ActivityThread"),
                "getPackageInfo", String::class.java, Class.forName("android.content.res.CompatibilityInfo"), Integer.TYPE
            )
        )
    }
}