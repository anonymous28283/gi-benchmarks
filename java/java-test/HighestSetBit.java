package com.thealgorithms.bitmanipulation;

import java.util.Optional;


public final class HighestSetBit {

    private HighestSetBit() {
    }


    public static Optional<Integer> findHighestSetBit(int num) {
        if (num < 0) {
            throw new IllegalArgumentException("Input cannot be negative");
        }

        if (num == 0) {
            return Optional.empty();
        }

        int position = 0;
        while (num > 0) {
            num >>= 1;
            position++;
        }

        return Optional.of(position - 1);
    }
}
