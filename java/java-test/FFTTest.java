package com.thealgorithms.maths;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

import java.util.ArrayList;
import org.junit.jupiter.api.Test;

class FFTTest {


    @Test
    void getRealtest() {
        FFT.Complex complex = new FFT.Complex(1.0, 1.0);
        assertEquals(1.0, complex.getReal());
    }


    @Test
    void getImaginaryTest() {
        FFT.Complex complex = new FFT.Complex();
        assertEquals(0.0, complex.getImaginary());
    }


    @Test
    void addTest() {
        FFT.Complex complex1 = new FFT.Complex(1.0, 1.0);
        FFT.Complex complex2 = new FFT.Complex(2.0, 2.0);
        double add = complex1.add(complex2).getReal();
        assertEquals(3.0, add);
    }


    @Test
    void addFalseTest() {
        FFT.Complex complex1 = new FFT.Complex(1.0, 1.0);
        FFT.Complex complex2 = new FFT.Complex(2.0, 2.0);
        double add = complex1.add(complex2).getReal();
        assertNotEquals(2.0, add);
    }


    @Test
    void subtractTest() {
        FFT.Complex complex1 = new FFT.Complex(2.0, 2.0);
        FFT.Complex complex2 = new FFT.Complex(1.0, 1.0);
        double sub = complex1.subtract(complex2).getReal();
        assertEquals(1.0, sub);
    }


    @Test
    void multiplyWithComplexTest() {
        FFT.Complex complex1 = new FFT.Complex(2.0, 2.0);
        FFT.Complex complex2 = new FFT.Complex(1.0, 1.0);
        double multiReal = complex1.multiply(complex2).getReal();
        double multiImg = complex1.multiply(complex2).getImaginary();
        assertEquals(0.0, multiReal);
        assertEquals(4.0, multiImg);
    }


    @Test
    void multiplyWithScalarTest() {
        FFT.Complex complex1 = new FFT.Complex(2.0, 2.0);

        double multiReal = complex1.multiply(2).getReal();
        double multiImg = complex1.multiply(3).getImaginary();
        assertEquals(4.0, multiReal);
        assertEquals(6.0, multiImg);
    }


    @Test
    void conjugateTest() {
        FFT.Complex complex1 = new FFT.Complex(2.0, 2.0);
        double conReal = complex1.conjugate().getReal();
        double conImg = complex1.conjugate().getImaginary();
        assertEquals(2.0, conReal);
        assertEquals(-2.0, conImg);
    }


    @Test
    void abs() {
        FFT.Complex complex1 = new FFT.Complex(2.0, 3.0);
        double abs = complex1.abs();
        assertEquals(Math.sqrt(13), abs);
    }


    @Test
    void divideWithComplexTest() {
        FFT.Complex complex1 = new FFT.Complex(2.0, 2.0);
        FFT.Complex complex2 = new FFT.Complex(1.0, 2.0);
        double divReal = complex1.divide(complex2).getReal();
        double divImg = complex1.divide(complex2).getImaginary();
        assertEquals(1.2, divReal);
        assertEquals(-0.4, divImg);
    }


    @Test
    void divideWithScalarTest() {
        FFT.Complex complex1 = new FFT.Complex(2.0, 2.0);
        double divReal = complex1.divide(2).getReal();
        double divImg = complex1.divide(2).getImaginary();
        assertEquals(1, divReal);
        assertEquals(1, divImg);
    }




    @Test
    void fft() {
        ArrayList<FFT.Complex> arr = new ArrayList<FFT.Complex>();
        FFT.Complex complex1 = new FFT.Complex(2.0, 2.0);
        FFT.Complex complex2 = new FFT.Complex(1.0, 3.0);
        FFT.Complex complex3 = new FFT.Complex(3.0, 1.0);
        FFT.Complex complex4 = new FFT.Complex(2.0, 2.0);

        arr.add(complex1);
        arr.add(complex2);
        arr.add(complex3);
        arr.add(complex4);
        arr = FFT.fft(arr, false);
        double realV1 = arr.get(0).getReal();
        double realV2 = arr.get(2).getReal();
        double imgV1 = arr.get(0).getImaginary();
        double imgV2 = arr.get(2).getImaginary();
        assertEquals(8.0, realV1);
        assertEquals(2.0, realV2);
        assertEquals(8.0, imgV1);
        assertEquals(-2.0, imgV2);
    }
}
