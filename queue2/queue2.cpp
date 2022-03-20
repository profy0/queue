#include <iostream>
#include <exception>
#include "queue.h";

using namespace std;

istream& operator>>(istream& in, prior& pr) {
	int now;
	if (in >> now) pr = static_cast<prior>(now);
	return in;
}

int main() {

	cout << "Enter the number of elements: ";
	int cnt = 0;
	cin >> cnt;
	queue q;
	cout << "Enter the elements(value priority(1 - HIGH, 2 - MEDIUM, 3 - LOW)): ";
	for (int i = 0; i < cnt; i++) {
		node n;
		int val;
		prior priority;
		cin >> val >> priority;
		n.x = val;
		n.pr = priority;
		q.push(n);
	}

	node ch;

	try {
		ch = q.aboutFront();
	}
	catch (exception t) {
		cerr << t.what();
		return 0;
	}

	cout << "Front - ";
	cout << "value: " << ch.x << " priority: " << ch.pr << "\n";

	cout << "Count of - ";
	cout << "all: " << q.countOfAll() << " high: " << q.countOfHigh() << " medium: " << q.countOfMedium() << " low: " << q.countOfLow() << "\n";

	cout << "Enter the number of deletions: ";
	cin >> cnt;

	try {
		for (int i = 0; i < cnt; i++) {
			q.pop();
		}
	}
	catch (exception t) {
		cerr << t.what();
		return 0;
	}

	cout << "Empty? ";
	cout << (q.empty() ? "Yes" : "No") << "\n";

	queue q3(q);

	cout << "Number of all for q: " << q.countOfAll() << "\n";
	cout << "Number of all for q3: " << q3.countOfAll() << "\n";

	queue q2 = move(q);

	cout << "Number of all for q: " << q.countOfAll() << "\n";
	cout << "Number of all for q2: " << q2.countOfAll() << "\n";

}