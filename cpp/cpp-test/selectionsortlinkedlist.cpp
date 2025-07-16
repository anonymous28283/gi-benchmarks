
using namespace std;


class node {
 public:
    int data;
    node *link;
    node(int d) {
        data = d;
        link = NULL;
    }
};


void print(node *head) {
    node *current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->link;
    }
    cout << endl;
}


node *createlist(int n) {
    node *head = NULL;
    node *t = NULL;
    for (int i = 0; i < n; i++) {
        node *temp = NULL;
        int num;
        cin >> num;
        temp = new node(num);
        if (head == NULL) {
            head = temp;
            t = temp;
            continue;
        }
        if (t->link == NULL)
            t->link = temp;
        t = temp;
    }
    return head;
}


void my_selection_sort_linked_list(node *&head) {
    node *min = head;




    node *current =
        min->link;
    node *previous = min;

    node *temp =
        NULL;










    while (
        min->link !=
        NULL)
    {



        while (current != NULL)


        {
            if (current->data < min->data)

            {
                if (temp == NULL)


                {
                    if (previous ==
                        min)
                    {

                        head = current;

                        min->link = current->link;
                        current->link = previous;
                        min = current;
                        current = previous->link;
                    } else

                    {

                        head = current;

                        previous->link = current->link;
                        current->link = min;
                        min = current;
                        current = previous->link;
                    }
                } else

                {
                    temp->link = current;
                    previous->link = current->link;
                    current->link = min;
                    min = current;
                    current = previous->link;
                }
            } else

            {
                previous = previous->link;
                current = current->link;
            }
        }




        temp = min;
        min = min->link;
        previous = min;
        current = min->link;
    }
}























int main() {
    node *head = NULL;
    int n;
    cout << "enter the no. of nodes : ";

    cin >> n;
    if (n == 0)
        return 0;
    head = createlist(n);
    cout << "original list is : ";
    print(head);
    my_selection_sort_linked_list(head);
    cout << "sorted list is : ";
    print(head);
    return 0;
}