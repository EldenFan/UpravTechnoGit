#include "MyVector.h"
#include <string>

template<class T>
MyVector<T>::MyVector()
{
    arr = nullptr;
    size = 0;
}

template<class T>
MyVector<T>::~MyVector()
{
    delete[] arr;
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
        throw std::string{"index out of range!"};
    }
    else
    {
        return arr[index];
    }
}

template<class T>
void MyVector<T>::Copy(const MyVector<T>& second)
{
    delete[] arr;

    size = second.size;
    arr = new T[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = second.arr[i];
    }
}

template<class T>
MyVector<T>::MyVector(const MyVector<T>& another)
{
    Copy(another);
}

template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& another)
{
    Copy(another);

    return *this;
}

template <class T>
void MyVector<T>::PushBack(T append)
{
    T* temp = new T[size + 1];

    for (int i = 0; i < size; i++)
    {
        temp[i] = arr[i];
    }
    temp[size] = append;

    delete[] arr;
    arr = temp;
    size++;
}

template <class T>
void MyVector<T>::Pop(int index)
{
    if (index >= size || index < 0)
    {
        throw std::string{"index out of range!"};
    }

    T* temp = new T[size - 1];

    for (int i = 0; i < size; i++)
    {
        if (i < index)
        {
            temp[i] = arr[i];
        }
        if (i > index)
        {
            temp[i - 1] = arr[i];
        }
    }

    delete[] arr;
    arr = temp;
    size--;
}