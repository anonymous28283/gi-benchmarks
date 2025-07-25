package com.thealgorithms.divideandconquer;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.ArrayList;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class SkylineAlgorithmTest {

    private SkylineAlgorithm skylineAlgorithm;

    @BeforeEach
    public void setUp() {
        skylineAlgorithm = new SkylineAlgorithm();
    }

    @Test
    public void testProduceSubSkyLinesSinglePoint() {

        ArrayList<SkylineAlgorithm.Point> points = new ArrayList<>();
        points.add(new SkylineAlgorithm.Point(1, 10));

        ArrayList<SkylineAlgorithm.Point> result = skylineAlgorithm.produceSubSkyLines(points);

        assertEquals(1, result.size());
        assertEquals(1, result.get(0).getX());
        assertEquals(10, result.get(0).getY());
    }

    @Test
    public void testProduceSubSkyLinesTwoPoints() {

        ArrayList<SkylineAlgorithm.Point> points = new ArrayList<>();
        points.add(new SkylineAlgorithm.Point(1, 10));
        points.add(new SkylineAlgorithm.Point(1, 5));

        ArrayList<SkylineAlgorithm.Point> result = skylineAlgorithm.produceSubSkyLines(points);

        assertEquals(1, result.size());
        assertEquals(1, result.get(0).getX());
        assertEquals(5, result.get(0).getY());
    }

    @Test
    public void testProduceSubSkyLinesMultiplePoints() {

        ArrayList<SkylineAlgorithm.Point> points = new ArrayList<>();
        points.add(new SkylineAlgorithm.Point(1, 10));
        points.add(new SkylineAlgorithm.Point(2, 15));
        points.add(new SkylineAlgorithm.Point(3, 5));
        points.add(new SkylineAlgorithm.Point(4, 20));

        ArrayList<SkylineAlgorithm.Point> result = skylineAlgorithm.produceSubSkyLines(points);

        assertEquals(2, result.size());


        assertEquals(1, result.get(0).getX());
        assertEquals(10, result.get(0).getY());
        assertEquals(3, result.get(1).getX());
        assertEquals(5, result.get(1).getY());
    }

    @Test
    public void testProduceFinalSkyLine() {

        ArrayList<SkylineAlgorithm.Point> left = new ArrayList<>();
        left.add(new SkylineAlgorithm.Point(1, 10));
        left.add(new SkylineAlgorithm.Point(2, 5));

        ArrayList<SkylineAlgorithm.Point> right = new ArrayList<>();
        right.add(new SkylineAlgorithm.Point(3, 8));
        right.add(new SkylineAlgorithm.Point(4, 3));

        ArrayList<SkylineAlgorithm.Point> result = skylineAlgorithm.produceFinalSkyLine(left, right);

        assertEquals(3, result.size());


        assertEquals(1, result.get(0).getX());
        assertEquals(10, result.get(0).getY());
        assertEquals(2, result.get(1).getX());
        assertEquals(5, result.get(1).getY());
        assertEquals(4, result.get(2).getX());
        assertEquals(3, result.get(2).getY());
    }

    @Test
    public void testXComparator() {

        SkylineAlgorithm.XComparator comparator = new SkylineAlgorithm().new XComparator();

        SkylineAlgorithm.Point p1 = new SkylineAlgorithm.Point(1, 10);
        SkylineAlgorithm.Point p2 = new SkylineAlgorithm.Point(2, 5);


        assertEquals(-1, comparator.compare(p1, p2));
        assertEquals(1, comparator.compare(p2, p1));
        assertEquals(0, comparator.compare(p1, new SkylineAlgorithm.Point(1, 15)));
    }
}
