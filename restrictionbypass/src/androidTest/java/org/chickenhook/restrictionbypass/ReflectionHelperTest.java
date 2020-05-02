package org.chickenhook.restrictionbypass;

import org.chickenhook.restrictionbypass.helpers.Reflection;
import org.junit.Test;

import static org.junit.Assert.assertSame;

public class ReflectionHelperTest {

    Object reflectiveField = new Object();

    @Test
    public void getReflective() throws Exception {
        assertSame(Reflection.getReflective(this, "reflectiveField"), reflectiveField);
    }
}
