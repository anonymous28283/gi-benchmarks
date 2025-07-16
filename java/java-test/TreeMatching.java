package com.thealgorithms.dynamicprogramming;

import com.thealgorithms.datastructures.graphs.UndirectedAdjacencyListGraph;


public class TreeMatching {

    private UndirectedAdjacencyListGraph graph;
    private int[][] dp;


    public TreeMatching(UndirectedAdjacencyListGraph graph) {
        this.graph = graph;
        this.dp = new int[graph.size()][2];
    }


    public int getMaxMatching(int root, int parent) {
        if (root < 0 || root >= graph.size()) {
            throw new IllegalArgumentException("Invalid root: " + root);
        }
        maxMatching(root, parent);
        return Math.max(dp[root][0], dp[root][1]);
    }


    private void maxMatching(int node, int parent) {
        dp[node][0] = 0;
        dp[node][1] = 0;

        int sumWithoutEdge = 0;
        for (int adjNode : graph.getNeighbors(node)) {
            if (adjNode == parent) {
                continue;
            }
            maxMatching(adjNode, node);
            sumWithoutEdge += Math.max(dp[adjNode][0], dp[adjNode][1]);
        }

        dp[node][0] = sumWithoutEdge;

        for (int adjNode : graph.getNeighbors(node)) {
            if (adjNode == parent) {
                continue;
            }
            int weight = graph.getEdgeWeight(node, adjNode);
            dp[node][1] = Math.max(dp[node][1], sumWithoutEdge - Math.max(dp[adjNode][0], dp[adjNode][1]) + dp[adjNode][0] + weight);
        }
    }
}
