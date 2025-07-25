


typedef struct min_heap
{
    int *p;
    int size;
    int count;
} Heap;

Heap *create_heap(Heap *heap);
void down_heapify(Heap *heap, int index);
void up_heapify(Heap *heap, int index);
void push(Heap *heap, int x);
void pop(Heap *heap);
int top(Heap *heap);
int empty(Heap *heap);
int size(Heap *heap);

int main()
{
    Heap *head = create_heap(head);
    push(head, 10);
    printf("Pushing element : 10\n");
    push(head, 3);
    printf("Pushing element : 3\n");
    push(head, 2);
    printf("Pushing element : 2\n");
    push(head, 8);
    printf("Pushing element : 8\n");
    printf("Top element = %d \n", top(head));
    push(head, 1);
    printf("Pushing element : 1\n");
    push(head, 7);
    printf("Pushing element : 7\n");
    printf("Top element = %d \n", top(head));
    pop(head);
    printf("Popping an element.\n");
    printf("Top element = %d \n", top(head));
    pop(head);
    printf("Popping an element.\n");
    printf("Top element = %d \n", top(head));
    printf("\n");
    return 0;
}
Heap *create_heap(Heap *heap)
{
    heap = (Heap *)malloc(sizeof(Heap));
    heap->size = 1;
    heap->p = (int *)malloc(heap->size * sizeof(int));
    heap->count = 0;
    return heap;
}

void down_heapify(Heap *heap, int index)
{
    if (index >= heap->count)
        return;
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int leftflag = 0, rightflag = 0;

    int minimum = *((heap->p) + index);
    if (left < heap->count && minimum > *((heap->p) + left))
    {
        minimum = *((heap->p) + left);
        leftflag = 1;
    }
    if (right < heap->count && minimum > *((heap->p) + right))
    {
        minimum = *((heap->p) + right);
        leftflag = 0;
        rightflag = 1;
    }
    if (leftflag)
    {
        *((heap->p) + left) = *((heap->p) + index);
        *((heap->p) + index) = minimum;
        down_heapify(heap, left);
    }
    if (rightflag)
    {
        *((heap->p) + right) = *((heap->p) + index);
        *((heap->p) + index) = minimum;
        down_heapify(heap, right);
    }
}
void up_heapify(Heap *heap, int index)
{
    int parent = (index - 1) / 2;
    if (parent < 0)
        return;
    if (*((heap->p) + index) < *((heap->p) + parent))
    {
        int temp = *((heap->p) + index);
        *((heap->p) + index) = *((heap->p) + parent);
        *((heap->p) + parent) = temp;
        up_heapify(heap, parent);
    }
}

void push(Heap *heap, int x)
{
    if (heap->count >= heap->size)
        return;
    *((heap->p) + heap->count) = x;
    heap->count++;
    if (4 * heap->count >= 3 * heap->size)
    {
        heap->size *= 2;
        (heap->p) = (int *)realloc((heap->p), (heap->size) * sizeof(int));
    }
    up_heapify(heap, heap->count - 1);
}
void pop(Heap *heap)
{
    if (heap->count == 0)
        return;
    heap->count--;
    int temp = *((heap->p) + heap->count);
    *((heap->p) + heap->count) = *(heap->p);
    *(heap->p) = temp;
    down_heapify(heap, 0);
    if (4 * heap->count <= heap->size)
    {
        heap->size /= 2;
        (heap->p) = (int *)realloc((heap->p), (heap->size) * sizeof(int));
    }
}
int top(Heap *heap)
{
    if (heap->count != 0)
        return *(heap->p);
    else
        return INT_MIN;
}
int empty(Heap *heap)
{
    if (heap->count != 0)
        return 0;
    else
        return 1;
}
int size(Heap *heap) { return heap->count; }
