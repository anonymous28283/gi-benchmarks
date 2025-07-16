package com.thealgorithms.datastructures.crdt;

import java.time.Instant;
import java.util.HashMap;
import java.util.Map;


class LWWElementSet<T> {
    final Map<T, Element<T>> addSet;
    final Map<T, Element<T>> removeSet;


    LWWElementSet() {
        this.addSet = new HashMap<>();
        this.removeSet = new HashMap<>();
    }


    public void add(T key) {
        addSet.put(key, new Element<>(key, Instant.now()));
    }


    public void remove(T key) {
        removeSet.put(key, new Element<>(key, Instant.now()));
    }


    public boolean lookup(T key) {
        Element<T> inAddSet = addSet.get(key);
        Element<T> inRemoveSet = removeSet.get(key);

        return inAddSet != null && (inRemoveSet == null || inAddSet.timestamp.isAfter(inRemoveSet.timestamp));
    }


    public void merge(LWWElementSet<T> other) {
        for (Map.Entry<T, Element<T>> entry : other.addSet.entrySet()) {
            addSet.merge(entry.getKey(), entry.getValue(), this::resolveConflict);
        }
        for (Map.Entry<T, Element<T>> entry : other.removeSet.entrySet()) {
            removeSet.merge(entry.getKey(), entry.getValue(), this::resolveConflict);
        }
    }


    private Element<T> resolveConflict(Element<T> e1, Element<T> e2) {
        return e1.timestamp.isAfter(e2.timestamp) ? e1 : e2;
    }
}


class Element<T> {
    T key;
    Instant timestamp;


    Element(T key, Instant timestamp) {
        this.key = key;
        this.timestamp = timestamp;
    }
}
