package com.thealgorithms.maths;

import static com.thealgorithms.maths.GoldbachConjecture.getPrimeSum;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.Test;

public class GoldbachConjectureTest {
    @Test
    void testValidEvenNumbers() {
        assertEquals(new GoldbachConjecture.Result(3, 7), getPrimeSum(10));
        assertEquals(new GoldbachConjecture.Result(5, 7), getPrimeSum(12));
        assertEquals(new GoldbachConjecture.Result(3, 11), getPrimeSum(14));
        assertEquals(new GoldbachConjecture.Result(5, 13), getPrimeSum(18));
    }
    @Test
    void testInvalidOddNumbers() {
        assertThrows(IllegalArgumentException.class, () -> getPrimeSum(7));
        assertThrows(IllegalArgumentException.class, () -> getPrimeSum(15));
    }
    @Test
    void testLesserThanTwo() {
        assertThrows(IllegalArgumentException.class, () -> getPrimeSum(1));
        assertThrows(IllegalArgumentException.class, () -> getPrimeSum(2));
        assertThrows(IllegalArgumentException.class, () -> getPrimeSum(-5));
        assertThrows(IllegalArgumentException.class, () -> getPrimeSum(-26));
    }
}
