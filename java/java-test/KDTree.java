package com.thealgorithms.datastructures.trees;

import java.util.Arrays;
import java.util.Comparator;
import java.util.Objects;
import java.util.Optional;



public class KDTree {

    private Node root;

    private final int k;


    KDTree(int k) {
        this.k = k;
    }


    KDTree(Point[] points) {
        if (points.length == 0) {
            throw new IllegalArgumentException("Points array cannot be empty");
        }
        this.k = points[0].getDimension();
        for (Point point : points) {
            if (point.getDimension() != k) {
                throw new IllegalArgumentException("Points must have the same dimension");
            }
        }
        this.root = build(points, 0);
    }


    KDTree(int[][] pointsCoordinates) {
        if (pointsCoordinates.length == 0) {
            throw new IllegalArgumentException("Points array cannot be empty");
        }
        this.k = pointsCoordinates[0].length;
        Point[] points = Arrays.stream(pointsCoordinates).map(Point::new).toArray(Point[] ::new);
        for (Point point : points) {
            if (point.getDimension() != k) {
                throw new IllegalArgumentException("Points must have the same dimension");
            }
        }
        this.root = build(points, 0);
    }

    static class Point {

        int[] coordinates;

        public int getCoordinate(int i) {
            return coordinates[i];
        }

        public int getDimension() {
            return coordinates.length;
        }

        Point(int[] coordinates) {
            this.coordinates = coordinates;
        }

        @Override
        public boolean equals(Object obj) {
            if (obj instanceof Point other) {
                return Arrays.equals(other.coordinates, this.coordinates);
            }
            return false;
        }

        @Override
        public int hashCode() {
            return Arrays.hashCode(coordinates);
        }

        @Override
        public String toString() {
            return Arrays.toString(coordinates);
        }


        public static int comparableDistance(Point p1, Point p2) {
            int distance = 0;
            for (int i = 0; i < p1.getDimension(); i++) {
                int t = p1.getCoordinate(i) - p2.getCoordinate(i);
                distance += t * t;
            }
            return distance;
        }


        public static int comparableDistanceExceptAxis(Point p1, Point p2, int axis) {
            int distance = 0;
            for (int i = 0; i < p1.getDimension(); i++) {
                if (i == axis) {
                    continue;
                }
                int t = p1.getCoordinate(i) - p2.getCoordinate(i);
                distance += t * t;
            }
            return distance;
        }
    }

    static class Node {

        private Point point;
        private int axis;

        private Node left = null;
        private Node right = null;

        Node(Point point, int axis) {
            this.point = point;
            this.axis = axis;
        }

        public Point getPoint() {
            return point;
        }

        public Node getLeft() {
            return left;
        }

        public Node getRight() {
            return right;
        }

        public int getAxis() {
            return axis;
        }


        public Node getNearChild(Point point) {
            if (point.getCoordinate(axis) < this.point.getCoordinate(axis)) {
                return left;
            } else {
                return right;
            }
        }


        public Node getFarChild(Point point) {
            if (point.getCoordinate(axis) < this.point.getCoordinate(axis)) {
                return right;
            } else {
                return left;
            }
        }


        public int getAxisCoordinate() {
            return point.getCoordinate(axis);
        }
    }

    public Node getRoot() {
        return root;
    }


    private Node build(Point[] points, int depth) {
        if (points.length == 0) {
            return null;
        }
        int axis = depth % k;
        if (points.length == 1) {
            return new Node(points[0], axis);
        }
        Arrays.sort(points, Comparator.comparingInt(o -> o.getCoordinate(axis)));
        int median = points.length >> 1;
        Node node = new Node(points[median], axis);
        node.left = build(Arrays.copyOfRange(points, 0, median), depth + 1);
        node.right = build(Arrays.copyOfRange(points, median + 1, points.length), depth + 1);
        return node;
    }


    public void insert(Point point) {
        if (point.getDimension() != k) {
            throw new IllegalArgumentException("Point has wrong dimension");
        }
        root = insert(root, point, 0);
    }


    private Node insert(Node root, Point point, int depth) {
        int axis = depth % k;
        if (root == null) {
            return new Node(point, axis);
        }
        if (point.getCoordinate(axis) < root.getAxisCoordinate()) {
            root.left = insert(root.left, point, depth + 1);
        } else {
            root.right = insert(root.right, point, depth + 1);
        }

        return root;
    }


    public Optional<Node> search(Point point) {
        if (point.getDimension() != k) {
            throw new IllegalArgumentException("Point has wrong dimension");
        }
        return search(root, point);
    }


    public Optional<Node> search(Node root, Point point) {
        if (root == null) {
            return Optional.empty();
        }
        if (root.point.equals(point)) {
            return Optional.of(root);
        }
        return search(root.getNearChild(point), point);
    }


    public Point findMin(int axis) {
        return findMin(root, axis).point;
    }


    public Node findMin(Node root, int axis) {
        if (root == null) {
            return null;
        }
        if (root.getAxis() == axis) {
            if (root.left == null) {
                return root;
            }
            return findMin(root.left, axis);
        } else {
            Node left = findMin(root.left, axis);
            Node right = findMin(root.right, axis);
            Node[] candidates = {left, root, right};
            return Arrays.stream(candidates).filter(Objects::nonNull).min(Comparator.comparingInt(a -> a.point.getCoordinate(axis))).orElse(null);
        }
    }


    public Point findMax(int axis) {
        return findMax(root, axis).point;
    }


    public Node findMax(Node root, int axis) {
        if (root == null) {
            return null;
        }
        if (root.getAxis() == axis) {
            if (root.right == null) {
                return root;
            }
            return findMax(root.right, axis);
        } else {
            Node left = findMax(root.left, axis);
            Node right = findMax(root.right, axis);
            Node[] candidates = {left, root, right};
            return Arrays.stream(candidates).filter(Objects::nonNull).max(Comparator.comparingInt(a -> a.point.getCoordinate(axis))).orElse(null);
        }
    }


    public void delete(Point point) {
        Node node = search(point).orElseThrow(() -> new IllegalArgumentException("Point not found"));
        root = delete(root, node);
    }


    private Node delete(Node root, Node node) {
        if (root == null) {
            return null;
        }
        if (root.equals(node)) {
            if (root.right != null) {
                Node min = findMin(root.right, root.getAxis());
                root.point = min.point;
                root.right = delete(root.right, min);
            } else if (root.left != null) {
                Node min = findMin(root.left, root.getAxis());
                root.point = min.point;
                root.left = delete(root.left, min);
            } else {
                return null;
            }
        }
        if (root.getAxisCoordinate() < node.point.getCoordinate(root.getAxis())) {
            root.left = delete(root.left, node);
        } else {
            root.right = delete(root.right, node);
        }
        return root;
    }


    public Point findNearest(Point point) {
        return findNearest(root, point, root).point;
    }


    private Node findNearest(Node root, Point point, Node nearest) {
        if (root == null) {
            return nearest;
        }
        if (root.point.equals(point)) {
            return root;
        }
        int distance = Point.comparableDistance(root.point, point);
        int distanceExceptAxis = Point.comparableDistanceExceptAxis(root.point, point, root.getAxis());
        if (distance < Point.comparableDistance(nearest.point, point)) {
            nearest = root;
        }
        nearest = findNearest(root.getNearChild(point), point, nearest);
        if (distanceExceptAxis < Point.comparableDistance(nearest.point, point)) {
            nearest = findNearest(root.getFarChild(point), point, nearest);
        }
        return nearest;
    }
}
