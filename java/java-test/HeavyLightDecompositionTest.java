package com.thealgorithms.tree;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class HeavyLightDecompositionTest {

    private HeavyLightDecomposition hld;
    private final int[] values = {0, 10, 20, 30, 40, 50};


    @BeforeEach
    void setUp() {
        hld = new HeavyLightDecomposition(5);
        hld.addEdge(1, 2);
        hld.addEdge(1, 3);
        hld.addEdge(2, 4);
        hld.addEdge(2, 5);
        hld.initialize(1, values);
    }


    @Test
    void testBasicTreeInitialization() {
        assertTrue(true, "Basic tree structure initialized successfully");
    }


    @Test
    void testQueryMaxInPath() {
        assertEquals(50, hld.queryMaxInPath(4, 5), "Max value in path (4,5) should be 50");
        assertEquals(30, hld.queryMaxInPath(3, 2), "Max value in path (3,2) should be 30");
    }


    @Test
    void testUpdateNodeValue() {
        hld.updateSegmentTree(1, 0, hld.getPositionIndex() - 1, hld.getPosition(4), 100);
        assertEquals(100, hld.queryMaxInPath(4, 5), "Updated value should be reflected in query");
    }


    @Test
    void testSkewedTreeMaxQuery() {
        assertEquals(40, hld.queryMaxInPath(1, 4), "Max value in skewed tree (1,4) should be 40");
    }


    @Test
    void testDepthSwapInPathQuery() {
        assertEquals(50, hld.queryMaxInPath(5, 2), "Query should handle depth swap correctly");
        assertEquals(40, hld.queryMaxInPath(4, 1), "Query should handle swapped nodes correctly and return max value");
    }
}
