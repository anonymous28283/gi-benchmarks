package com.thealgorithms.backtracking;

import static java.util.Collections.singletonList;
import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import org.junit.jupiter.api.Test;

public class NQueensTest {

    @Test
    public void testNQueens1() {
        List<List<String>> expected = singletonList(singletonList("Q"));
        assertEquals(expected, NQueens.getNQueensArrangements(1));
    }

    @Test
    public void testNQueens2() {
        List<List<String>> expected = new ArrayList<>();
        assertEquals(expected, NQueens.getNQueensArrangements(2));
    }

    @Test
    public void testNQueens3() {
        List<List<String>> expected = new ArrayList<>();
        assertEquals(expected, NQueens.getNQueensArrangements(3));
    }

    @Test
    public void testNQueens4() {
        List<List<String>> expected = Arrays.asList(Arrays.asList(".Q..", "...Q", "Q...", "..Q."), Arrays.asList("..Q.", "Q...", "...Q", ".Q.."));
        assertEquals(expected, NQueens.getNQueensArrangements(4));
    }

    @Test
    public void testNQueens5() {

        List<List<String>> result = NQueens.getNQueensArrangements(5);
        assertEquals(10, result.size());
    }

    @Test
    public void testNQueens6() {
        List<List<String>> result = NQueens.getNQueensArrangements(6);
        assertEquals(4, result.size());
    }
}
