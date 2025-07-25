package com.thealgorithms.datastructures.hashmap.hashing;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

class GenericHashMapUsingArrayListTest {

    @Test
    void testGenericHashmapWhichUsesArrayAndBothKeyAndValueAreStrings() {
        GenericHashMapUsingArrayList<String, String> map = new GenericHashMapUsingArrayList<>();
        map.put("USA", "Washington DC");
        map.put("Nepal", "Kathmandu");
        map.put("India", "New Delhi");
        map.put("Australia", "Sydney");
        assertNotNull(map);
        assertEquals(4, map.size());
        assertEquals("Kathmandu", map.get("Nepal"));
        assertEquals("Sydney", map.get("Australia"));
    }

    @Test
    void testGenericHashmapWhichUsesArrayAndKeyIsStringValueIsInteger() {
        GenericHashMapUsingArrayList<String, Integer> map = new GenericHashMapUsingArrayList<>();
        map.put("USA", 87);
        map.put("Nepal", 25);
        map.put("India", 101);
        map.put("Australia", 99);
        assertNotNull(map);
        assertEquals(4, map.size());
        assertEquals(25, map.get("Nepal"));
        assertEquals(99, map.get("Australia"));
        map.remove("Nepal");
        assertFalse(map.containsKey("Nepal"));
    }

    @Test
    void testGenericHashmapWhichUsesArrayAndKeyIsIntegerValueIsString() {
        GenericHashMapUsingArrayList<Integer, String> map = new GenericHashMapUsingArrayList<>();
        map.put(101, "Washington DC");
        map.put(34, "Kathmandu");
        map.put(46, "New Delhi");
        map.put(89, "Sydney");
        assertNotNull(map);
        assertEquals(4, map.size());
        assertEquals("Sydney", map.get(89));
        assertEquals("Washington DC", map.get(101));
        assertTrue(map.containsKey(46));
    }

    @Test
    void testRemoveNonExistentKey() {
        GenericHashMapUsingArrayList<String, String> map = new GenericHashMapUsingArrayList<>();
        map.put("USA", "Washington DC");
        map.remove("Nepal");
        assertEquals(1, map.size());
    }

    @Test
    void testRehashing() {
        GenericHashMapUsingArrayList<String, String> map = new GenericHashMapUsingArrayList<>();
        for (int i = 0; i < 20; i++) {
            map.put("Key" + i, "Value" + i);
        }
        assertEquals(20, map.size());
        assertEquals("Value5", map.get("Key5"));
    }

    @Test
    void testUpdateValueForExistingKey() {
        GenericHashMapUsingArrayList<String, String> map = new GenericHashMapUsingArrayList<>();
        map.put("USA", "Washington DC");
        map.put("USA", "New Washington DC");
        assertEquals("New Washington DC", map.get("USA"));
    }

    @Test
    void testToStringMethod() {
        GenericHashMapUsingArrayList<String, String> map = new GenericHashMapUsingArrayList<>();
        map.put("USA", "Washington DC");
        map.put("Nepal", "Kathmandu");
        String expected = "{USA : Washington DC, Nepal : Kathmandu}";
        assertEquals(expected, map.toString());
    }

    @Test
    void testContainsKey() {
        GenericHashMapUsingArrayList<String, String> map = new GenericHashMapUsingArrayList<>();
        map.put("USA", "Washington DC");
        assertTrue(map.containsKey("USA"));
        assertFalse(map.containsKey("Nepal"));
    }
}
