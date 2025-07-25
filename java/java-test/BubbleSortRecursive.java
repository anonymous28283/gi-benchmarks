package com.thealgorithms.sorts;


public class BubbleSortRecursive implements SortAlgorithm {

    @Override
    public <T extends Comparable<T>> T[] sort(T[] array) {
        bubbleSort(array, array.length);
        return array;
    }


    private static <T extends Comparable<T>> void bubbleSort(T[] array, int len) {
        boolean swapped = false;
        for (int i = 0; i < len - 1; ++i) {
            if (SortUtils.greater(array[i], array[i + 1])) {
                SortUtils.swap(array, i, i + 1);
                swapped = true;
            }
        }
        if (swapped) {
            bubbleSort(array, len - 1);
        }
    }
}
