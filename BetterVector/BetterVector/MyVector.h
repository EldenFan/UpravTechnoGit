#include <iterator>
#include <iostream>
#include <algorithm>

template<class T>
class MyVector {
private:
	T* data;
	int size;
	int capacity;
	T* reallocate()
	{
		capacity = capacity > 0 ? capacity * 2 : 1;
		T* temp = new T[capacity];
		return temp;
	}
public:
	MyVector() {
		data = nullptr;
		size = 0;
		capacity = 0;
	}

	~MyVector() {
		delete[] data;
	}

	int GetSize() {
		return size;
	}

	T& operator[] (int index) {
		if (index >= size) {
			throw std::runtime_error("index out of range!");
		}
		else {
			return data[index];
		}
	}

	MyVector<T>& operator =(const MyVector& another) {
		if (this != &another) {
			delete[] data;
			size = another.size;
			capacity = another.capacity;
			data = new T[capacity];
			std::copy(another.data, another.data + size, data);
		}
		return *this;
	 }

	MyVector(const MyVector& another) {
			delete[] data;
			size = another.size;
			capacity = another.capacity;
			data = new T[capacity];
			std::copy(another.data, another.data + size, data);
	}

	class Iterator {
	private:
		T* ptr;
	public:
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		Iterator(pointer element) {
			ptr = element;
		}

		reference operator*() const {
			return *ptr;
		}

		pointer operator -> () {
			return ptr;
		}

		Iterator& operator++() {
			++ptr;
			return *this;
		}

		Iterator operator++(int) {
			Iterator temp = *this;
			++(*this);
			return temp;
		}

		Iterator& operator--() {
			--ptr;
			return *this;
		}

		Iterator operator--(int) {
			Iterator temp = *this;
			--(*this);
			return temp;
		}

		Iterator operator+ (difference_type n) {
			return Iterator(ptr + n);
		}

		Iterator operator- (difference_type n) {
			return Iterator(ptr - n);
		}

		reference operator[](difference_type n) {
			return *(ptr + n);
		}

		friend bool operator == (const Iterator& a, const Iterator& b) {
			return a.ptr == b.ptr;
		}

		friend bool operator != (const Iterator& a, const Iterator& b) {
			return a.ptr != b.ptr;
		}

		friend bool operator < (const Iterator& a, const Iterator& b) {
			return a.ptr < b.ptr;
		}

		friend bool operator > (const Iterator& a, const Iterator& b) {
			return a.ptr > b.ptr;
		}

		friend difference_type operator - (const Iterator& a, const Iterator& b) {
			return a.ptr - b.ptr;
		}
	};

	Iterator begin() {
		return Iterator(data);
	}

	Iterator end() {
		return Iterator(data + size);
	}

	void Pop(Iterator place) {
		if (place < this->begin() || place > this->end()) {
			throw std::runtime_error("Iterator out of range!");
		}
		T* temp = new T[capacity];
		std::copy(this->begin(), place, temp);
		std::copy(place + 1, this->end(), temp + (place - this->begin()));
		--size;
		delete[] data;
		data = temp;
	}

	void Pop(int index) {
		if (index < 0 || index >= size) {
			throw std::runtime_error("Index out of range!");
		}
		Pop(this->begin() + index);
	}

	void Pop() {
		if (size == 0)
		{
			throw std::runtime_error("Vector is empty!");
		}
		Pop(size - 1);
	}

	void Push_back(const T& append) {
		if (capacity == size) {
			T* temp = reallocate();
			std::copy(this->begin(), this->end(), temp);
			delete[] data;
			data = temp;
		}
		data[size++] = append;
	}
};


