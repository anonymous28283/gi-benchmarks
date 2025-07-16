package com.thealgorithms.maths;

import java.util.ArrayList;


public final class VampireNumber {

    private VampireNumber() {
    }

    static boolean isVampireNumber(int a, int b, boolean ignorePseudoVampireNumbers) {

        if (ignorePseudoVampireNumbers && String.valueOf(a).length() != String.valueOf(b).length()) {
            return false;
        }

        String mulDigits = splitIntoSortedDigits(a * b);
        String factorDigits = splitIntoSortedDigits(a, b);

        return mulDigits.equals(factorDigits);
    }


    static String splitIntoSortedDigits(int... nums) {

        ArrayList<Integer> digits = new ArrayList<>();
        for (int num : nums) {
            while (num > 0) {
                digits.add(num % 10);
                num /= 10;
            }
        }


        StringBuilder res = new StringBuilder();
        digits.stream().sorted().forEach(res::append);
        return res.toString();
    }
}
