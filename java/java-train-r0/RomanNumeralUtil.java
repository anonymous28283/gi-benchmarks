package com.thealgorithms.maths;


public final class RomanNumeralUtil {
    private RomanNumeralUtil() {
    }

    private static final int MIN_VALUE = 1;
    private static final int MAX_VALUE = 5999;

    private static final String[] RN_M = {
        "",
        "M",
        "MM",
        "MMM",
        "MMMM",
        "MMMMM",
    };

    private static final String[] RN_C = {
        "",
        "C",
        "CC",
        "CCC",
        "CD",
        "D",
        "DC",
        "DCC",
        "DCCC",
        "CM",
    };

    private static final String[] RN_X = {
        "",
        "X",
        "XX",
        "XXX",
        "XL",
        "L",
        "LX",
        "LXX",
        "LXXX",
        "XC",
    };

    private static final String[] RN_I = {
        "",
        "I",
        "II",
        "III",
        "IV",
        "V",
        "VI",
        "VII",
        "VIII",
        "IX",
    };

    public static String generate(int number) {
        if (number < MIN_VALUE || number > MAX_VALUE) {
            throw new IllegalArgumentException(String.format("The number must be in the range [%d, %d]", MIN_VALUE, MAX_VALUE));
        }

        return (RN_M[number / 1000] + RN_C[number % 1000 / 100] + RN_X[number % 100 / 10] + RN_I[number % 10]);
    }
}
