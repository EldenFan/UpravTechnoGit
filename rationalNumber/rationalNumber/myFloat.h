
class MyFloat 
{
protected:
	int n, d;
	void Norm();
	int gcdEuclid(int, int);
public:
	MyFloat(double);
	MyFloat(int, int);
	int GetNum();
	int GetDen();
	void Print();
	void Println();
};

MyFloat operator +(MyFloat x, MyFloat y);

MyFloat operator -(MyFloat x, MyFloat y);

MyFloat operator *(MyFloat x, MyFloat y);

MyFloat operator /(MyFloat x, MyFloat y);

