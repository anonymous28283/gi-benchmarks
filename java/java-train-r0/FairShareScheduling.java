package com.thealgorithms.scheduling;

import java.util.HashMap;
import java.util.Map;


public final class FairShareScheduling {

    static class User {
        String name;
        int allocatedResources;
        int totalWeight;

        User(String name) {
            this.name = name;
            this.allocatedResources = 0;
            this.totalWeight = 0;
        }

        void addWeight(int weight) {
            this.totalWeight += weight;
        }
    }

    private final Map<String, User> users;

    public FairShareScheduling() {
        users = new HashMap<>();
    }

    public void addUser(String userName) {
        users.putIfAbsent(userName, new User(userName));
    }

    public void addTask(String userName, int weight) {
        User user = users.get(userName);
        if (user != null) {
            user.addWeight(weight);
        }
    }

    public void allocateResources(int totalResources) {
        int totalWeights = users.values().stream().mapToInt(user -> user.totalWeight).sum();
        for (User user : users.values()) {
            user.allocatedResources = (int) ((double) user.totalWeight / totalWeights * totalResources);
        }
    }

    public Map<String, Integer> getAllocatedResources() {
        Map<String, Integer> allocation = new HashMap<>();
        for (User user : users.values()) {
            allocation.put(user.name, user.allocatedResources);
        }
        return allocation;
    }
}
