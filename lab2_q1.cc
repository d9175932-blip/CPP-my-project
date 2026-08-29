##include <iostream>
#include "args.h"

struct Node {
    int data;
    Node* next;
};

// Build the linked list from command-line arguments
Node* buildList(Args& args) {
    Node* head = nullptr;
    Node* tail = nullptr;

    while (args.has()) {
        int value = args.next<int>();

        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

// Print the linked list
void printList(Node* head) {
    Node* current = head;

    while (current != nullptr) {
        std::cout << current->data;

        if (current->next != nullptr) {
            std::cout << " ";
        }

        current = current->next;
    }

    std::cout << '\n';
}

// Part (a): Iterative reversal
// O(n) time and O(1) extra space
Node* reverseIterative(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;

    while (curr != nullptr) {
        Node* next = curr->next;

        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

// Part (b): Recursive reversal
Node* reverseRecursive(Node* head) {
    // Base case: empty list or one-node list
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    Node* newHead = reverseRecursive(head->next);

    head->next->next = head;
    head->next = nullptr;

    return newHead;
}

// Free all nodes
void deleteList(Node* head) {
    while (head != nullptr) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

int main(int argc, char* argv[]) {
    Args args(argc, argv);

    Node* head = buildList(args);

    // Part (a)
    head = reverseIterative(head);
    printList(head);

    // Part (b)
    head = reverseRecursive(head);
    printList(head);

    deleteList(head);

    return 0;
}
