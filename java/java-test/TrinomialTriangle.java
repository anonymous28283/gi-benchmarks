package com.thealgorithms.maths;


public final class TrinomialTriangle {
    private TrinomialTriangle() {
    }

    public static int trinomialValue(int n, int k) {
        if (n == 0 && k == 0) {
            return 1;
        }

        if (k < -n || k > n) {
            return 0;
        }

        return (trinomialValue(n - 1, k - 1) + trinomialValue(n - 1, k) + trinomialValue(n - 1, k + 1));
    }

    public static void printTrinomial(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = -i; j <= 0; j++) {
                System.out.print(trinomialValue(i, j) + " ");
            }

            for (int j = 1; j <= i; j++) {
                System.out.print(trinomialValue(i, j) + " ");
            }

            System.out.println();
        }
    }

    public static void main(String[] argc) {
        int n = 6;
        printTrinomial(n);
    }
}
