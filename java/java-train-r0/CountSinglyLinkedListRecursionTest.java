package com.thealgorithms.datastructures.lists;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class CountSinglyLinkedListRecursionTest {

    private CountSinglyLinkedListRecursion list;

    @BeforeEach
    public void setUp() {
        list = new CountSinglyLinkedListRecursion();
    }

    @Test
    public void testCountEmptyList() {

        assertEquals(0, list.count(), "Count of an empty list should be 0.");
    }

    @Test
    public void testCountSingleElementList() {

        list.insert(1);
        assertEquals(1, list.count(), "Count of a single-element list should be 1.");
    }

    @Test
    public void testCountMultipleElements() {

        for (int i = 1; i <= 5; i++) {
            list.insert(i);
        }
        assertEquals(5, list.count(), "Count of a list with 5 elements should be 5.");
    }

    @Test
    public void testCountWithDuplicateElements() {

        list.insert(1);
        list.insert(2);
        list.insert(2);
        list.insert(3);
        list.insert(3);
        assertEquals(5, list.count(), "Count of a list with duplicate elements should match total node count.");
    }
}
