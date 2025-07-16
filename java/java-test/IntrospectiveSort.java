package com.thealgorithms.sorts;


public class IntrospectiveSort implements SortAlgorithm {

    private static final int INSERTION_SORT_THRESHOLD = 16;


    @Override
    public <T extends Comparable<T>> T[] sort(T[] array) {
        if (array == null || array.length <= 1) {
            return array;
        }
        final int depth = 2 * (int) (Math.log(array.length) / Math.log(2));
        introspectiveSort(array, 0, array.length - 1, depth);
        return array;
    }


    private static <T extends Comparable<T>> void introspectiveSort(T[] array, final int low, int high, final int depth) {
        while (high - low > INSERTION_SORT_THRESHOLD) {
            if (depth == 0) {
                heapSort(array, low, high);
                return;
            }
            final int pivotIndex = partition(array, low, high);
            introspectiveSort(array, pivotIndex + 1, high, depth - 1);
            high = pivotIndex - 1;
        }
        insertionSort(array, low, high);
    }


    private static <T extends Comparable<T>> int partition(T[] array, final int low, final int high) {
        final int pivotIndex = low + (int) (Math.random() * (high - low + 1));
        SortUtils.swap(array, pivotIndex, high);
        final T pivot = array[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (array[j].compareTo(pivot) <= 0) {
                i++;
                SortUtils.swap(array, i, j);
            }
        }
        SortUtils.swap(array, i + 1, high);
        return i + 1;
    }


    private static <T extends Comparable<T>> void insertionSort(T[] array, final int low, final int high) {
        for (int i = low + 1; i <= high; i++) {
            final T key = array[i];
            int j = i - 1;
            while (j >= low && array[j].compareTo(key) > 0) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = key;
        }
    }


    private static <T extends Comparable<T>> void heapSort(T[] array, final int low, final int high) {
        final int n = high - low + 1;
        for (int i = (n / 2) - 1; i >= 0; i--) {
            heapify(array, i, n, low);
        }
        for (int i = high; i > low; i--) {
            SortUtils.swap(array, low, i);
            heapify(array, 0, i - low, low);
        }
    }


    private static <T extends Comparable<T>> void heapify(T[] array, final int i, final int n, final int low) {
        final int left = 2 * i + 1;
        final int right = 2 * i + 2;
        int largest = i;

        if (left < n && array[low + left].compareTo(array[low + largest]) > 0) {
            largest = left;
        }
        if (right < n && array[low + right].compareTo(array[low + largest]) > 0) {
            largest = right;
        }
        if (largest != i) {
            SortUtils.swap(array, low + i, low + largest);
            heapify(array, largest, n, low);
        }
    }
}
