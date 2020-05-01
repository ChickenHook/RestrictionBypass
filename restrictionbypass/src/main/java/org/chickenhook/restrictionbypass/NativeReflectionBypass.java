package org.chickenhook.restrictionbypass;

import java.lang.reflect.Field;
import java.lang.reflect.Method;

class NativeReflectionBypass {

    public static native Method getDeclaredMethod(Object recv, String name, Class<?>[] parameterTypes);
    public static native Method getMethod(Object recv, String name, Class<?>[] parameterTypes);
    public static native Field getDeclaredField(Object recv, String name);

    static {
        System.loadLibrary("nrb");
    }
}
