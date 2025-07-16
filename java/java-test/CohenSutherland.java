package com.thealgorithms.lineclipping;

import com.thealgorithms.lineclipping.utils.Line;
import com.thealgorithms.lineclipping.utils.Point;


public class CohenSutherland {


    private static final int INSIDE = 0;
    private static final int LEFT = 1;
    private static final int RIGHT = 2;
    private static final int BOTTOM = 4;
    private static final int TOP = 8;


    double xMin;
    double yMin;
    double xMax;
    double yMax;

    public CohenSutherland(double xMin, double yMin, double xMax, double yMax) {
        this.xMin = xMin;
        this.yMin = yMin;
        this.xMax = xMax;
        this.yMax = yMax;
    }


    private int computeCode(double x, double y) {
        int code = INSIDE;

        if (x < xMin)
        {
            code |= LEFT;
        } else if (x > xMax)
        {
            code |= RIGHT;
        }
        if (y < yMin)
        {
            code |= BOTTOM;
        } else if (y > yMax)
        {
            code |= TOP;
        }

        return code;
    }


    public Line cohenSutherlandClip(Line line) {
        double x1 = line.start.x;
        double y1 = line.start.y;
        double x2 = line.end.x;
        double y2 = line.end.y;

        int code1 = computeCode(x1, y1);
        int code2 = computeCode(x2, y2);
        boolean accept = false;

        while (true) {
            if ((code1 == 0) && (code2 == 0)) {

                accept = true;
                break;
            } else if ((code1 & code2) != 0) {

                break;
            } else {

                double x = 0;
                double y = 0;


                int codeOut = (code1 != 0) ? code1 : code2;


                if ((codeOut & TOP) != 0) {

                    x = x1 + (x2 - x1) * (yMax - y1) / (y2 - y1);
                    y = yMax;
                } else if ((codeOut & BOTTOM) != 0) {

                    x = x1 + (x2 - x1) * (yMin - y1) / (y2 - y1);
                    y = yMin;
                } else if ((codeOut & RIGHT) != 0) {

                    y = y1 + (y2 - y1) * (xMax - x1) / (x2 - x1);
                    x = xMax;
                } else if ((codeOut & LEFT) != 0) {

                    y = y1 + (y2 - y1) * (xMin - x1) / (x2 - x1);
                    x = xMin;
                }


                if (codeOut == code1) {
                    x1 = x;
                    y1 = y;
                    code1 = computeCode(x1, y1);
                } else {
                    x2 = x;
                    y2 = y;
                    code2 = computeCode(x2, y2);
                }
            }
        }

        if (accept) {
            return new Line(new Point(x1, y1), new Point(x2, y2));
        } else {

            return null;
        }
    }
}
