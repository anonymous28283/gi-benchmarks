package com.thealgorithms.slidingwindow;
import java.util.HashSet;


public final class LongestSubstringWithoutRepeatingCharacters {


    private LongestSubstringWithoutRepeatingCharacters() {
    }


    public static int lengthOfLongestSubstring(String s) {
        int maxLength = 0;
        int left = 0;
        HashSet<Character> charSet = new HashSet<>();

        for (int right = 0; right < s.length(); right++) {

            while (charSet.contains(s.charAt(right))) {
                charSet.remove(s.charAt(left));
                left++;
            }
            charSet.add(s.charAt(right));
            maxLength = Math.max(maxLength, right - left + 1);
        }

        return maxLength;
    }
}
