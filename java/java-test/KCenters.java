package com.thealgorithms.greedyalgorithms;

import java.util.Arrays;


public final class KCenters {
    private KCenters() {
    }


    public static int findKCenters(int[][] distances, int k) {
        int n = distances.length;
        boolean[] selected = new boolean[n];
        int[] maxDist = new int[n];

        Arrays.fill(maxDist, Integer.MAX_VALUE);

        selected[0] = true;
        for (int i = 1; i < n; i++) {
            maxDist[i] = Math.min(maxDist[i], distances[0][i]);
        }

        for (int centers = 1; centers < k; centers++) {
            int farthest = -1;
            for (int i = 0; i < n; i++) {
                if (!selected[i] && (farthest == -1 || maxDist[i] > maxDist[farthest])) {
                    farthest = i;
                }
            }
            selected[farthest] = true;
            for (int i = 0; i < n; i++) {
                maxDist[i] = Math.min(maxDist[i], distances[farthest][i]);
            }
        }

        int result = 0;
        for (int dist : maxDist) {
            result = Math.max(result, dist);
        }
        return result;
    }
}
