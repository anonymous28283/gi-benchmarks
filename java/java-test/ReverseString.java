package com.thealgorithms.strings;


public final class ReverseString {
    private ReverseString() {
    }


    public static String reverse(String str) {
        return new StringBuilder(str).reverse().toString();
    }


    public static String reverse2(String str) {
        if (str == null || str.isEmpty()) {
            return str;
        }

        char[] value = str.toCharArray();
        for (int i = 0, j = str.length() - 1; i < j; i++, j--) {
            char temp = value[i];
            value[i] = value[j];
            value[j] = temp;
        }
        return new String(value);
    }


    public static String reverse3(String string) {
        if (string.isEmpty()) {
            return string;
        }
        char[] chars = string.toCharArray();
        StringBuilder sb = new StringBuilder();
        for (int i = string.length() - 1; i >= 0; i--) {
            sb.append(chars[i]);
        }
        return sb.toString();
    }
}
