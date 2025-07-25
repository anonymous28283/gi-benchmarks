package com.thealgorithms.bitmanipulation;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

public class ParityCheckTest {
    @Test
    public void testIsOddParity() {
        assertTrue(ParityCheck.checkParity(5));
        assertFalse(ParityCheck.checkParity(7));
        assertFalse(ParityCheck.checkParity(8));
    }
}
