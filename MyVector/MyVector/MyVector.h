#pragma once
template<class T>
class MyVector
{
private:
	T* data;
	int size;
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

