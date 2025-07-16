package com.thealgorithms.conversions;


public final class TurkishToLatinConversion {
    private TurkishToLatinConversion() {
    }


    public static String convertTurkishToLatin(String param) {
        char[] turkishChars = new char[] {
            0x131,
            0x130,
            0xFC,
            0xDC,
            0xF6,
            0xD6,
            0x15F,
            0x15E,
            0xE7,
            0xC7,
            0x11F,
            0x11E,
        };
        char[] latinChars = new char[] {
            'i',
            'I',
            'u',
            'U',
            'o',
            'O',
            's',
            'S',
            'c',
            'C',
            'g',
            'G',
        };
        for (int i = 0; i < turkishChars.length; i++) {
            param = param.replaceAll(String.valueOf(turkishChars[i]), String.valueOf(latinChars[i]));
        }
        return param;
    }
}
