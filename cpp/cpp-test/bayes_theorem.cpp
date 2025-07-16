



double bayes_AgivenB(double BgivenA, double A, double B) {
    return (BgivenA * A) / B;
}


double bayes_BgivenA(double AgivenB, double A, double B) {
    return (AgivenB * B) / A;
}


int main() {
    double A = 0.01;
    double B = 0.1;
    double BgivenA = 0.9;
    double AgivenB = bayes_AgivenB(BgivenA, A, B);
    std::cout << "A given B = " << AgivenB << std::endl;
    std::cout << "B given A = " << bayes_BgivenA(AgivenB, A, B) << std::endl;
    return 0;
}
