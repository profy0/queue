enum prior {UNKNOWN, HIGH, MEDIUM, LOW};

struct node {
	int x;
	prior pr;
	node* nxt;
	node() : x(0), pr(UNKNOWN), nxt(nullptr) {}
};

class queue {

private:
	int* cnt;
	node* front, * high, * medium, * low;

public:

	queue();

	//queue(const queue& other) 
	// good version of copy constructor
	queue(const queue& other);

	queue(queue&& other);

	queue& operator=(const queue& other);

	queue& operator=(queue&& other);

	const int countOfHigh();

	const int countOfMedium();

	const int countOfLow();

	const int countOfAll();

	const bool empty();
	void push(node el);
	void pop();
	const node aboutFront();

};