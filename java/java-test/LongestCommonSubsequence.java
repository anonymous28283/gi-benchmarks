package com.thealgorithms.dynamicprogramming;


final class LongestCommonSubsequence {

    private LongestCommonSubsequence() {
    }


    public static String getLCS(String str1, String str2) {

        if (str1 == null || str2 == null) {
            return null;
        }

        if (str1.length() == 0 || str2.length() == 0) {
            return "";
        }


        String[] arr1 = str1.split("");
        String[] arr2 = str2.split("");


        int[][] lcsMatrix = new int[arr1.length + 1][arr2.length + 1];



        for (int i = 0; i < arr1.length + 1; i++) {
            lcsMatrix[i][0] = 0;
        }
        for (int j = 1; j < arr2.length + 1; j++) {
            lcsMatrix[0][j] = 0;
        }


        for (int i = 1; i < arr1.length + 1; i++) {
            for (int j = 1; j < arr2.length + 1; j++) {

                if (arr1[i - 1].equals(arr2[j - 1])) {
                    lcsMatrix[i][j] = lcsMatrix[i - 1][j - 1] + 1;
                } else {

                    lcsMatrix[i][j] = Math.max(lcsMatrix[i - 1][j], lcsMatrix[i][j - 1]);
                }
            }
        }


        return lcsString(str1, str2, lcsMatrix);
    }


    public static String lcsString(String str1, String str2, int[][] lcsMatrix) {
        StringBuilder lcs = new StringBuilder();
        int i = str1.length();
        int j = str2.length();


        while (i > 0 && j > 0) {

            if (str1.charAt(i - 1) == str2.charAt(j - 1)) {
                lcs.append(str1.charAt(i - 1));
                i--;
                j--;
            } else if (lcsMatrix[i - 1][j] > lcsMatrix[i][j - 1]) {

                i--;
            } else {

                j--;
            }
        }

        return lcs.reverse().toString();
    }
}
