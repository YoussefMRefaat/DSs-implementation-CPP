#include <iostream>

class Stack {
private:
    size_t size;
    int* data;
    unsigned int length;

    void growIfNecessary() {
        if (length >= size + 1) {
            size_t newSize = size * 2;
            copyToNewSize(newSize);
        }
    }

    void shrinkIfNecessary() {
        size_t bound = size / 2;
        if (length <= bound && size > 8)
            copyToNewSize(bound);
    }

    void copyToNewSize(size_t newSize) {
        int* tmp = new int[newSize];
        for (unsigned int i = 0; i < length; i++)
            tmp[i] = data[i];
        delete[] data;
        size = newSize;
        data = tmp;
    }

public:
    Stack(int startingSize = 8) {
        if (startingSize < 1)
            startingSize = 8;
        size = startingSize;
        length = 0;
        data = new int[size];
    }

    ~Stack() {
        delete[] data;
    }

    Stack(const Stack& another) {
        size = another.size;
        data = new int[size];
        length = another.length;
        for (unsigned int i = 0; i < length; i++)
            data[i] = another.data[i];
    }

    Stack& operator=(const Stack& another) {
        if (this == &another)
            return *this;

        delete[] data;
        size = another.size;
        data = new int[size];
        length = another.length;
        for (unsigned int i = 0; i < length; i++)
            data[i] = another.data[i];
        return *this;
    }

    bool isEmpty() {
        return length == 0;
    }

    int push(int value) {
        length++;
        growIfNecessary();
        data[length - 1] = value;
        return length;
    }

    int pop() {
        if (isEmpty())
            throw std::out_of_range("Empty array!");
        length--;
        int value = data[length];
        shrinkIfNecessary();
        return value;
    }

    int getLength() {
        return length;
    }

    int peek() {
        if (isEmpty())
            throw std::out_of_range("Empty array!");
        return data[length - 1];
    }

};
