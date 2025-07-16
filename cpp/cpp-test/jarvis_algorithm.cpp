






namespace geometry {

    namespace jarvis {

        struct Point {
            int x, y;
        };


        class Convexhull {
            std::vector<Point> points;
            int size;

        public:

            explicit Convexhull(const std::vector<Point> &pointList) {
                points = pointList;
                size = points.size();
            }


            std::vector<Point> getConvexHull() const {

                std::vector<Point> hull;


                int leftmost_point = 0;
                for (int i = 1; i < size; i++) {
                    if (points[i].x < points[leftmost_point].x) {
                        leftmost_point = i;
                    }
                }



                int p = leftmost_point, q = 0;
                do {

                    hull.push_back(points[p]);






                    q = (p + 1) % size;
                    for (int i = 0; i < size; i++) {


                        if (orientation(points[p], points[i], points[q]) == 2) {
                            q = i;
                        }
                    }




                    p = q;

                } while (p != leftmost_point);

                return hull;
            }


            static int orientation(const Point &p, const Point &q, const Point &r) {
                int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

                if (val == 0) {
                    return 0;
                }
                return (val > 0) ? 1 : 2;
            }

        };

    }
}


static void test() {
    std::vector<geometry::jarvis::Point> points = {{0, 3},
                                                   {2, 2},
                                                   {1, 1},
                                                   {2, 1},
                                                   {3, 0},
                                                   {0, 0},
                                                   {3, 3}
    };
    geometry::jarvis::Convexhull hull(points);
    std::vector<geometry::jarvis::Point> actualPoint;
    actualPoint = hull.getConvexHull();

    std::vector<geometry::jarvis::Point> expectedPoint = {{0, 3},
                                                          {0, 0},
                                                          {3, 0},
                                                          {3, 3}};
    for (int i = 0; i < expectedPoint.size(); i++) {
        assert(actualPoint[i].x == expectedPoint[i].x);
        assert(actualPoint[i].y == expectedPoint[i].y);
    }
    std::cout << "Test implementations passed!\n";
}


int main() {
    test();
    return 0;
}
