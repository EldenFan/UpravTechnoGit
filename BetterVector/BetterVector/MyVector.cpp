/*template<class T>
MyVector<T>::MyVector()
{
    data = nullptr;
    size = 0;
    capacity = 2;
}

template<class T>
MyVector<T>::~MyVector()
{
    delete[] data;
}

template<class T>
int MyVector<T>::GetSize()
{
    return size;
}

template<class T>
T& MyVector<T>::operator[](int index)
{
    if (index >= size)
    {
        throw std::runtime_error("index out of range!");
    }
    else
    {
        return data[index];
    }
}

template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& another)
{
    if (this != &another)
    {
        delete[] data;
        size = another.size;
        data = new T[capacity];
        capacity = another.capacity;
        std::copy(another.data, another.data + size, data);
    }
    return *this;
}

template <class T>
void MyVector<T>::PushBack(const T& append)
{
    if (capacity == size)
    {
        T* temp = new T[capacity * 2];
        capacity *= 2;
        std::copy(data, data + size, temp);
        delete[] data;
        data = temp;
    }
    data[size++] = append;
}

template <class T>
MyVector<T>::Iterator::Iterator(T* another)
{
    ptr = another;
}

template <class T>
T& MyVector<T>::Iterator::operator*() const
{
    return *ptr;
}

template <class T>
T* MyVector<T>::Iterator::operator->()
{
    return ptr;
}

template <class T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator++()
{
    ++ptr;
    return this;
}

template <class T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator++(int)
{
    Iterator temp = this;
    ++(*this);
    return temp;
}

template <class T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator--()
{
    --ptr;
    return this;
}

template <class T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator--(int)
{
    Iterator temp = this;
    --(*this);
    return temp;
}

template <class T>
bool operator == (const typename MyVector<T>::Iterator& a, const typename MyVector<T>::Iterator& b)
{
    return a.ptr == b.ptr;
}

template <class T>
bool operator != (const typename MyVector<T>::Iterator& a, const typename MyVector<T>::Iterator& b)
{
    return a.ptr != b.ptr;
}

template <class T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator+(std::ptrdiff_t n)
{
    return Iterator(ptr + n);
}

template <class T>
T& MyVector<T>::Iterator::operator[](std::ptrdiff_t n)
{
    return *(ptr + n);
}

template <class T>
typename MyVector<T>::Iterator MyVector<T>::begin()
{
    return Iterator(data);
}

template <class T>
typename MyVector<T>::Iterator MyVector<T>::end()
{
    return Iterator(data + size);
}

template <class T>
void MyVector<T>::Pop()
{
}
*/