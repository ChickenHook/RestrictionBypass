package org.chickenhook.restrictionbypass.helpers;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import java.lang.reflect.Field;

public class Reflection {

    public static @Nullable
    <T> T getReflective(@NonNull Object obj, @NonNull String field) throws NoSuchFieldException, IllegalAccessException {
        return getReflective(obj, obj.getClass(), field);
    }

    public static @Nullable
    <T> T getReflective(@Nullable Object obj, @NonNull Class<?> cls, @NonNull String field) throws NoSuchFieldException, IllegalAccessException {
        Field f = cls.getDeclaredField(field);
        f.setAccessible(true);
        return (T) f.get(obj);
    }
}
