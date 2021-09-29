#include <iostream>


class DynamicArray {
protected:
	size_t size;
	int* data;
	int length;

	void growIfNecessary() {

		if (length == (size + 1)) {
			size_t bound = size * 2;
			copyToNewSize(bound);
		}
	}

	void shrinkIfNecessary() {
		size_t bound = size / 2;
		if (length <= bound && size > 8)
			copyToNewSize(size / 2);
	}

	void copyToNewSize(size_t newSize) {
		int* temp = new int[newSize];
		for (int i = 0; i < length; i++) {
			temp[i] = data[i];
		}
		delete[] data;
		size = newSize;
		data = temp;
	}


	void checkIndex(int index) {
		if (index >= length || index < 0)
			throw std::out_of_range("Index is out of the array range!");
	}

	bool isEmpty() {
		return length == 0;
	}

	bool isDeletable() {
		if (isEmpty())
			throw std::out_of_range("Array is already empty!");
	}

public:
	DynamicArray(size_t startingSize = 8) {
		if (startingSize < 1)
			startingSize = 8;
		size = startingSize;
		data = new int[size];
		length = 0;
	}

	~DynamicArray() {
		delete[] data;
	}

	DynamicArray(const DynamicArray& another) {
		size = another.size;
		data = new int[size];
		length = another.length;
		for (int i = 0; i < length; i++)
			data[i] = another.data[i];
	}

	DynamicArray& operator=(const DynamicArray& another) {
		if (this == &another)
			return *this;

		delete[] data;
		size = another.size;
		data = new int[size];
		length = another.length;
		for (int i = 0; i < length; i++)
			data[i] = another.data[i];
		return *this;
	}

	int push(int value) {
		length++;
		growIfNecessary();
		data[length - 1] = value;

		return length;
	}

	int pop() {
		isDeletable();
		length--;
		int value = data[length];
		data[length] = NULL;
		shrinkIfNecessary();
		return value;
	}


	int insert(int index, int value) {
		checkIndex(index);
		length++;
		growIfNecessary();
		for (int i = (length - 1); i > index; i--) {
			data[i] = data[i - 1];
		}

		data[index] = value;
		return length;
	}

	int remove(int index) {
		isDeletable();
		checkIndex(index);
		int value = data[index];
		length--;
		for (int i = index; i < length; i++)
			data[i] = data[i + 1];
		shrinkIfNecessary();
		return value;
	}

	int get(int index) {
		checkIndex(index);
		return data[index];
	}

	void set(int index, int value) {
		checkIndex(index);
		data[index] = value;
	}

	int search(int value) {
		for (int i = 0; i < length; i++) {
			if (data[i] == value)
				return i;
		}
		return -1;
	}

	int getLength() {
		return length;
	}

};

