// A design without factory pattern
#include <iostream>
using namespace std;

// Library classes
class Operator {
public:
	virtual void printOperator() = 0;
};
class Filter_edge_sobel_operator : public Operator {
public:
	void printOperator() {
		cout << "Sobel operator" << endl;
	}
};
class Filter_edge_prewitt_operator : public Operator {
	public:
	void printOperator() {
		cout << "Prewitt operator" << endl;
	}
};

// Creator (or user) class
class Creator {
public:
  Creator() {}
	~Creator() { }
  static Operator* create_operator(int type) {
    Operator * pOperator;

		// Creator explicitly creates classes according to type
		if (type == 1)
			pOperator = new Filter_edge_sobel_operator();
		else if (type == 2)
			pOperator = new Filter_edge_prewitt_operator();
		else
			pOperator = NULL;
    return pOperator;
	}
};

// Driver program
int main() {
	Operator * sobel_operator = Creator:: create_operator(1);
	sobel_operator->printOperator();

	Operator * prewitt_operator = Creator:: create_operator(2);
	prewitt_operator->printOperator();
	return 0;
}
