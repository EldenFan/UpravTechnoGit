#include <iterator>
#include <iostream>
#include <algorithm>

template<class T>
class MyVector {
private:
	T* data;
	int size;
	int capacity;
	T* reallocate() {
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
		capacity = another.capacity;
		data = new T[capacity];
		size = another.size;
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
		if ((size & (size - 1)) == 0) {
			Rezise(size);
		}
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

	friend bool operator == (MyVector& a, MyVector& b) {
		if (a.GetSize() != b.GetSize()) {
			return false;
		}
		int n = a.GetSize();
		for (int i = 0; i < n; i++) {
			if (a[i] != b[i]) {
				return false;
			}
		}
		return true;
	}

	void Rezise(int n) {
		if (n < 0 || n > capacity) {
			throw std::runtime_error("Capacity out of range!");
		}
		int temp = n;
		if ((n & (n - 1)) != 0) {
			std::cerr << "Warning: The value of n is not a power of 2. The value will be close to the nearest largest power of 2" << std::endl;
			temp = 1;
			while (temp < n) {
				temp *= 2;
			}
		}
		if (temp == capacity) {
			std::cerr << "Vector is not rezised. It is already nearest largest power of 2" << std::endl;
			return;
		}
		T* arr = new T[temp];
		capacity = temp;
		size = temp;
		std::copy(data, data + size, arr);
		delete[] data;
		data = arr;
	}
};
