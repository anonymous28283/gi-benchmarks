package com.thealgorithms.matrix;


public final class SolveSystem {
    private SolveSystem() {
    }


    public static double[] solveSystem(double[][] matrix, double[] constants) {
        final double tol = 0.00000001;
        for (int k = 0; k < matrix.length - 1; k++) {

            double maxVal = Math.abs(matrix[k][k]);
            int maxIdx = k;
            for (int j = k + 1; j < matrix.length; j++) {
                if (Math.abs(matrix[j][k]) > maxVal) {
                    maxVal = matrix[j][k];
                    maxIdx = j;
                }
            }
            if (Math.abs(maxVal) < tol) {

                continue;
            }

            double[] temp = matrix[k];
            matrix[k] = matrix[maxIdx];
            matrix[maxIdx] = temp;
            double tempConst = constants[k];
            constants[k] = constants[maxIdx];
            constants[maxIdx] = tempConst;
            for (int i = k + 1; i < matrix.length; i++) {

                matrix[i][k] /= matrix[k][k];
                for (int j = k + 1; j < matrix.length; j++) {
                    matrix[i][j] -= matrix[i][k] * matrix[k][j];
                }
                constants[i] -= matrix[i][k] * constants[k];
            }
        }

        double[] x = new double[constants.length];
        System.arraycopy(constants, 0, x, 0, constants.length);
        for (int i = matrix.length - 1; i >= 0; i--) {
            double sum = 0;
            for (int j = i + 1; j < matrix.length; j++) {
                sum += matrix[i][j] * x[j];
            }
            x[i] = constants[i] - sum;
            if (Math.abs(matrix[i][i]) > tol) {
                x[i] /= matrix[i][i];
            } else {
                throw new IllegalArgumentException("Matrix was found to be singular");
            }
        }
        return x;
    }
}
