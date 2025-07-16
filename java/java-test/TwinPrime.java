package com.thealgorithms.maths;


import com.thealgorithms.maths.Prime.PrimeCheck;

public final class TwinPrime {
    private TwinPrime() {
    }


    static int getTwinPrime(int inputNumber) {



        if (PrimeCheck.isPrime(inputNumber) && PrimeCheck.isPrime(inputNumber + 2)) {
            return inputNumber + 2;
        }


        return -1;
    }
}
