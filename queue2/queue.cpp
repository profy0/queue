#include <iostream>
#include "queue.h"

queue::queue() {
	cnt = new int[3];
	for (int i = 0; i < 3; i++) cnt[i] = 0;
	front = nullptr;
	high = nullptr;
	medium = nullptr;
	low = nullptr;
}

queue::queue(const queue& other) {
	this->cnt = new int[3];
	for (int i = 0; i < 3; i++) this->cnt[i] = other.cnt[i];
	node* nowForOther = other.front;
	front = new node();
	front = nowForOther;
	high = new node();
	high = other.high;
	if(nowForOther!=nullptr) nowForOther = nowForOther->nxt;
	if (other.high != nullptr)
	while (nowForOther!= other.medium) {
		high->nxt = nowForOther;
		high = nowForOther;
		nowForOther = nowForOther->nxt;
	}
	medium = new node();
	medium = other.medium;
	if(nowForOther!=nullptr) nowForOther = nowForOther->nxt;
	if (other.high != nullptr) high->nxt = medium;
	if (other.medium != nullptr)
	while (nowForOther!= other.low) {
		medium->nxt = nowForOther;
		medium = nowForOther;
		nowForOther = nowForOther->nxt;
	}
	low = new node();
	low = other.low;
	if(nowForOther!=nullptr) nowForOther = nowForOther->nxt;
	if (other.medium != nullptr) medium->nxt = low;
	if (other.low != nullptr)
	while (nowForOther!= nullptr) {
		low->nxt = nowForOther;
		low = nowForOther;
		nowForOther = nowForOther->nxt;
	}
}

queue::queue(queue&& other)
	:front(other.front),
	high(other.high),
	medium(other.medium),
	low(other.low) {
	cnt = new int[3];
	for (int i = 0; i < 3; i++) cnt[i] = other.cnt[i];
	for (int i = 0; i < 3; i++) other.cnt[i] = 0;
	other.front = nullptr;
	other.high = nullptr;
	other.medium = nullptr;
	other.low = nullptr;
}

queue& queue::operator=(const queue& other) {
	if (&other == this) {
		return *this;
	}
	delete[] cnt;
	delete front;
	delete high;
	delete medium;
	delete low;
	this->cnt = new int[3];
	for (int i = 0; i < 3; i++) this->cnt[i] = other.cnt[i];
	node* nowForOther = other.front;
	front = new node();
	front = nowForOther;
	high = new node();
	high = other.high;
	if (nowForOther != nullptr) nowForOther = nowForOther->nxt;
	if (other.high != nullptr)
		while (nowForOther != other.medium) {
			high->nxt = nowForOther;
			high = nowForOther;
			nowForOther = nowForOther->nxt;
		}
	medium = new node();
	medium = other.medium;
	if (nowForOther != nullptr) nowForOther = nowForOther->nxt;
	if (other.high != nullptr) high->nxt = medium;
	if (other.medium != nullptr)
		while (nowForOther != other.low) {
			medium->nxt = nowForOther;
			medium = nowForOther;
			nowForOther = nowForOther->nxt;
		}
	low = new node();
	low = other.low;
	if (nowForOther != nullptr) nowForOther = nowForOther->nxt;
	if (other.medium != nullptr) medium->nxt = low;
	if (other.low != nullptr)
		while (nowForOther != nullptr) {
			low->nxt = nowForOther;
			low = nowForOther;
			nowForOther = nowForOther->nxt;
		}

	return *this;
}

queue& queue::operator=(queue&& other) {
	if (&other == this) {
		return *this;
	}
	delete[] cnt;
	delete front;
	delete high;
	delete medium;
	delete low;
	cnt = new int[3];
	for (int i = 0; i < 3; i++) cnt[i] = other.cnt[i];
	front = other.front;
	high = other.high;
	medium = other.medium;
	low = other.low;
	for (int i = 0; i < 3; i++) cnt[i] = 0;
	other.front = nullptr;
	other.high = nullptr;
	other.medium = nullptr;
	other.low = nullptr;
	return *this;
}

const int queue::countOfHigh() {
	return cnt[0];
}

const int queue::countOfMedium() {
	return cnt[1];
}

const int queue::countOfLow() {
	return cnt[2];
}

const int queue::countOfAll() {
	return cnt[0] + cnt[1] + cnt[2];
}

const bool queue::empty() {
	return countOfAll() == 0;
}

void queue::push(node el) {
	node* t = new node();
	t->x = el.x;
	t->pr = el.pr;
	int priority = el.pr;
	if (priority == 1) {							// high
		if (countOfHigh()) {
			high->nxt = t;
			if (countOfMedium()) t->nxt = medium; else t->nxt = low;
			high = t;
		}
		else {
			if (empty()) {
				front = t;
				high = t;
			}
			else {
				t->nxt = front;
				high = t;
				front = t;
			}
		}
	}
	if (priority == 2) {						// medium
		if (countOfMedium()) {
			t->nxt = low;
			medium->nxt = t;
			medium = t;
		}
		else {
			if (countOfHigh()) {
				medium = t;
				medium->nxt = high->nxt;
				high->nxt = medium;
			}
			else {
				if (empty()) {
					front = t;
					medium = t;
				}
				else {
					t->nxt = front;
					medium = t;
					front = t;
				}
			}
		}
	}
	if (priority == 3) {								// low
		if (countOfLow()) {
			low->nxt = t;
			low = t;
		}
		else {
			if (countOfMedium()) {
				low = t;
				medium->nxt = low;
			}
			else {
				if (countOfHigh()) {
					low = t;
					high->nxt = low;
				}
				else {
					front = t;
					low = t;
				}
			}
		}
	}
	cnt[el.pr - 1]++;			// the number of elements of each priority  
}

void queue::pop() {
	if (countOfAll() == 0) throw std::exception("Error! Empty queue!");
	cnt[front->pr - 1]--;
	if (front->nxt != nullptr) {
		if (front->pr == 1 && front->nxt->pr != 1) high = nullptr;
		if (front->pr == 2 && front->nxt->pr != 2) medium = nullptr;
		if (front->pr == 3 && front->nxt->pr != 3) low = nullptr;
	}
	front = front->nxt;
}

const node queue::aboutFront() {
	if (countOfAll() == 0) throw std::exception("Error! Empty queue!");
	return *front;
}