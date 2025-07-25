package com.thealgorithms.sorts;


public class HeapSort implements SortAlgorithm {


    @Override
    public <T extends Comparable<T>> T[] sort(T[] array) {
        int n = array.length;
        heapify(array, n);
        while (n > 1) {
            SortUtils.swap(array, 0, n - 1);
            n--;
            siftDown(array, 1, n);
        }
        return array;
    }

    private <T extends Comparable<T>> void heapify(final T[] array, final int n) {
        for (int k = n / 2; k >= 1; k--) {
            siftDown(array, k, n);
        }
    }

    private <T extends Comparable<T>> void siftDown(final T[] array, int k, final int n) {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && SortUtils.less(array[j - 1], array[j])) {
                j++;
            }
            if (!SortUtils.less(array[k - 1], array[j - 1])) {
                break;
            }
            SortUtils.swap(array, k - 1, j - 1);
            k = j;
        }
    }
}
