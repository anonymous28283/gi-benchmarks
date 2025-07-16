package com.thealgorithms.strings.zigZagPattern;

final class ZigZagPattern {

    private ZigZagPattern() {
    }


    public static String encode(String s, int numRows) {
        if (numRows < 2 || s.length() < numRows) {
            return s;
        }

        StringBuilder result = new StringBuilder(s.length());
        int cycleLength = 2 * numRows - 2;

        for (int row = 0; row < numRows; row++) {
            for (int j = row; j < s.length(); j += cycleLength) {
                result.append(s.charAt(j));

                if (row > 0 && row < numRows - 1) {
                    int diagonal = j + cycleLength - 2 * row;
                    if (diagonal < s.length()) {
                        result.append(s.charAt(diagonal));
                    }
                }
            }
        }

        return result.toString();
    }
}
