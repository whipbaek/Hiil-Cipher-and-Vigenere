#include <bits/stdc++.h>
#define KEY_SZ 2 // 2 x 2 Matrix Key
using namespace std;


string encryption(string plaintext, string key) {
	string result = plaintext;
	vector<pair<int, bool>> idxArr; // ���ĺ��� ��ġ��, ��ҹ��� ���� (true -> �빮��, false -> �ҹ���)
	string alphatext = "";
	int keyArr[2][2] = { key[0] - 65, key[2] - 65, key[1] - 65, key[3] - 65 };
	int idx = 0;
	vector<int> valArr;

	// extract alphabet
	for (int i = 0; i < plaintext.size(); i++) {
		char val = plaintext[i];
		bool upper = false;
		if ((val >= 'a' && val <= 'z') || (val >= 'A' && val <= 'Z')) {
			if (val >= 'A' && val <= 'Z') upper = true;

			alphatext += toupper(val);
			idxArr.push_back(make_pair(i, upper));
		}
	}

	// making val vector
	for (char val : alphatext) { valArr.push_back(val - 65); }

	vector<int> modArr(alphatext.size());


	// encryption, 2���� ������ ���ش�.
	for (int i = 0; i < valArr.size(); i+=KEY_SZ) {
		int temp[2] = { valArr[i], valArr[i + 1] };
		for (int j = 0; j < KEY_SZ; j++, idx++) {
			for (int k = 0; k < KEY_SZ; k++) {
				modArr[idx] += temp[k] * keyArr[k][j];
			}
		}
	}

	for (int i = 0; i < modArr.size(); i++) {
		if (idxArr[i].second) { //�빮�ڶ��
			result[idxArr[i].first] = (modArr[i]%26) + 65;
		}
		else {
			result[idxArr[i].first] = tolower((modArr[i]%26) + 65);
		}
	}
	
	return result;
}

void decryption(string plaintext, string key) {
	string alphatext = ""; // ���ĺ��� ����
	vector<pair<int, bool>> idxArr; // ���ĺ��� ��ġ��, ��ҹ��� ���� (true -> �빮��, false -> �ҹ���)
	vector<int> valArr; // ��ȣȭ�� ���ĺ��� ���ڷ� ��ȯ�� ��

	// extract alphabet and Index ����
	for (int i = 0; i < plaintext.size(); i++) {
		char val = plaintext[i];
		bool upper = false;
		if ((val >= 'a' && val <= 'z') || (val >= 'A' && val <= 'Z')) {
			if (val >= 'A' && val <= 'Z') upper = true;

			alphatext += toupper(val);
			idxArr.push_back(make_pair(i, upper));
		}
	}

	// making val vector
	for (char val : alphatext) { valArr.push_back(val - 65); }

	double keyArr[2][2] = { (double)key[0] - 65, (double)key[2] - 65, 
							(double)key[1] - 65, (double)key[3] - 65 }; // Key

	double a, b, c, d;
	a = keyArr[0][0];
	b = keyArr[0][1];
	c = keyArr[1][0];
	d = keyArr[1][1];

	double val = 1 / (a*d - b*c); // val -> 1/(ad-bc)
	double reversArr[2][2] = { val * d, -(val * b), -(val * c), val * a }; //����ĸ����

	
	double result[2] = { reversArr[0][0] * valArr[0] + reversArr[1][0] * valArr[1], reversArr[0][1] * valArr[0] + reversArr[1][1] * valArr[1] };

	for (auto val : result) cout << val << " ";
	cout << '\n';

}

int main(void) {

	string plaintext = "AB";
	string key = "CEDB";
	cout << encryption(plaintext, key) << '\n';

	decryption("EB", key);

	//cout << encryption("SHORTEXAMPLE", "HILL") << '\n';

	return 0;
}