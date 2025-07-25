


int linearsearch(int *arr, int size, int val)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (arr[i] == val)
            return 1;
    }
    return 0;
}

int main()
{
    int n, i, v;
    printf("Enter the size of the array:\n");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));
    printf("Enter the contents for an array of size %d:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);


    printf("Enter the value to be searched:\n");
    scanf("%d", &v);
    if (linearsearch(a, n, v))
        printf("Value %d is in the array.\n", v);
    else
        printf("Value %d is not in the array.\n", v);

    free(a);
    return 0;
}
