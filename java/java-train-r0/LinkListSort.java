package com.thealgorithms.sorts;

import java.util.Arrays;

public class LinkListSort {

    public static boolean isSorted(int[] p, int option) {
        int[] a = p;

        int[] b = p;

        int ch = option;


        switch (ch) {
        case 1:
            Task nm = new Task();
            Node start = null;
            Node prev = null;
            Node fresh;
            Node ptr;
            for (int i = 0; i < a.length; i++) {

                fresh = new Node();
                fresh.val = a[i];
                if (start == null) {
                    start = fresh;
                } else {
                    prev.next = fresh;
                }
                prev = fresh;
            }
            start = nm.sortByMergeSort(start);

            int i = 0;
            for (ptr = start; ptr != null; ptr = ptr.next) {
                a[i++] = ptr.val;

            }
            Arrays.sort(b);

            LinkListSort uu = new LinkListSort();
            return uu.compare(a, b);


        case 2:
            Node start1 = null;
            Node prev1 = null;
            Node fresh1;
            Node ptr1;
            for (int i1 = 0; i1 < a.length; i1++) {

                fresh1 = new Node();
                fresh1.val = a[i1];
                if (start1 == null) {
                    start1 = fresh1;
                } else {
                    prev1.next = fresh1;
                }
                prev1 = fresh1;
            }
            Task1 kk = new Task1();
            start1 = kk.sortByInsertionSort(start1);

            int i1 = 0;
            for (ptr1 = start1; ptr1 != null; ptr1 = ptr1.next) {
                a[i1++] = ptr1.val;

            }
            LinkListSort uu1 = new LinkListSort();

            return uu1.compare(a, b);


        case 3:
            Task2 mm = new Task2();
            Node start2 = null;
            Node prev2 = null;
            Node fresh2;
            Node ptr2;
            for (int i2 = 0; i2 < a.length; i2++) {

                fresh2 = new Node();
                fresh2.val = a[i2];
                if (start2 == null) {
                    start2 = fresh2;
                } else {
                    prev2.next = fresh2;
                }
                prev2 = fresh2;
            }
            start2 = mm.sortByHeapSort(start2);

            int i3 = 0;
            for (ptr2 = start2; ptr2 != null; ptr2 = ptr2.next) {
                a[i3++] = ptr2.val;

            }
            Arrays.sort(b);

            LinkListSort uu2 = new LinkListSort();
            return uu2.compare(a, b);


        default:

            System.out.println("Wrong choice");
        }

        return false;
    }

    boolean compare(int[] a, int[] b) {
        for (int i = 0; i < a.length; i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }
        return true;


    }
}

class Node {

    int val;
    Node next;

}

class Task {

    private int[] a;

    public Node sortByMergeSort(Node head) {
        if (head == null || head.next == null) {
            return head;
        }
        int c = count(head);
        a = new int[c];

        int i = 0;
        for (Node ptr = head; ptr != null; ptr = ptr.next) {
            a[i++] = ptr.val;
        }

        i = 0;
        task(a, 0, c - 1);

        for (Node ptr = head; ptr != null; ptr = ptr.next) {
            ptr.val = a[i++];

        }
        return head;
    }

    int count(Node head) {
        int c = 0;
        Node ptr;
        for (ptr = head; ptr != null; ptr = ptr.next) {
            c++;
        }
        return c;


    }

    void task(int[] n, int i, int j) {
        if (i < j) {
            int m = (i + j) / 2;
            task(n, i, m);
            task(n, m + 1, j);
            task1(n, i, m, j);

        }
    }

    void task1(int[] n, int s, int m, int e) {
        int i = s;
        int k = 0;
        int j = m + 1;
        int[] b = new int[e - s + 1];
        while (i <= m && j <= e) {
            if (n[j] >= n[i]) {
                b[k++] = n[i++];
            } else {
                b[k++] = n[j++];
            }
        }

        while (i <= m) {
            b[k++] = n[i++];
        }
        while (j <= e) {
            b[k++] = n[j++];
        }
        for (int p = s; p <= e; p++) {
            a[p] = b[p - s];
        }
    }

}

class Task1 {

    public Node sortByInsertionSort(Node head) {
        if (head == null || head.next == null) {
            return head;
        }
        int c = count(head);
        int[] a = new int[c];

        a[0] = head.val;
        int i;
        Node ptr;
        for (ptr = head.next, i = 1; ptr != null; ptr = ptr.next, i++) {
            int j = i - 1;
            while (j >= 0 && a[j] > ptr.val) {

                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = ptr.val;
        }
        i = 0;
        for (ptr = head; ptr != null; ptr = ptr.next) {
            ptr.val = a[i++];

        }
        return head;
    }

    static int count(Node head) {
        Node ptr;
        int c = 0;
        for (ptr = head; ptr != null; ptr = ptr.next) {
            c++;
        }
        return c;


    }

}

class Task2 {

    public Node sortByHeapSort(Node head) {
        if (head == null || head.next == null) {
            return head;
        }
        int c = count(head);
        int[] a = new int[c];

        int i = 0;
        for (Node ptr = head; ptr != null; ptr = ptr.next) {
            a[i++] = ptr.val;

        }
        i = 0;
        task(a);
        for (Node ptr = head; ptr != null; ptr = ptr.next) {
            ptr.val = a[i++];

        }
        return head;
    }

    int count(Node head) {
        int c = 0;
        Node ptr;
        for (ptr = head; ptr != null; ptr = ptr.next) {
            c++;
        }
        return c;


    }

    void task(int[] n) {
        int k = n.length;
        for (int i = k / 2 - 1; i >= 0; i--) {
            task1(n, k, i);
        }
        for (int i = k - 1; i > 0; i--) {
            int d = n[0];
            n[0] = n[i];
            n[i] = d;
            task1(n, i, 0);

        }
    }

    void task1(int[] n, int k, int i) {
        int p = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < k && n[l] > n[p]) {
            p = l;
        }
        if (r < k && n[r] > n[p]) {
            p = r;
        }
        if (p != i) {
            int d = n[p];
            n[p] = n[i];
            n[i] = d;
            task1(n, k, p);
        }
    }

}
