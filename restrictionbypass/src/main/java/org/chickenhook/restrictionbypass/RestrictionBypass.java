package org.chickenhook.restrictionbypass;

import android.os.Build;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class RestrictionBypass {
    public static Method getDeclaredMethod(Object clazz, String name, Class<?>... args) throws NoSuchMethodException, InvocationTargetException, IllegalAccessException {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
            return NativeReflectionBypass.getDeclaredMethod(clazz, name, args);
        } else {
            Method getDeclaredMethod = Class.class.getMethod(
                    "getDeclaredMethod",
                    String.class, Class[].class
            );
            return (Method) getDeclaredMethod.invoke(clazz, name, args);
        }
    }

    public static Method getMethod(Object clazz, String name, Class<?>... args) throws NoSuchMethodException, InvocationTargetException, IllegalAccessException {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
            return NativeReflectionBypass.getMethod(clazz, name, args);
        } else {
            Method getDeclaredMethod = Class.class.getMethod(
                    "getMethod",
                    String.class, Class[].class
            );
            return (Method) getDeclaredMethod.invoke(clazz, name, args);
        }
    }


    public static Field getDeclaredField(Class obj, String name) throws NoSuchMethodException, InvocationTargetException, IllegalAccessException {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
            return NativeReflectionBypass.getDeclaredField(obj, name);
        } else {
            Method getDeclaredField = Class.class.getMethod("getDeclaredField", String.class);
            return (Field) getDeclaredField.invoke(obj, name);
        }
    }
}
