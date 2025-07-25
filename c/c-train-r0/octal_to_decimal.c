



int convertValue(int num, int i) { return num * pow(8, i); }

long long toDecimal(int octal_value)
{
    int decimal_value = 0, i = 0;

    while (octal_value)
    {

        decimal_value += convertValue(octal_value % 10, i++);


        octal_value /= 10;
    }

    return decimal_value;
}

int main()
{
    printf("Enter octal value: ");

    int octal_value;

    scanf("%d", &octal_value);

    long long result = toDecimal(octal_value);

    printf("%d in decimal is %lld\n", octal_value, result);

    return 0;
}
