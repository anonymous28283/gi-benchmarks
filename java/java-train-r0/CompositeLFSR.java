package com.thealgorithms.ciphers.a5;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;


public abstract class CompositeLFSR implements BaseLFSR {

    protected final List<LFSR> registers = new ArrayList<>();


    @Override
    public boolean clock() {
        boolean majorityBit = getMajorityBit();
        boolean result = false;
        for (var register : registers) {
            result ^= register.getLastBit();
            if (register.getClockBit() == majorityBit) {
                register.clock();
            }
        }
        return result;
    }


    private boolean getMajorityBit() {
        Map<Boolean, Integer> bitCount = new TreeMap<>();
        bitCount.put(Boolean.FALSE, 0);
        bitCount.put(Boolean.TRUE, 0);

        registers.forEach(lfsr -> bitCount.put(lfsr.getClockBit(), bitCount.get(lfsr.getClockBit()) + 1));
        return bitCount.get(Boolean.FALSE) <= bitCount.get(Boolean.TRUE);
    }
}
