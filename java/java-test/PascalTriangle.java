package com.thealgorithms.maths;

public final class PascalTriangle {
    private PascalTriangle() {
    }



    public static int[][] pascal(int n) {

        int[][] arr = new int[n][n];

        for (int line = 0; line < n; line++) {

            for (int i = 0; i <= line; i++) {

                if (line == i || i == 0) {
                    arr[line][i] = 1;
                } else {
                    arr[line][i] = arr[line - 1][i - 1] + arr[line - 1][i];
                }
            }
        }

        return arr;
    }
}
