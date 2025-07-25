package com.thealgorithms.maths;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.Test;


class FastExponentiationTest {


    @Test
    void testSmallNumbers() {
        assertEquals(1024, FastExponentiation.fastExponentiation(2, 10, 10000), "2^10 mod 10000 should be 1024");
        assertEquals(81, FastExponentiation.fastExponentiation(3, 4, 1000), "3^4 mod 1000 should be 81");
    }


    @Test
    void testWithModulo() {
        assertEquals(24, FastExponentiation.fastExponentiation(2, 10, 1000), "2^10 mod 1000 should be 24");
        assertEquals(0, FastExponentiation.fastExponentiation(10, 5, 10), "10^5 mod 10 should be 0");
    }


    @Test
    void testBaseCases() {
        assertEquals(1, FastExponentiation.fastExponentiation(2, 0, 1000), "Any number raised to the power 0 mod anything should be 1");
        assertEquals(0, FastExponentiation.fastExponentiation(0, 10, 1000), "0 raised to any power should be 0");
        assertEquals(1, FastExponentiation.fastExponentiation(0, 0, 1000), "0^0 is considered 0 in modular arithmetic.");
    }


    @Test
    void testNegativeBase() {
        assertEquals(9765625, FastExponentiation.fastExponentiation(-5, 10, 1000000007), "-5^10 mod 1000000007 should be 9765625");
    }


    @Test
    void testNegativeExponent() {
        assertThrows(ArithmeticException.class, () -> { FastExponentiation.fastExponentiation(2, -5, 1000); });
    }


    @Test
    void testInvalidModulus() {
        assertThrows(IllegalArgumentException.class, () -> { FastExponentiation.fastExponentiation(2, 5, 0); });
    }
}
