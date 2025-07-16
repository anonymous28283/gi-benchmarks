package com.thealgorithms.matrix;



import com.thealgorithms.matrix.utils.MatrixUtil;



public final class MirrorOfMatrix {
    private MirrorOfMatrix() {
    }

    public static double[][] mirrorMatrix(final double[][] originalMatrix) {
        MatrixUtil.validateInputMatrix(originalMatrix);

        int numRows = originalMatrix.length;
        int numCols = originalMatrix[0].length;

        double[][] mirroredMatrix = new double[numRows][numCols];

        for (int i = 0; i < numRows; i++) {
            mirroredMatrix[i] = MatrixUtil.reverseRow(originalMatrix[i]);
        }
        return mirroredMatrix;
    }
}
