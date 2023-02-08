#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string tong(string a, string b);
string xu_ly_tong(string a, string b);
string tru(string a, string b);
string xu_ly_tru(string a, string b);
string nhan(string a, string b);
string xu_ly_nhan(string a, string b);
string chia(string a, string b);
int so_sanh(string a, string b);
string xu_ly_chia(string a, string b);
string luy_thua(string a, string m);

string tong(string a, string b) {

	//Cân bằng 2 chuỗi
	while (a.size() < b.size()) a = '0' + a;
	while (a.size() > b.size()) b = '0' + b;

	int sum = 0;
	int mem = 0;
	//Thuật toán cộng
	for (int i = a.size() - 1; i >= 0; i--) {
		sum = int(a[i] - 48) + int(b[i] - 48) + mem;
		if (sum > 9) {
			a[i] = char(sum % 10 + 48);
			mem = 1;
		}
		else {
			a[i] = char(sum + 48);
			mem = 0;
		}
	}
	if (mem == 1) { a = '1' + a; }
	return a;
}

string xu_ly_tong(string a, string b) {
	if (a[0] != '-' && b[0] != '-') {
		return tong(a, b);
	}
	else if (a[0] == '-' && b[0] == '-') {
		a.erase(a.begin() + 0);//Xóa dấu -
		b.erase(b.begin() + 0);
		return '-' + tong(a, b);
	}
	else {
		if (a[0] == '-') {
			a.erase(a.begin() + 0);
			if (a.size() > b.size()) {
				return '-' + tru(a, b);
			}
			else if (a.size() < b.size()) {
				return tru(b, a);
			}
			else {
				for (int i = 0; i < a.size(); i++) {
					if (a[i] < b[i]) {
						return tru(b, a);
					}
				}
				return tru(a, b);
			}
		}
		else {
			b.erase(b.begin() + 0);
			if (a.size() > b.size()) {
				return '-' + tru(a, b);
			}
			else if (a.size() < b.size()) {
				return tru(b, a);
			}
			else {
				for (int i = 0; i < a.size(); i++) {
					if (a[i] < b[i]) {
						return tru(b, a);
					}
				}
				return tru(a, b);
			}
		}
	}
}

string tru(string a, string b) {
	bool kt_tru = true;
	//Xử lý chuỗi
	if (a.size() > b.size()) {
		while (a.size() > b.size()) {
			b = '0' + b;
		}
	}
	else if (a.size() < b.size()) {
		while (a.size() < b.size()) {
			a = '0' + a;
		}
		swap(a, b);
		kt_tru = false;
	}
	else if (a.size() == b.size()) {
		if (strcmp(a.c_str(), b.c_str()) == -1) {
			kt_tru = false;
			swap(a, b);
		}
	}
	//Thuật toán trừ
	int minus = 0;
	int mem = 0;
	for (int i = a.size() - 1; i >= 0; i--) {
		minus = int(a[i] - 48) - int(b[i] - 48) - mem;
		if (minus < 0) {
			a[i] = char(int(a[i] - 48) + 10 - int(b[i] - 48) + 48);
			mem = 1;
		}
		else {
			a[i] = char(minus + 48);
			mem = 0;
		}
	}
	//fix số 0 ở đầu chuỗi
	while (a[0] == '0' && a.size() > 1) {
		a.erase(a.begin() + 0);
	}
	if (kt_tru == false) { return '-' + a; }
	else { return a; }
}

string xu_ly_tru(string a, string b) {
	if (a[0] != '-' && b[0] != '-')return tru(a, b);
	else if (a[0] == '-' && b[0] == '-') {
		b.erase(b.begin() + 0);//Bỏ dấu -
		return xu_ly_tong(a, b);
	}
	else {
		if (a[0] == '-') {
			a.erase(a.begin() + 0);
			return '-' + xu_ly_tong(a, b);
		}
		else {
			b.erase(b.begin() + 0);//Bỏ dấu -
			return xu_ly_tong(a, b);
		}
	}
}

string nhan(string a, string b) {
	//------Setting------
	int na = a.size();
	int nb = b.size();
	int n = na + nb;
	int mem = 0;
	string final;

	//Thêm vào toàn bộ chuỗi final là kí tự 0, để có thể duyệt và thêm vào chuỗi
	for (int i = 0; i < n; i++) {
		final.push_back('0');
	}

	//------ Reverse String --------
	for (int i = 0; i < na / 2; i++) {
		swap(a[i], a[na - i - 1]);
	}
	for (int i = 0; i < nb / 2; i++) {
		swap(b[i], b[nb - i - 1]);
	}
	//----- Thuật toán nhân ----- 
	for (int i = 0; i < na; i++) {
		for (int j = 0; j < nb; j++) {
			int tempt = (int(final[i + j] - 48) + int(a[i] - 48) * int(b[j] - 48) + mem) % 10;
			mem = (int(final[i + j] - 48) + int(a[i] - 48) * int(b[j] - 48) + mem) / 10;
			final[i + j] = char(tempt + 48);
			if (j == nb - 1) { final[i + j + 1] = char(mem + 48); mem = 0; }
		}
	}

	//Xóa số 0 ở đầu
	while (final[n - 1] == '0' && n > 1) {
		final.pop_back();
		n--;
	}

	//Đảo chuỗi lại cho đúng
	for (int i = 0; i < final.size() / 2; i++) {
		swap(final[i], final[final.size() - i - 1]);
	}
	return final;
}

string xu_ly_nhan(string a, string b) {
	if (a[0] != '-' && b[0] != '-')return nhan(a, b);
	else if (a[0] == '-' && b[0] == '-') {
		a.erase(a.begin() + 0);//Bỏ dấu -
		b.erase(b.begin() + 0);//Bỏ dấu -
		return nhan(a, b);
	}
	else {
		if (a[0] == '-') {
			a.erase(a.begin() + 0);
			return '-' + nhan(a, b);
		}
		else {
			b.erase(b.begin() + 0);//Bỏ dấu -
			return '-' + nhan(a, b);
		}
	}
}

string chia(string a, string b) {
	/*
		25/5
		Ý tưởng là: cho i=0 nhân với 5 và tăng dần lên: 0*5, 1*5, 2*5,... 5*5 => i lúc đó là kết quả
	*/

	int k;
	k = so_sanh(a, b);
	if (k == -1) {
		string tempt = { '0' };
		return tempt;
	}
	else if (k == 0) {
		string tempt = { '1' };
		return tempt;
	}
	else {
		string i = { '0' };
		string h = { '1' };
		string t = { '1' };
		string c = { '1','0' };
		string r = to_string(a.size());
		string tempt1;
		string p;
		while (true) {
			p = luy_thua(c, xu_ly_tru(r, h));
			i = xu_ly_tong(i, p);
			tempt1 = xu_ly_nhan(i, b);
			k = so_sanh(a, tempt1);
			if (k == 1) {
				continue;
			}
			else if (k == -1) {
				i = xu_ly_tru(i, p);
				h = xu_ly_tong(h, t);
				if (so_sanh(h, r) == 1) {

					return i;
				}
			}
			else if (k == 0) {
				return i;
			}
		}
	}
}

string luy_thua(string a, string m) {
	string result = a;
	string tempt = { '1' };
	string tempt1 = { '0' };
	if (so_sanh(m, tempt1) == 0) {
		return tempt;
	}
	else if (so_sanh(m, tempt) == 0) {
		return result;
	}
	else {
		while (true) {
			result = xu_ly_nhan(result, a);
			m = xu_ly_tru(m, tempt);
			if (so_sanh(m, tempt) == 0) {
				return result;
			}
		}
	}
}

int so_sanh(string a, string b) {
	if (a.size() > b.size()) {
		return 1;
	}
	else if (a.size() < b.size()) {
		return -1;
	}
	else {
		return strcmp(a.c_str(), b.c_str());
	}
}

string xu_ly_chia(string a, string b) {
	if (a[0] != '-' && b[0] != '-')return chia(a, b);
	else if (a[0] == '-' && b[0] == '-') {
		a.erase(a.begin() + 0);//Bỏ dấu -
		b.erase(b.begin() + 0);//Bỏ dấu -
		return chia(a, b);
	}
	else {
		if (a[0] == '-') {
			a.erase(a.begin() + 0);
			return '-' + chia(a, b);
		}
		else {
			b.erase(b.begin() + 0);//Bỏ dấu -
			return '-' + chia(a, b);
		}
	}
}