

using namespace std;


cll::cll() {
    head = NULL;
    total = 0;
}

cll::~cll() {
}


void cll::display() {
    if (head == NULL)
        cout << "List is empty !" << endl;
    else {
        cout << "CLL list: ";
        node *current = head;
        for (int i = 0; i < total; i++) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << head->data << endl;
        cout << "Total element: " << total << endl;
    }
}


void cll::insert_front(int new_data) {
    node *newNode;
    newNode = new node;
    newNode->data = new_data;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
        head->next = head;
    } else {
        node *current = head;
        while (current->next != head) {
            current = current->next;
        }
        newNode->next = head;
        current->next = newNode;
        head = newNode;
    }
    total++;
}


void cll::insert_tail(int new_data) {
    node *newNode;
    newNode = new node;
    newNode->data = new_data;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
        head->next = head;
    } else {
        node *current = head;
        while (current->next != head) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = head;
    }
    total++;
}


int cll::get_size() { return total; }


bool cll::find_item(int item_to_find) {
    if (head == NULL) {
        cout << "List is empty !" << endl;
        return false;
    } else {
        node *current = head;
        while (current->next != head) {
            if (current->data == item_to_find)
                return true;
            current = current->next;
        }
        return false;
    }
}


int cll::operator*() { return head->data; }


void cll::operator++() {
    if (head == NULL) {
        cout << "List is empty !" << endl;
    } else {
        node *current = head;
        while (current->next != head) {
            current = current->next;
        }
        current->next = head->next;
        head = head->next;
    }
    total--;
}
