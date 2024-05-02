
class complex {
protected:
	double re, im;
public:
	complex(double r = 0, double i = 0) { re = r, im = i; }
	void print();
	friend complex operator+ (complex, complex);
	friend complex operator- (complex, complex);
	friend complex operator* (complex, complex);
	friend complex operator/ (complex, complex);
};