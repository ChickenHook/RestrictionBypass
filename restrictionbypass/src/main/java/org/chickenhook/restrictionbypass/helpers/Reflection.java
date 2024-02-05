package org.chickenhook.restrictionbypass.helpers;

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
    public static
    <T> T getReflective(Object obj, String field) throws NoSuchFieldException, IllegalAccessException {
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
    public static
    <T> T getReflective(Object obj, Class<?> cls, String field) throws NoSuchFieldException, IllegalAccessException {
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
    public static
    void setReflective(Object obj, String field, Object value) throws NoSuchFieldException, IllegalAccessException {
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
    public static
    void setReflective(Object obj, Class<?> cls, String field, Object value) throws NoSuchFieldException, IllegalAccessException {
        Field f = cls.getDeclaredField(field);
        f.setAccessible(true);
        f.set(obj, value);
    }
}
