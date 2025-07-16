package com.thealgorithms.matrix.matrixexponentiation;

import com.thealgorithms.matrix.utils.MatrixUtil;
import java.math.BigDecimal;


public final class Fibonacci {
    private Fibonacci() {
    }


    private static final BigDecimal ONE = BigDecimal.valueOf(1);
    private static final BigDecimal ZERO = BigDecimal.valueOf(0);

    private static final BigDecimal[][] FIB_MATRIX = {{ONE, ONE}, {ONE, ZERO}};
    private static final BigDecimal[][] IDENTITY_MATRIX = {{ONE, ZERO}, {ZERO, ONE}};


    public static BigDecimal[][] fib(int n) {
        if (n == 0) {
            return IDENTITY_MATRIX;
        } else {
            BigDecimal[][] cachedResult = fib(n / 2);
            BigDecimal[][] matrixExpResult = MatrixUtil.multiply(cachedResult, cachedResult).get();
            if (n % 2 == 0) {
                return matrixExpResult;
            } else {
                return MatrixUtil.multiply(FIB_MATRIX, matrixExpResult).get();
            }
        }
    }
}
