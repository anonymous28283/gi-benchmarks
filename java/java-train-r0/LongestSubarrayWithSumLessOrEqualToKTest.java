package com.thealgorithms.slidingwindow;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;


public class LongestSubarrayWithSumLessOrEqualToKTest {


    @Test
    public void testLongestSubarrayWithSumLEK() {
        assertEquals(3, LongestSubarrayWithSumLessOrEqualToK.longestSubarrayWithSumLEK(new int[] {1, 2, 3, 4}, 6));
        assertEquals(4, LongestSubarrayWithSumLessOrEqualToK.longestSubarrayWithSumLEK(new int[] {1, 2, 3, 4}, 10));
        assertEquals(2, LongestSubarrayWithSumLessOrEqualToK.longestSubarrayWithSumLEK(new int[] {5, 1, 2, 3}, 5));
        assertEquals(0, LongestSubarrayWithSumLessOrEqualToK.longestSubarrayWithSumLEK(new int[] {1, 2, 3}, 0));
    }
}
