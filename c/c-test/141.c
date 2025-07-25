
bool hasCycle(struct ListNode *head)
{
    struct ListNode *fast = head, *slow = head;
    while (slow && fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
            return true;
    }
    return false;
}
