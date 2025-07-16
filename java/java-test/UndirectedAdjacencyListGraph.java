package com.thealgorithms.datastructures.graphs;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

public class UndirectedAdjacencyListGraph {
    private ArrayList<HashMap<Integer, Integer>> adjacencyList = new ArrayList<>();


    public int addNode() {
        adjacencyList.add(new HashMap<>());
        return adjacencyList.size() - 1;
    }


    public boolean addEdge(int orig, int dest, int weight) {
        int numNodes = adjacencyList.size();
        if (orig >= numNodes || dest >= numNodes || orig < 0 || dest < 0) {
            return false;
        }

        if (adjacencyList.get(orig).containsKey(dest)) {
            return false;
        }

        adjacencyList.get(orig).put(dest, weight);
        adjacencyList.get(dest).put(orig, weight);
        return true;
    }


    public HashSet<Integer> getNeighbors(int node) {
        return new HashSet<>(adjacencyList.get(node).keySet());
    }


    public Integer getEdgeWeight(int orig, int dest) {
        return adjacencyList.get(orig).getOrDefault(dest, null);
    }


    public int size() {
        return adjacencyList.size();
    }
}
