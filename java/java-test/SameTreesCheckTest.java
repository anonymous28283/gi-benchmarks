package com.thealgorithms.datastructures.trees;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;


public class SameTreesCheckTest {
    @Test
    public void testBothRootsAreNull() {
        assertTrue(SameTreesCheck.check(null, null));
    }

    @Test
    public void testOneRootIsNull() {
        final BinaryTree.Node root = TreeTestUtils.createTree(new Integer[] {100});
        assertFalse(SameTreesCheck.check(root, null));
    }

    @Test
    public void testSingleNodeTreesAreSame() {
        final BinaryTree.Node p = TreeTestUtils.createTree(new Integer[] {100});
        final BinaryTree.Node q = TreeTestUtils.createTree(new Integer[] {100});
        assertTrue(SameTreesCheck.check(p, q));
    }


    @Test
    public void testSameTreesIsSuccessful() {
        final BinaryTree.Node p = TreeTestUtils.createTree(new Integer[] {1, 2, 3, 4, 5, 6, 7});
        final BinaryTree.Node q = TreeTestUtils.createTree(new Integer[] {1, 2, 3, 4, 5, 6, 7});
        assertTrue(SameTreesCheck.check(p, q));
    }


    @Test
    public void testSameTreesFails() {
        final BinaryTree.Node p = TreeTestUtils.createTree(new Integer[] {1, 2, 3, 4, 5, 6, 7});
        final BinaryTree.Node q = TreeTestUtils.createTree(new Integer[] {1, 2, 3, 4, 5, 6});
        assertFalse(SameTreesCheck.check(p, q));
    }


    @Test
    public void testTreesWithDifferentStructure() {
        final BinaryTree.Node p = TreeTestUtils.createTree(new Integer[] {1, 2});
        final BinaryTree.Node q = TreeTestUtils.createTree(new Integer[] {1, null, 2});
        assertFalse(SameTreesCheck.check(p, q));
    }
}
