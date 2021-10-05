#include <iostream>

struct node {
    int data;
    node* next;
    node* prev;
};

class DoublyLinkedList {
private:
    int length;
    node* head;
    node* tail;

    bool isEmpty() {
        return length == 0;
    }

    bool hasOne() {
        return length == 1;
    }

    int removeLastOne() {
        int data = head->data;
        delete head;
        head = tail = nullptr;
        length = 0;
        return data;
    }

    void checkIndex(int index) {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index is out of the list range");
    }

    node* getNode(int index) {
        if (isEmpty())
            throw std::out_of_range("Empty list");
        checkIndex(index);
        node* tmp;

        if (index != 0 && length / index < 2) {
            tmp = tail;
            for (int i = length - 1; i > index; i--) {
                tmp = tmp->prev;
            }
        }
        else {
            tmp = head;
            for (int i = 0; i < index; i++) {
                tmp = tmp->next;
            }

        }
        return tmp;
    }

public:
    DoublyLinkedList() {
        head = tail = nullptr;
        length = 0;
    }

    ~DoublyLinkedList() {
        if (!isEmpty())
            clear();
    }

    DoublyLinkedList(const DoublyLinkedList& another) {
        head = tail = nullptr;
        length = 0;

        node* tmp = another.head;
        for (int i = 0; i < another.length; i++) {
            push(tmp->data);
            tmp = tmp->next;
        }
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& another) {
        if (this == &another)
            return *this;

        if (!isEmpty())
            clear();
        node* tmp = another.head;
        for (int i = 0; i < another.length; i++) {
            push(tmp->data);
            tmp = tmp->next;
        }
        return *this;
    }

    int getLength() {
        return length;
    }

    int push(int data) {
        node* newNode = new node{ data , nullptr , tail };
        if (isEmpty())
            head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
        return ++length;
    }

    int pop() {
        if (isEmpty())
            throw std::out_of_range("Empty list");

        if (hasOne())
            return removeLastOne();

        length--;
        int data = tail->data;
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        return data;
    }

    int unshift(int data) {
        node* newNode = new node{ data, head, nullptr };
        if (isEmpty())
            head = tail = newNode;
        else {
            head->prev = newNode;
            head = newNode;
        }
        return ++length;
    }

    int shift() {
        if (isEmpty())
            throw std::out_of_range("Empty list");

        if (hasOne()) {
            return removeLastOne();
        }

        int data = head->data;
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
        length--;
        return data;
    }

    int insert(int index, int data) {
        if (index == length)
            return push(data);

        if (index == 0)
            return unshift(data);

        node* target = getNode(index);
        node* newNode = new node{ data , target , target->prev };
        target->prev->next = newNode;
        target->prev = newNode;
        return ++length;
    }

    int remove(int index) {
        if (index == length - 1)
            return pop();

        if (index == 0)
            return shift();

        node* target = getNode(index);
        target->prev->next = target->next;
        target->next->prev = target->prev;
        int data = target->data;
        delete target;
        length--;
        return data;
    }

    int get(int index) {
        node* target = getNode(index);
        return target->data;
    }

    void set(int index, int data) {
        node* target = getNode(index);
        target->data = data;
    }

    int search(int data) {
        node* tmp = head;
        for (int i = 0; i < length; i++) {
            if (tmp->data == data)
                return i;
            tmp = tmp->next;
        }
        return -1;
    }

    void clear() {
        for (int i = 0; i < length; i++) {
            node* tmp = head->next;
            delete head;
            head = tmp;
        }
        length = 0;
        head = tail = nullptr;
    }

};