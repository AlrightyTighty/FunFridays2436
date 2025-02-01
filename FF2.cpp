#include <iostream>

using namespace std;

struct ListNode {
	int value;
	ListNode* next;
	ListNode(int val) {
		value = val;
	}
};


struct ListNode2 {
	int value;
	int key;
	ListNode2* next;
	ListNode2(int val, int key) {
		value = val;
		this->key = key;
	}
};

ListNode* reverse(ListNode* head)
{
	ListNode* prev = nullptr;
	ListNode* cur = head;
	while (cur != nullptr)
	{
		ListNode* next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	return prev;
}

bool isPalindrome(ListNode* head)
{
	if (head == nullptr || head->next == nullptr)
		return true;
	// Split here
	ListNode* fast = head;
	ListNode* slow = head;
	int i = 0;
	while (fast != nullptr)
	{
		i++;
		fast = fast->next;
		if (i % 2 == 0)
			slow = slow->next;
	}
	ListNode* secondHalf = slow->next;
	slow->next = nullptr;
	secondHalf = reverse(secondHalf);
	// Compare both parts
	ListNode* firstHalf = head;
	while (firstHalf != nullptr && secondHalf != nullptr)
	{
		if (firstHalf->value != secondHalf->value)
			return false;
		firstHalf = firstHalf->next;
		secondHalf = secondHalf->next;
	}

	return true;

}

ListNode2* searchOrAdd(ListNode2* head, int key)
{
	if (head == nullptr)
		return new ListNode2(1, key);

//	cout << "Head not null" << endl;

	ListNode2* current = head;
	ListNode2* prev = nullptr;
	while (current != nullptr && current->key != key)
	{
		prev = current;
		current = current->next;
	}
	if (current != nullptr)
	{
		current->value += 1;
		return head;
	}
	prev->next = new ListNode2(1, key);
	return head;
}

ListNode2* countFrequency(ListNode* head)
{
	ListNode2* newHead = nullptr;
	while (head != nullptr)
	{
		newHead = searchOrAdd(newHead, head->value);
		head = head->next;
	}
	return newHead;
}

int main()
{
	ListNode* first = new ListNode(1);
	ListNode* second = new ListNode(2);
	ListNode* third = new ListNode(2);
	ListNode* fourth = new ListNode(1);
	first->next = second;
	second->next = third;
	third->next = fourth;
	cout << isPalindrome(first) << endl;
	first->next = second;
	second->next = third;
	third->next = fourth;
	ListNode2* newHead = countFrequency(first);
	while (newHead != nullptr) {
		cout << newHead -> value << endl;
		newHead = newHead -> next;
	}
	return 0;
}
