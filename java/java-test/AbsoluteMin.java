package com.thealgorithms.maths;

import java.util.Arrays;

public final class AbsoluteMin {
    private AbsoluteMin() {
    }


    public static int getMinValue(int... numbers) {
        if (numbers.length == 0) {
            throw new IllegalArgumentException("Numbers array cannot be empty");
        }

        var absMinWrapper = new Object() { int value = numbers[0]; };

        Arrays.stream(numbers).skip(1).filter(number -> Math.abs(number) <= Math.abs(absMinWrapper.value)).forEach(number -> absMinWrapper.value = Math.min(absMinWrapper.value, number));

        return absMinWrapper.value;
    }
}
