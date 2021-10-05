#include <iostream>

struct node {
    int data;
    node* next;
};

class Queue {
private:
    node* head;
    node* tail;
    size_t size;

public:
    Queue() {
        head = tail = nullptr;
        size = 0;
    }

    ~Queue() {
        if (!isEmpty()) {
            clear();
        }
    }

    Queue(const Queue& another) {
        node* tmp = another.head;
        while (tmp != nullptr) {
            enqueue(tmp->data);
            tmp = tmp->next;
        }
    }

    Queue& operator=(const Queue& another) {
        if (this == &another)
            return *this;

        clear();
        node* tmp = another.head;
        while (tmp != nullptr) {
            enqueue(tmp->data);
            tmp = tmp->next;
        }
        return *this;
    }

    size_t enqueue(int value) {
        node* newNode = new node{ value };
        if (isEmpty()) {
            newNode->next = nullptr;
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        return ++size;
    }

    int dequeue() {
        if (isEmpty())
            throw std::runtime_error("Empty array!");

        int value = head->data;
        node* tmp = head;
        head = head->next;
        delete tmp;
        size--;
        return value;
    }

    int peek() {
        if (isEmpty())
            throw std::runtime_error("Empty array!");

        return head->data;
    }

    bool isEmpty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }

    void clear() {
        unsigned int tmp = size;
        for (unsigned int i = 0; i < tmp; i++) {
            dequeue();
        }
    }

};
