

char get_perfect_number(unsigned long N)
{
    unsigned long sum = 1;
    char ret = 0;

    for (unsigned long i = 2; i * i <= N; i++)
    {
        if (N % i == 0)
        {
            sum += i;
            unsigned long tmp = N / i;
            if (tmp != i)
            {
                sum += tmp;
            }
        }
    }

    ret = sum == N ? 0 : (sum > N ? 1 : -1);



    return ret;
}


unsigned long is_abundant(unsigned long N)
{
    return get_perfect_number(N) == 1 ? 1 : 0;
}


unsigned long get_next_abundant(unsigned long N)
{
    unsigned long i;
    for (i = N + 1; !is_abundant(i); i++)
    {
        ;
    }
    return i;
}


char is_sum_of_abundant(unsigned long N)
{

    for (unsigned long i = get_next_abundant(1); i <= (N >> 1);
         i = get_next_abundant(i))
    {
        if (is_abundant(N - i))
        {
            printf("\t%4lu + %4lu = %4lu\n", i, N - i, N);
            return 1;
        }
    }
    return 0;
}


int main(int argc, char **argv)
{
    unsigned long MAX_N = 28123;

    unsigned long sum = 0;
    if (argc == 2)
    {
        MAX_N = strtoul(argv[1], NULL, 10);
    }



    double total_duration = 0.f;
    long i;

    for (i = 1; i <= MAX_N; i++)
    {
        clock_t start_time = clock();
        if (!is_sum_of_abundant(i))
        {
            sum += i;
        }
        clock_t end_time = clock();
        total_duration += (double)(end_time - start_time) / CLOCKS_PER_SEC;

        printf("... %5lu: %8lu\r", i, sum);
        if (i % 100 == 0)
        {
            fflush(stdout);
        }
    }

    printf("Time taken: %.4g s\n", total_duration);
    printf(
        "Sum of numbers that cannot be represented as sum of two abundant "
        "numbers : %lu\n",
        sum);

    return 0;
}
