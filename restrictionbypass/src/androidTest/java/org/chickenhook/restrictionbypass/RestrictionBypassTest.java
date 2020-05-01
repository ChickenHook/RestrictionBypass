package org.chickenhook.restrictionbypass;

import org.junit.Test;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import static junit.framework.TestCase.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertSame;

public class RestrictionBypassTest {

    Object testField1 = new Object();
    Object testField2 = null;

    Object getTestField1() {
        return testField1;
    }

    public int add(int a, int b) {
        return a + b;
    }

    @Test
    public void getDeclaredMethod() throws Exception {
        Method m = RestrictionBypass.getDeclaredMethod(this.getClass(), "getTestField1");
        assertSame(testField1, m.invoke(this));
    }

    @Test
    public void getDeclaredMethodAdd() throws Exception {
        Method m = RestrictionBypass.getDeclaredMethod(this.getClass(), "add", int.class, int.class);
        assertSame(5, m.invoke(this, 1,4));
    }


    @Test
    public void getMethod() throws Exception {
        Method m = RestrictionBypass.getMethod(this.getClass(), "getTestField1");
        assertNull(m);
    }
    @Test
    public void getMethodAdd() throws Exception {
        Method m = RestrictionBypass.getMethod(this.getClass(), "add", int.class, int.class);
        assertSame(5, m.invoke(this, 1,4));
    }
    @Test
    public void getDeclaredField() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
        Field f = RestrictionBypass.getDeclaredField(this.getClass(), "testField1");
        assertNotNull(f);
        assertSame(f.get(this), testField1);
    }

    @Test
    public void getDeclaredNullField() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
        Field f = RestrictionBypass.getDeclaredField(this.getClass(), "testField2");
        assertNotNull(f);
        assertSame(f.get(this), testField2);
    }
}