package com.thealgorithms.maths;

import java.util.Arrays;


public final class SieveOfEratosthenes {
    private SieveOfEratosthenes() {
    }

    private static void checkInput(int n) {
        if (n <= 0) {
            throw new IllegalArgumentException("n must be positive.");
        }
    }

    private static Type[] sievePrimesTill(int n) {
        checkInput(n);
        Type[] isPrimeArray = new Type[n + 1];
        Arrays.fill(isPrimeArray, Type.PRIME);
        isPrimeArray[0] = Type.NOT_PRIME;
        isPrimeArray[1] = Type.NOT_PRIME;

        double cap = Math.sqrt(n);
        for (int i = 2; i <= cap; i++) {
            if (isPrimeArray[i] == Type.PRIME) {
                for (int j = 2; i * j <= n; j++) {
                    isPrimeArray[i * j] = Type.NOT_PRIME;
                }
            }
        }
        return isPrimeArray;
    }

    private static int countPrimes(Type[] isPrimeArray) {
        return (int) Arrays.stream(isPrimeArray).filter(element -> element == Type.PRIME).count();
    }

    private static int[] extractPrimes(Type[] isPrimeArray) {
        int numberOfPrimes = countPrimes(isPrimeArray);
        int[] primes = new int[numberOfPrimes];
        int primeIndex = 0;
        for (int curNumber = 0; curNumber < isPrimeArray.length; ++curNumber) {
            if (isPrimeArray[curNumber] == Type.PRIME) {
                primes[primeIndex++] = curNumber;
            }
        }
        return primes;
    }


    public static int[] findPrimesTill(int n) {
        return extractPrimes(sievePrimesTill(n));
    }

    private enum Type {
        PRIME,
        NOT_PRIME,
    }
}
