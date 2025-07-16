




long long collatz(long long start_num)
{
    long long length = 1;

    while (start_num != 1)
    {
        if (start_num & 0x01)
            start_num = 3 * start_num + 1;
        else
            start_num >>= 1;
        length++;
    }

    return length;
}


int main(int argc, char **argv)
{
    long long max_len = 0, max_len_num = 0;
    long long MAX_NUM = 1000000;

    if (argc ==
        2)
    {
        MAX_NUM = atoll(argv[1]);
        printf("Maximum number: %lld\n", MAX_NUM);
    }

    long long i;

    for (i = 1; i < MAX_NUM; i++)
    {
        long long L = collatz(i);
        if (L > max_len)
        {
            max_len = L;
            max_len_num = i;
        }

        printf("Thread: %2d\t %3lld: \t%5lld\n", omp_get_thread_num(), i, L);
    }

    printf("Start: %3lld: \tLength: %5lld\n", max_len_num, max_len);

    return 0;
}
