class Complex {
private:
	double mReal;
	double mImaginary;
public:
	double getReal();
	double getImaginary();
	Complex(double real, double imaginary); //constructor

	Complex operator+(const Complex& rhs); //+ overload
	Complex operator-(const Complex& rhs); //- overload
	Complex operator*(double rhs);         //* by constant overload
	double absoluteValue();
};
