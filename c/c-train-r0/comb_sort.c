



void sort(int *numbers, int size)
{
    int gap = size;
    while (gap > 1)
    {
        gap = gap / SHRINK;
        int i = 0;
        while ((i + gap) < size)
        {
            if (numbers[i] > numbers[i + gap])
            {
                int tmp = numbers[i];
                numbers[i] = numbers[i + gap];
                numbers[i + gap] = tmp;
            }
            i++;
        }
    }
}

void display(int *array, int n)
{
    int i;
    for (i = 0; i < n; ++i) printf("%d ", array[i]);
    printf("\n");
}

int main()
{
    int size = 6;
    int *numbers = malloc(size * sizeof(int));
    printf("Insert %d unsorted numbers: \n", size);
    int i;
    for (i = 0; i < size; ++i) scanf("%d", &numbers[i]);
    printf("Initial array: ");
    display(numbers, size);
    sort(numbers, size);
    printf("Sorted array: ");
    display(numbers, size);
    free(numbers);
    return 0;
}
