







static void test() {
    std::vector<geometry::grahamscan::Point> points = {
        {0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    std::vector<geometry::grahamscan::Point> expected_result = {
        {0, 3}, {4, 4}, {3, 1}, {0, 0}};
    std::vector<geometry::grahamscan::Point> derived_result;
    std::vector<geometry::grahamscan::Point> res;

    derived_result = geometry::grahamscan::convexHull(points, points.size());

    std::cout << "1st test: ";
    for (int i = 0; i < expected_result.size(); i++) {
        assert(derived_result[i].x == expected_result[i].x);
        assert(derived_result[i].y == expected_result[i].y);
    }
    std::cout << "passed!" << std::endl;
}


int main() {
    test();
    return 0;
}
