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
	Creator(int type) {

		// Creator explicitly creates classes according to type
		if (type == 1)
			pOperator = new Filter_edge_sobel_operator();
		else if (type == 2)
			pOperator = new Filter_edge_prewitt_operator();
		else
			pOperator = NULL;
	}

	~Creator() {
		if (pOperator)
		{
			delete[] pOperator;
			pOperator = NULL;
		}
	}

	Operator* getOperator() {
		return pOperator;
	}
private:
	Operator *pOperator;
};

// Driver program
int main() {
	Creator *pCreator1 = new Creator(1);
	Operator * pOperator1 = pCreator1->getOperator();
	pOperator1->printOperator();

	Creator *pCreator2 = new Creator(2);
	Operator * pOperator2 = pCreator2->getOperator();
	pOperator2->printOperator();
	return 0;
}
