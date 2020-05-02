package org.chickenhook.restrictionbypass.helpers;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import java.lang.reflect.Field;

public class Reflection {


    /**
     * Retrieve a member of the given object
     * @param obj containing the member
     * @param field the member name
     * @param <T> the type of the member
     * @return the member
     * @throws NoSuchFieldException when field was found
     * @throws IllegalAccessException when field was not accessible
     */
    public static @Nullable
    <T> T getReflective(@NonNull Object obj, @NonNull String field) throws NoSuchFieldException, IllegalAccessException {
        return getReflective(obj, obj.getClass(), field);
    }

    /**
     * Retrieve a member of the given object
     * @param obj containing the member (can be null on static field)
     * @param cls class of a super type
     * @param field the member name
     * @param <T> the type of the member
     * @return the member
     * @throws NoSuchFieldException when field was found
     * @throws IllegalAccessException when field was not accessible
     */
    public static @Nullable
    <T> T getReflective(@Nullable Object obj, @NonNull Class<?> cls, @NonNull String field) throws NoSuchFieldException, IllegalAccessException {
        Field f = cls.getDeclaredField(field);
        f.setAccessible(true);
        return (T) f.get(obj);
    }



    /**
     * Set a member of the given object
     * @param obj containing the member
     * @param field the member name
     * @param value the value to be set
     * @throws NoSuchFieldException when field was found
     * @throws IllegalAccessException when field was not accessible
     */
    public static @Nullable
    void setReflective(@NonNull Object obj, @NonNull String field, @Nullable Object value) throws NoSuchFieldException, IllegalAccessException {
        setReflective(obj, obj.getClass(), field, value);
    }

    /**
     * Set a member of the given object
     * @param obj containing the member
     * @param cls super class of the obj
     * @param field the member name
     * @param value the value to be set
     * @throws NoSuchFieldException when field was found
     * @throws IllegalAccessException when field was not accessible
     */
    public static @Nullable
    void setReflective(@Nullable Object obj, @NonNull Class<?> cls, @NonNull String field, @Nullable Object value) throws NoSuchFieldException, IllegalAccessException {
        Field f = cls.getDeclaredField(field);
        f.setAccessible(true);
        f.set(obj, value);
    }
}
