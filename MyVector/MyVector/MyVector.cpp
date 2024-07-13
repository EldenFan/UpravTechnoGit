#include "MyVector.h"
#include<iostream>
#include <string>

template<class T>
MyVector<T>::MyVector()
{
    data = nullptr;
    size = 0;
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
        data = new T[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = another.data[i];
        }
    }
    return *this;
}

template<class T>
MyVector<T>::MyVector(const MyVector<T>& another)
{
    *this = another;
}

template <class T>
void MyVector<T>::PushBack(T append)
{
    T* temp = new T[size + 1];

    for (int i = 0; i < size; i++)
    {
        temp[i] = data[i];
    }
    temp[size] = append;

    delete[] data;
    data = temp;
    ++size;
}

template <class T>
void MyVector<T>::Pop(int index)
{
    if (index >= size || index < 0)
    {
        throw std::runtime_error("index out of range!");
    }

    T* temp = new T[size - 1];

    for (int i = 0; i < size; i++)
    {
        if (i < index)
        {
            temp[i] = data[i];
        }
        if (i > index)
        {
            temp[i - 1] = data[i];
        }
    }

    delete[] data;
    data = temp;
    size--;
}