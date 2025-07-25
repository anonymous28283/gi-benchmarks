package com.thealgorithms.bitmanipulation;


public final class ParityCheck {
    private ParityCheck() {
    }


    public static boolean checkParity(int n) {
        int count = 0;
        while (n > 0) {
            count += n & 1;
            n >>= 1;
        }
        return count % 2 == 0;
    }
}
