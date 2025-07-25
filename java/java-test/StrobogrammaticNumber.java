package com.thealgorithms.maths;

import java.util.HashMap;
import java.util.Map;


public class StrobogrammaticNumber {

    public boolean isStrobogrammatic(String number) {
        Map<Character, Character> strobogrammaticMap = new HashMap<>();
        strobogrammaticMap.put('0', '0');
        strobogrammaticMap.put('1', '1');
        strobogrammaticMap.put('6', '9');
        strobogrammaticMap.put('8', '8');
        strobogrammaticMap.put('9', '6');

        int left = 0;
        int right = number.length() - 1;

        while (left <= right) {
            char leftChar = number.charAt(left);
            char rightChar = number.charAt(right);

            if (!strobogrammaticMap.containsKey(leftChar) || strobogrammaticMap.get(leftChar) != rightChar) {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }
}
