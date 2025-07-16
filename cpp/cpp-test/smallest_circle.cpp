





struct Point {
    double x,
        y;


    explicit Point(double a = 0.f, double b = 0.f) {
        x = a;
        y = b;
    }
};


double LenghtLine(const Point &A, const Point &B) {
    double dx = B.x - A.x;
    double dy = B.y - A.y;
    return std::sqrt((dx * dx) + (dy * dy));
}


double TriangleArea(const Point &A, const Point &B, const Point &C) {
    double a = LenghtLine(A, B);
    double b = LenghtLine(B, C);
    double c = LenghtLine(C, A);
    double p = (a + b + c) / 2;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}


bool PointInCircle(const std::vector<Point> &P, const Point &Center, double R) {
    for (size_t i = 0; i < P.size(); i++) {
        if (LenghtLine(P[i], Center) > R)
            return false;
    }
    return true;
}


double circle(const std::vector<Point> &P) {
    double minR = INFINITY;
    double R;
    Point C;
    Point minC;



    for (size_t i = 0; i < P.size() - 2; i++)

        for (size_t j = i + 1; j < P.size(); j++)

            for (size_t k = j + 1; k < P.size(); k++) {



                C.x = -0.5 * ((P[i].y * (P[j].x * P[j].x + P[j].y * P[j].y -
                                         P[k].x * P[k].x - P[k].y * P[k].y) +
                               P[j].y * (P[k].x * P[k].x + P[k].y * P[k].y -
                                         P[i].x * P[i].x - P[i].y * P[i].y) +
                               P[k].y * (P[i].x * P[i].x + P[i].y * P[i].y -
                                         P[j].x * P[j].x - P[j].y * P[j].y)) /
                              (P[i].x * (P[j].y - P[k].y) +
                               P[j].x * (P[k].y - P[i].y) +
                               P[k].x * (P[i].y - P[j].y)));
                C.y = 0.5 * ((P[i].x * (P[j].x * P[j].x + P[j].y * P[j].y -
                                        P[k].x * P[k].x - P[k].y * P[k].y) +
                              P[j].x * (P[k].x * P[k].x + P[k].y * P[k].y -
                                        P[i].x * P[i].x - P[i].y * P[i].y) +
                              P[k].x * (P[i].x * P[i].x + P[i].y * P[i].y -
                                        P[j].x * P[j].x - P[j].y * P[j].y)) /
                             (P[i].x * (P[j].y - P[k].y) +
                              P[j].x * (P[k].y - P[i].y) +
                              P[k].x * (P[i].y - P[j].y)));
                R = (LenghtLine(P[i], P[j]) * LenghtLine(P[j], P[k]) *
                     LenghtLine(P[k], P[i])) /
                    (4 * TriangleArea(P[i], P[j], P[k]));
                if (!PointInCircle(P, C, R)) {
                    continue;
                }
                if (R <= minR) {
                    minR = R;
                    minC = C;
                }
            }


    for (size_t i = 0; i < P.size() - 1; i++)

        for (size_t j = i + 1; j < P.size(); j++) {

            C.x = (P[i].x + P[j].x) / 2;
            C.y = (P[i].y + P[j].y) / 2;
            R = LenghtLine(C, P[i]);
            if (!PointInCircle(P, C, R)) {
                continue;
            }
            if (R <= minR) {
                minR = R;
                minC = C;
            }
        }
    std::cout << minC.x << " " << minC.y << std::endl;
    return minR;
}


void test() {
    std::vector<Point> Pv;
    Pv.push_back(Point(0, 0));
    Pv.push_back(Point(5, 4));
    Pv.push_back(Point(1, 3));
    Pv.push_back(Point(4, 1));
    Pv.push_back(Point(3, -2));
    std::cout << circle(Pv) << std::endl;
}


void test2() {
    std::vector<Point> Pv;
    Pv.push_back(Point(0, 0));
    Pv.push_back(Point(0, 2));
    Pv.push_back(Point(2, 2));
    Pv.push_back(Point(2, 0));
    std::cout << circle(Pv) << std::endl;
}


void test3() {
    std::vector<Point> Pv;
    Pv.push_back(Point(0.5, 1));
    Pv.push_back(Point(3.5, 3));
    Pv.push_back(Point(2.5, 0));
    Pv.push_back(Point(2, 1.5));
    std::cout << circle(Pv) << std::endl;
}


int main() {
    test();
    std::cout << std::endl;
    test2();
    std::cout << std::endl;
    test3();
    return 0;
}
