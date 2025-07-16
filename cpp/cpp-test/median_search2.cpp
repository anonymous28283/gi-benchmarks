





struct ListNode {
    int val{0};
    ListNode* next{nullptr};
    ListNode() = default;
    explicit ListNode(int x)
        : val(x) {}
    ListNode(int x, ListNode* next)
        : val(x),
          next(next) {
    }
};


namespace search {

namespace median_search2 {

ListNode* middleNode(ListNode* head) {
    if (!head) {
        return nullptr;
    }


    ListNode* fastptr = nullptr;
    ListNode* slowptr = fastptr = head;


    while (fastptr->next && fastptr->next->next) {
        slowptr = slowptr->next;
        fastptr = fastptr->next->next;
    }

    return (fastptr->next) ? slowptr->next : slowptr;
}

void deleteAll(const ListNode* const head) {
    if (head) {
        deleteAll(head->next);
        delete head;
    }
}
}
}


static void test() {
    auto* head1 = new ListNode;
    head1->val = 1;

    ListNode* temp = head1;
    for (int i = 2; i < 6; ++i) {

        auto* temp1 = new ListNode;
        temp1->val = i;


        temp->next = temp1;
        temp = temp1;
    }
    temp->next = nullptr;

    const ListNode* const median = search::median_search2::middleNode(head1);
    assert(3 == median->val);
    search::median_search2::deleteAll(head1);
    std::cout << "test case:1 passed\n";


    auto* head2 = new ListNode;
    head2->val = 1;

    ListNode* temp2 = head2;
    for (int i = 2; i < 7; ++i) {

        auto* temp3 = new ListNode;
        temp3->val = i;


        temp2->next = temp3;
        temp2 = temp3;
    }
    temp2->next = nullptr;

    const ListNode* const median1 = search::median_search2::middleNode(head2);
    assert(4 == median1->val);
    search::median_search2::deleteAll(head2);
    std::cout << "test case:2 passed\n";

    std::cout << "--All tests passed--\n";
}


int main() {
    test();
    return 0;
}
