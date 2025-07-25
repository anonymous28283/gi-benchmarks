package com.thealgorithms.maths;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import java.util.stream.Stream;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.MethodSource;


class CatalanNumbersTest {


    static Stream<Object[]> catalanNumbersProvider() {
        return Stream.of(new Object[] {0, 1}, new Object[] {1, 1}, new Object[] {2, 2}, new Object[] {3, 5}, new Object[] {4, 14}, new Object[] {5, 42}, new Object[] {6, 132}, new Object[] {7, 429}, new Object[] {8, 1430}, new Object[] {9, 4862}, new Object[] {10, 16796});
    }


    @ParameterizedTest
    @MethodSource("catalanNumbersProvider")
    void testCatalanNumbers(int input, int expected) {
        assertEquals(expected, CatalanNumbers.catalan(input), () -> String.format("Catalan number for input %d should be %d", input, expected));
    }


    @Test
    void testIllegalInput() {
        assertThrows(IllegalArgumentException.class, () -> CatalanNumbers.catalan(-1));
        assertThrows(IllegalArgumentException.class, () -> CatalanNumbers.catalan(-5));
    }
}
