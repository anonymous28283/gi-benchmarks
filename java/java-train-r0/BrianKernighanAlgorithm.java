package com.thealgorithms.others;

import java.util.Scanner;


public final class BrianKernighanAlgorithm {
    private BrianKernighanAlgorithm() {
    }


    static int countSetBits(int num) {
        int cnt = 0;
        while (num != 0) {
            num = num & (num - 1);
            cnt++;
        }
        return cnt;
    }


    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int num = sc.nextInt();
        int setBitCount = countSetBits(num);
        System.out.println(setBitCount);
        sc.close();
    }
}
