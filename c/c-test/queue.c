





int count;




int main(int argc, char const *argv[])
{
    create();
    enque(5);

    return 0;
}

void create()
{
    head = NULL;
    tail = NULL;
}


void enque(int x)
{
    if (head == NULL)
    {
        head = (struct node *)malloc(sizeof(struct node));
        head->data = x;
        head->pre = NULL;
        tail = head;
    }
    else
    {
        tmp = (struct node *)malloc(sizeof(struct node));
        tmp->data = x;
        tmp->next = tail;
        tail = tmp;
    }
}


int deque()
{
    int returnData = 0;
    if (head == NULL)
    {
        printf("ERROR: Deque from empty queue.\n");
        exit(1);
    }
    else
    {
        returnData = head->data;
        if (head->pre == NULL)
            head = NULL;
        else
            head = head->pre;
        head->next = NULL;
    }
    return returnData;
}


int size() { return count; }
