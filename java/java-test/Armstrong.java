package com.thealgorithms.maths;


public class Armstrong {


    public boolean isArmstrong(int number) {
        if (number < 0) {
            return false;
        }
        long sum = 0;
        int totalDigits = (int) Math.log10(number) + 1;
        long originalNumber = number;

        while (originalNumber > 0) {
            long digit = originalNumber % 10;
            sum += (long) Math.pow(digit, totalDigits);
            originalNumber /= 10;
        }

        return sum == number;
    }
}
