#pragma once
template<class T>
class MyVector
{
private:
	T* arr;
	int size;
	void Copy(const MyVector<T>&);
public:
	MyVector();
	~MyVector();
	MyVector(const MyVector&);
	T& operator[] (int);
	int GetSize();
	MyVector<T>& operator =(const MyVector&);
	void PushBack(T);
	void Pop(int = size - 1);
};

template class MyVector<int>;

