






int ways(int n, int *a, int k)
{
    if (n < 0 || k < 0)
        return 0;
    if (n == 0)
        return 1;
    if (k == 0)
        return 0;
    return ways(n, a, k - 1) + ways(n - a[k - 1], a, k);
}

int main()
{
    int m;
    int t;
    int n;

    printf("Number of coins? ");
    scanf("%d", &m);
    int *coin = (int *)malloc(m * sizeof(int)), i;
    for (i = 0; i < m; i++)
    {
        printf("coin? ");
        scanf("%d", &coin[i]);
    }

    printf("---- your requests --- \n");
    while (1)
    {
        printf("amount? exit(0) ");
        scanf("%d", &n);
        if (!n)
        {
            break;
        }
        printf("%d\n", ways(n, coin, m));
    }

    free(coin);
    return 0;
}
