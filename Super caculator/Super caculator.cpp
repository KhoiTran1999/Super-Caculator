#include "tinh_toan.h"
#include <stack>
#include <queue>
//---------------------------
int kt_toan_tu(string a);
int kt_uu_tien(string a);
void trung_to_sang_hau_to(stack <string>& a, queue <string>& b, string c);
int so_toan_tu(string a);
void tinh_toan(stack <string>& a, queue <string> b);
//---------------------------
int main() {
	string c = { "" };
	cout << "Please fill an expression that includes unlimited Number, + - * / ( ):\nExample: 2+3*4/(4/4)\n\tExpresstion: ";
	cin >> c;
	stack <string>a;
	queue <string>b;
	trung_to_sang_hau_to(a, b, c);
	tinh_toan(a, b);
	cout << "\nresult: ";
	for (int i = 0; i < a.top().size(); i++) {
		if (a.top()[i] != ':') {//Fix lỗi in :
			cout <<  a.top()[i];//Xuất kết quả
		}
	}
	return 0;
}

int kt_uu_tien(string a) {
	if (a == "+" || a == "-") {
		return 1;
	}
	else if (a == "*" || a == "/") {
		return 2;
	}
	return 0;
}

int kt_toan_tu(string a) {
	if (a == "+" || a == "-" || a == "*" || a == "/" || a == "(" || a == ")") {
		return 0;
	}
	else {
		return 1;
	}
}

int so_toan_tu(string m) {
	if (m == "+") { return 1; }
	else if (m == "-") { return 2; }
	else if (m == "*") { return 3; }
	else if (m == "/") { return 4; }
}

void trung_to_sang_hau_to(stack <string>& a, queue <string>& b, string c) {
	if (c.front() == '-') { c.insert(c.begin() + 0, '0'); } //Nếu ở đầu c là dấu - thì thêm số 0 vô
	while (!c.empty()) {
		string m;//Truyền pt đầu của string c vào m

		while (c.front() >= 48 && c.front() <= 57) { //Trường hợp m là toán hạn
			m.push_back(c.front());
			c.erase(c.begin() + 0);
			if (c.size() == 0) { break; }
		}
		if (m.size() == 0) { //Trường hợp m là toán tử
			m.push_back(c.front());
			c.erase(c.begin() + 0);
		}

		//Test



		//Nếu m là toán hạn thì push vào Queue
		if (kt_toan_tu(m) != 0) {
			b.push(m);
		}
		//Nếu m là toán tử:
		else if (m == "+" || m == "-" || m == "*" || m == "/") {
			if (a.size() == 0) { //stack rỗng
				a.push(m);
			}
			else {//stack có pt
				if (kt_toan_tu(a.top()) == 1) {//pt đầu stack không phải là toán tử
					a.push(m);
				}
				else {//pt đầu stack là toán tử
					if (kt_uu_tien(m) > kt_uu_tien(a.top())) {//toán tử đang xét lớn hơn toán tử đầu stack
						a.push(m);
						continue;
					}
					while (kt_uu_tien(m) <= kt_uu_tien(a.top())) {//toán tử đang xét bé hơn hoặc bằng toán tử đầu stack
						b.push(a.top());
						a.pop();
						if (a.size() == 0 || kt_toan_tu(a.top()) == 1 || kt_uu_tien(m) > kt_uu_tien(a.top())) {
							a.push(m);
							break;
						}
					}
				}
			}
		}
		else if (m == "(") {//Nếu m là (
			a.push(m);
			if (c.front() == '-') {
				c.insert(c.begin() + 0, '0');
			}
		}
		else if (m == ")") {//Nếu m là )
			while (a.top() != "(") {//Chuyển tất cả pt trong ngoặc từ stack vào queue
				b.push(a.top());
				a.pop();
			}
			a.pop();//Xóa dấu mở ngoặc
		}
	}
	while (!a.empty()) {//Chuyển những pt còn sót lại vào Queue
		b.push(a.top());
		a.pop();
	}
}

void tinh_toan(stack <string>& a, queue <string> b) {
	while (!b.empty()) {
		string m = b.front();
		if (kt_toan_tu(m) != 0) {
			a.push(m);
		}
		else {
			string p1 = a.top(); a.pop();
			string p2 = a.top(); a.pop();
			int tempt = so_toan_tu(m);
			string p3;
			switch (tempt)
			{
			case 1: {
				p3 = xu_ly_tong(p2, p1);
				break;
			}
			case 2: {
				p3 = xu_ly_tru(p2, p1);
				break;
			}
			case 3: {
				p3 = xu_ly_nhan(p2, p1);
				break;
			}
			case 4: {
				p3 = xu_ly_chia(p2, p1);
				break;
			}
			}
			a.push(p3);
		}
		b.pop();
	}
}