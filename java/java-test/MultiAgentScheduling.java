package com.thealgorithms.scheduling;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class MultiAgentScheduling {

    static class Agent {
        String name;
        List<String> tasks;

        Agent(String name) {
            this.name = name;
            this.tasks = new ArrayList<>();
        }

        void addTask(String task) {
            tasks.add(task);
        }

        List<String> getTasks() {
            return tasks;
        }
    }

    private final Map<String, Agent> agents;

    public MultiAgentScheduling() {
        agents = new HashMap<>();
    }

    public void addAgent(String agentName) {
        agents.putIfAbsent(agentName, new Agent(agentName));
    }


    public void assignTask(String agentName, String task) {
        Agent agent = agents.get(agentName);
        if (agent != null) {
            agent.addTask(task);
        }
    }


    public Map<String, List<String>> getScheduledTasks() {
        Map<String, List<String>> schedule = new HashMap<>();
        for (Agent agent : agents.values()) {
            schedule.put(agent.name, agent.getTasks());
        }
        return schedule;
    }
}
