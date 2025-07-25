






int CArrayTests()
{
    printf("\n");
    printf(" +-------------------------------------+\n");
    printf(" |                                     |\n");
    printf(" |               C Array               |\n");
    printf(" |                                     |\n");
    printf(" +-------------------------------------+\n");
    printf("\n");

    CArray *array = getCArray(10);

    int i;
    for (i = 0; i < array->size; i++)
    {
        insertValueCArray(array, i, i + 1);
    }
    printf("Entered array is:\n");
    displayCArray(array);
    printf("\nCode: %d\n", pushValueCArray(array, 11));

    for (i = 0; i < array->size; i++)
    {
        removeValueCArray(array, i);
    }

    displayCArray(array);

    printf("\nCode: %d", removeValueCArray(array, -1));
    printf("\nCode: %d\n", insertValueCArray(array, -1, 1));


    for (i = 0; i < array->size; i++)
    {
        insertValueCArray(array, i, i + 1);
    }
    eraseCArray(array);
    displayCArray(array);


    CArray *arr = getCArray(13);
    for (i = 0; i < arr->size; i++)
    {
        insertValueCArray(arr, i, i + 1);
    }
    displayCArray(arr);
    for (i = 0; i < arr->size / 2; i++)
    {
        switchValuesCArray(arr, i, arr->size - i - 1);
    }

    displayCArray(arr);


    reverseCArray(arr);

    displayCArray(arr);


    srand(time(NULL));
    CArray *barray = getCArray(20);
    for (i = 0; i < barray->size; i++)
    {
        insertValueCArray(barray, i, rand());
    }
    CArray *carray = getCopyCArray(barray);
    CArray *darray = getCopyCArray(barray);
    printf("\nNot sorted Array:");
    displayCArray(barray);

    printf("\nBubble Sort:");
    clock_t begin1 = clock();

    bubbleSortCArray(barray);
    clock_t end1 = clock();
    double time_spent1 = (double)(end1 - begin1) / CLOCKS_PER_SEC;
    displayCArray(barray);

    printf("\nSelection Sort:");
    clock_t begin2 = clock();

    selectionSortCArray(carray);
    clock_t end2 = clock();
    double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
    displayCArray(carray);

    printf("\nInsertion Sort:");
    clock_t begin3 = clock();

    insertionSortCArray(darray);
    clock_t end3 = clock();
    double time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
    displayCArray(carray);


    reverseCArray(barray);






    printf("\nTotal time spent for bubble sort: %lf seconds", time_spent1);
    printf("\nTotal time spent for selection sort: %lf seconds", time_spent2);
    printf("\nTotal time spent for insertion sort: %lf seconds", time_spent3);


    CArray *aarray = getCArray(1000);
    for (i = 0; i < aarray->size; i++)
    {
        insertValueCArray(aarray, i, rand() % 100);
    }

    int j = 24;
    printf("\nOccurrences of the number %d in the array: %d", j,
           valueOcurranceCArray(aarray, j));
    printf("\nAnd its positions:\n");
    CArray *positions = valuePositionsCArray(aarray, j);
    displayCArray(positions);

    printf("\nAll %d s", j);
    for (i = 0; i < positions->size; i++)
    {
        printf("\nPosition %d has a value of %d", positions->array[i],
               aarray->array[positions->array[i]]);
    }
    printf("\nThe list has a minimum value of %d and a maximum value of %d",
           findMinCArray(aarray), findMaxCArray(aarray));
    insertionSortCArray(aarray);


    free(arr);
    free(array);
    free(aarray);
    free(barray);
    free(carray);
    free(darray);
    printf("\n");
    return 0;
}
