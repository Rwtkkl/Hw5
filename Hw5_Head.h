#ifndef HW5_HEAD_H
#define HW5_HEAD_H

#include <iostream>
#include <string>
using namespace std;

class Shape {
	Shape* connect;
protected:
	virtual void draw() = 0;
public:
	Shape() { connect = NULL; }
	virtual ~Shape() { }
	void paint() { draw(); }
	void setconnect(Shape* p) { this->connect = p->connect; }
	Shape* getconnect() { return connect; }
	Shape* add(Shape* p) { this->connect = p; return p; }
};

class Circle : public Shape {
protected:
	virtual void draw() {
		cout << "Circle" << endl;
	}
};

class Line : public Shape {
protected:
	virtual void draw() {
		cout << "Line" << endl;
	}
};

class Rect : public Shape {
protected:
	virtual void draw() {
		cout << "Rectangle" << endl;
	}
};

class UI {
public:
	static int memu() {
		cout << "삽입:1, 삭제:2, 모두보기:3, 종료:4 >> ";
		int answer;
		cin >> answer;
		return answer;
	}
	static int menushape() {
		cout << "선:1, 원:2, 사각형:3 >> ";
		int answer;
		cin >> answer;
		return answer;
	}
	static int deleteindex() {
		cout << "삭제하고자 하는 도형의 인덱스 >> ";
		int answer;
		cin >> answer;
		return answer;
	}
};

class GraphicEditor {
	Shape* pStart;
	Shape* pLast;
	int count;

public:
	GraphicEditor() { pStart = NULL; count = 0; }
	void Add(int num) {
		switch (num) {
		case 1:
			if (count == 0) {
				pStart = new Line();
				pLast = pStart;
			}
			else
				pLast = pLast->add(new Line());
			count++;
			break;

		case 2:
			if (count == 0) {
				pStart = new Circle();
				pLast = pStart;
			}
			else
				pLast = pLast->add(new Circle());
			count++;
			break;

		case 3:
			if (count == 0) {
				pStart = new Rect();
				pLast = pStart;
			}
			else
				pLast = pLast->add(new Rect());
			count++;
			break;

		}
	}
	void Case() {
		cout << "그래픽 에디터입니다." << endl;
		while (true) {
			switch (UI::memu()) {
			case 1:
				Add(UI::menushape());
				break;
			case 2:
				Del(UI::deleteindex());
				break;
			case 3: {
				Shape* p = pStart;
				for (int i = 0; i < count; i++) {
					cout << i << ": "; p->paint();
					p = p->getconnect();
				}
				break;
			}
			case 4:
				return;

			}
		}
	}
	void Del(int num) {
		Shape* p = pStart;
		Shape* del = pStart;

		if (num < count) {
			for (int i = 0; i < num; i++) {
				p = del;
				del = del->getconnect();
			}
			if (num == 0)
				pStart = p->getconnect();
			else
				p->setconnect(del);
			count--;
			if (count == 1)
				pLast = pStart;
			delete del;

		}
	}
};

#endif