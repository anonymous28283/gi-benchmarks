package com.thealgorithms.datastructures.lists;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.StringJoiner;


public class SinglyLinkedList implements Iterable<Integer> {


    private Node head;


    private int size;


    public SinglyLinkedList() {
        head = null;
        size = 0;
    }


    public SinglyLinkedList(Node head, int size) {
        this.head = head;
        this.size = size;
    }


    public boolean detectLoop() {
        Node currentNodeFast = head;
        Node currentNodeSlow = head;
        while (currentNodeFast != null && currentNodeFast.next != null) {
            currentNodeFast = currentNodeFast.next.next;
            currentNodeSlow = currentNodeSlow.next;
            if (currentNodeFast == currentNodeSlow) {
                return true;
            }
        }
        return false;
    }


    public Node middle() {
        if (head == null) {
            return null;
        }
        Node firstCounter = head;
        Node secondCounter = firstCounter.next;
        while (secondCounter != null && secondCounter.next != null) {
            firstCounter = firstCounter.next;
            secondCounter = secondCounter.next.next;
        }
        return firstCounter;
    }


    public void swapNodes(int valueFirst, int valueSecond) {
        if (valueFirst == valueSecond) {
            return;
        }
        Node previousA = null;
        Node currentA = head;
        while (currentA != null && currentA.value != valueFirst) {
            previousA = currentA;
            currentA = currentA.next;
        }

        Node previousB = null;
        Node currentB = head;
        while (currentB != null && currentB.value != valueSecond) {
            previousB = currentB;
            currentB = currentB.next;
        }

        if (currentA == null || currentB == null) {
            return;
        }


        if (previousA != null) {
            previousA.next = currentB;
        } else {

            head = currentB;
        }


        if (previousB != null) {
            previousB.next = currentA;
        } else {

            head = currentA;
        }


        Node temp = currentA.next;
        currentA.next = currentB.next;
        currentB.next = temp;
    }


    public Node reverseListIter(Node node) {
        Node prev = null;
        Node curr = node;

        while (curr != null && curr.next != null) {
            Node next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }

        if (curr != null) {
            curr.next = prev;
            prev = curr;
        }


        return prev;
    }

    public Node reverseListRec(Node head) {
        if (head == null || head.next == null) {
            return head;
        }

        Node prev = null;
        Node h2 = reverseListRec(head.next);

        head.next.next = head;
        head.next = prev;

        return h2;
    }


    public void clear() {
        Node cur = head;
        while (cur != null) {
            cur = cur.next;
        }
        head = null;
        size = 0;
    }


    public boolean isEmpty() {
        return size == 0;
    }


    public int size() {
        return size;
    }


    public Node getHead() {
        return head;
    }


    public void setHead(Node head) {
        this.head = head;
    }


    public int count() {
        int count = 0;
        for (final var element : this) {
            ++count;
        }
        return count;
    }


    public boolean search(final int key) {
        for (final var element : this) {
            if (element == key) {
                return true;
            }
        }
        return false;
    }

    @Override
    public String toString() {
        StringJoiner joiner = new StringJoiner("->");
        for (final var element : this) {
            joiner.add(element + "");
        }
        return joiner.toString();
    }

    public void deleteDuplicates() {
        Node pred = head;


        Node newHead = head;
        while (newHead != null) {


            if (newHead.next != null && newHead.value == newHead.next.value) {

                while (newHead.next != null && newHead.value == newHead.next.value) {
                    newHead = newHead.next;
                }

                pred.next = newHead.next;
                newHead = null;

            }

            pred = pred.next;
            newHead = pred;
        }
    }

    public void print() {
        Node temp = head;
        while (temp != null && temp.next != null) {
            System.out.print(temp.value + "->");
            temp = temp.next;
        }
        if (temp != null) {
            System.out.print(temp.value);
            System.out.println();
        }
    }


    public void insertHead(int x) {
        insertNth(x, 0);
    }


    public void insert(int data) {
        insertNth(data, size);
    }


    public void insertNth(int data, int position) {
        checkBounds(position, 0, size);
        Node newNode = new Node(data);
        if (head == null) {

            head = newNode;
            size++;
            return;
        }
        if (position == 0) {

            newNode.next = head;
            head = newNode;
            size++;
            return;
        }

        Node cur = head;
        for (int i = 0; i < position - 1; ++i) {
            cur = cur.next;
        }
        newNode.next = cur.next;
        cur.next = newNode;
        size++;
    }


    public void deleteHead() {
        deleteNth(0);
    }


    public void delete() {
        deleteNth(size - 1);
    }


    public void deleteNth(int position) {
        checkBounds(position, 0, size - 1);
        if (position == 0) {
            head = head.next;

            size--;
            return;
        }
        Node cur = head;
        for (int i = 0; i < position - 1; ++i) {
            cur = cur.next;
        }

        cur.next = cur.next.next;
        size--;
    }


    public int getNth(int index) {
        checkBounds(index, 0, size - 1);
        Node cur = head;
        for (int i = 0; i < index; ++i) {
            cur = cur.next;
        }
        return cur.value;
    }


    public void checkBounds(int position, int low, int high) {
        if (position > high || position < low) {
            throw new IndexOutOfBoundsException(position + "");
        }
    }


    public static void main(String[] arg) {
        SinglyLinkedList list = new SinglyLinkedList();
        assert list.isEmpty();
        assert list.size() == 0 && list.count() == 0;
        assert list.toString().isEmpty();


        list.insertHead(5);
        list.insertHead(7);
        list.insertHead(10);
        list.insert(3);
        list.insertNth(1, 4);
        assert list.toString().equals("10->7->5->3->1");
        System.out.println(list);

        assert list.search(10) && list.search(5) && list.search(1) && !list.search(100);


        assert list.getNth(0) == 10 && list.getNth(2) == 5 && list.getNth(4) == 1;


        list.deleteHead();
        list.deleteNth(1);
        list.delete();
        assert list.toString().equals("7->3");
        System.out.println(list);
        assert list.size == 2 && list.size() == list.count();

        list.clear();
        assert list.isEmpty();

        try {
            list.delete();
            assert false;

        } catch (Exception e) {
            assert true;

        }

        SinglyLinkedList instance = new SinglyLinkedList();
        Node head = new Node(0, new Node(2, new Node(3, new Node(3, new Node(4)))));
        instance.setHead(head);
        instance.deleteDuplicates();
        instance.print();
    }

    @Override
    public Iterator<Integer> iterator() {
        return new SinglyLinkedListIterator();
    }

    private class SinglyLinkedListIterator implements Iterator<Integer> {
        private Node current;

        SinglyLinkedListIterator() {
            current = head;
        }

        @Override
        public boolean hasNext() {
            return current != null;
        }

        @Override
        public Integer next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            final var value = current.value;
            current = current.next;
            return value;
        }
    }
}


class Node {


    int value;


    Node next;

    Node() {
    }


    Node(int value) {
        this(value, null);
    }


    Node(int value, Node next) {
        this.value = value;
        this.next = next;
    }
}
