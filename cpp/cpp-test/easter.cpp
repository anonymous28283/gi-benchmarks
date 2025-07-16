






class EasterYearMonthDay {
 public:
    uint64_t year;
    uint64_t month;
    uint64_t day;

    EasterYearMonthDay(uint64_t newYear, uint64_t newMonth, uint64_t newDay) {
        year = newYear;
        month = newMonth;
        day = newDay;
    }
};


EasterYearMonthDay findEaster(uint64_t y) {
    if (y > 1582) {
        uint64_t a = y % 19;
        uint64_t b = y / 100;
        uint64_t c = y % 100;
        uint64_t d = b / 4;
        uint64_t e = b % 4;
        uint64_t f = (b + 8) / 25;
        uint64_t g = (b - f + 1) / 3;
        uint64_t h = (19 * a + b - d - g + 15) %
                     30;
        uint64_t i = c / 4;
        uint64_t k = c % 4;
        uint64_t r =
            (32 + 2 * e + 2 * i - h - k) %
            7;
        uint64_t m = (a + 11 * h + 22 * r) / 451;
        uint64_t n = (h + r - 7 * m + 114) / 31;
        uint64_t p = (h + r - 7 * m + 114) % 31;


        EasterYearMonthDay date(
            y, n, p + 1);


        return date;
    } else {
        EasterYearMonthDay date(0, 0, 0);


        return date;
    }
}


static void test() {

    assert(findEaster(2003).month == 4);
    assert(findEaster(2003).day == 20);


    assert(findEaster(1910).month == 3);
    assert(findEaster(1910).day == 27);


    assert(findEaster(1877).month != 3);
    assert(findEaster(1877).day != 22);


    assert(findEaster(1400).month == 0);
    assert(findEaster(1400).day == 0);
}


int main() {
    test();
    return 0;
}
