package com.thealgorithms.maths;

import static com.thealgorithms.maths.Prime.PrimeCheck.isPrime;



public final class GoldbachConjecture {
    private GoldbachConjecture() {
    }
    public record Result(int number1, int number2) {
    }

    public static Result getPrimeSum(int number) {
        if (number <= 2 || number % 2 != 0) {
            throw new IllegalArgumentException("Number must be even and greater than 2.");
        }

        for (int i = 0; i <= number / 2; i++) {
            if (isPrime(i) && isPrime(number - i)) {
                return new Result(i, number - i);
            }
        }
        throw new IllegalStateException("No valid prime sum found.");
    }
}
