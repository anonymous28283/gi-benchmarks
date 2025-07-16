package com.thealgorithms.datastructures.trees;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;


public final class PostOrderTraversal {
    private PostOrderTraversal() {
    }
    public static List<Integer> recursivePostOrder(BinaryTree.Node root) {
        List<Integer> result = new ArrayList<>();
        recursivePostOrder(root, result);
        return result;
    }

    public static List<Integer> iterativePostOrder(BinaryTree.Node root) {
        LinkedList<Integer> result = new LinkedList<>();
        if (root == null) {
            return result;
        }

        Deque<BinaryTree.Node> stack = new ArrayDeque<>();
        stack.push(root);
        while (!stack.isEmpty()) {
            BinaryTree.Node node = stack.pop();
            result.addFirst(node.data);
            if (node.left != null) {
                stack.push(node.left);
            }
            if (node.right != null) {
                stack.push(node.right);
            }
        }

        return result;
    }

    private static void recursivePostOrder(BinaryTree.Node root, List<Integer> result) {
        if (root == null) {
            return;
        }
        recursivePostOrder(root.left, result);
        recursivePostOrder(root.right, result);
        result.add(root.data);
    }
}
