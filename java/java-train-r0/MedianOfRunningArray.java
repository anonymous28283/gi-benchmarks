package com.thealgorithms.misc;

import java.util.Collections;
import java.util.PriorityQueue;


public abstract class MedianOfRunningArray<T extends Number & Comparable<T>> {

    private PriorityQueue<T> maxHeap;
    private PriorityQueue<T> minHeap;


    public MedianOfRunningArray() {
        this.maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        this.minHeap = new PriorityQueue<>();
    }


    public void insert(final T e) {
        if (!minHeap.isEmpty() && e.compareTo(minHeap.peek()) < 0) {
            maxHeap.offer(e);
            if (maxHeap.size() > minHeap.size() + 1) {
                minHeap.offer(maxHeap.poll());
            }
        } else {
            minHeap.offer(e);
            if (minHeap.size() > maxHeap.size() + 1) {
                maxHeap.offer(minHeap.poll());
            }
        }
    }


    public T median() {
        if (maxHeap.isEmpty() && minHeap.isEmpty()) {
            throw new IllegalArgumentException("Enter at least 1 element, Median of empty list is not defined!");
        } else if (maxHeap.size() == minHeap.size()) {
            T maxHeapTop = maxHeap.peek();
            T minHeapTop = minHeap.peek();
            return calculateAverage(maxHeapTop, minHeapTop);
        }
        return maxHeap.size() > minHeap.size() ? maxHeap.peek() : minHeap.peek();
    }

    public abstract T calculateAverage(T a, T b);
}
