#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

#define KEY_SZ 2 // 2 x 2 Matrix Key
using namespace std;

// text���� ���ĺ��� ����
string extractAlpha(string plaintext, vector<pair<int, bool>> &idxArr) {
	string alphatext = "";
	
	for (int i = 0; i < plaintext.size(); i++) {
		char val = plaintext[i];
		bool upper = false;
		if ((val >= 'a' && val <= 'z') || (val >= 'A' && val <= 'Z')) {
			if (val >= 'A' && val <= 'Z') upper = true;

			alphatext += toupper(val);
			idxArr.push_back(make_pair(i, upper));
		}
	}

	return alphatext;
}
// text�� ������ ��ȯ
vector<int> makevalVec(string alphatext) {
	vector<int> valArr;
	for (char val : alphatext) { valArr.push_back(val - 65); }
	return valArr;
}
//���� key ��ķ� ����� �����
vector<vector<int>> makereversArr(string key) {

	int keyArr[2][2] = { key[0] - 65, key[2] - 65, key[1] - 65, key[3] - 65 }; // Key

	int a, b, c, d;
	a = keyArr[0][0];
	b = keyArr[0][1];
	c = keyArr[1][0];
	d = keyArr[1][1];

	int temp = a * d - b * c;
	if (temp% 2 == 0) {
		cout << "������ �����ϴ�, �ٸ�Ű�� ����ϼ���.\n";
		exit(0);
	}

	if (temp < 0) 	temp = -(-temp % 26) + 26;
	else if (temp > 0) 	temp = temp % 26;
	
	int inverse;

	for (int i = 1;; i++) {
		if (temp * i % 26 == 1) {
			inverse = i;
			break;
		}
	}

	vector<vector<int>> reverseArr = {
		{ (keyArr[1][1]) % 26, -(keyArr[0][1] % 26) + 26 },
		{ -(keyArr[1][0] % 26) + 26, (keyArr[0][0]) % 26 }
	};

	for (int i = 0; i < KEY_SZ; i++) {
		for (int j = 0; j < KEY_SZ; j++) {
			reverseArr[i][j] = reverseArr[i][j] * inverse % 26;
		}
	}

	return reverseArr;
};
// ��ȣȭ, padding ��� �߰��ؾ���
string encryption(string plaintext, string key) {
	string result = plaintext; // �������� �� result
	vector<pair<int, bool>> idxArr; // ���ĺ��� ��ġ��, ��ҹ��� ���� (true -> �빮��, false -> �ҹ���)
	string alphatext = ""; // ���ĺ��� ����
	int keyArr[2][2] = { key[0] - 65, key[2] - 65, key[1] - 65, key[3] - 65 }; // Key Matrix
	int idx = 0;
	vector<int> valArr;

	alphatext = extractAlpha(plaintext, idxArr); // extract alphabet
	valArr = makevalVec(alphatext); // making val vector
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


	//original �ؽ�Ʈ�� ġȯ���ֱ�
	for (int i = 0; i < modArr.size(); i++) {
		if (idxArr[i].second) //�빮�ڶ��
			result[idxArr[i].first] = (modArr[i] % 26) + 65; 
		else result[idxArr[i].first] = tolower((modArr[i]%26) + 65);
	}
	return result;
}
// ��ȣȭ
string decryption(string plaintext, string key) {
	string result = plaintext; 
	string alphatext = ""; 
	vector<pair<int, bool>> idxArr; 
	vector<int> valArr; 
	vector<vector<int>> reverseArr;
	int idx = 0;

	alphatext = extractAlpha(plaintext, idxArr);
	valArr = makevalVec(alphatext);
	vector<int> modArr(alphatext.size());
	reverseArr = makereversArr(key); // ����� �����

	// 2���� ��ȣȭ
	for (int i = 0; i < valArr.size(); i += KEY_SZ) {
		int temp[2] = { valArr[i], valArr[i + 1] };
		for (int j = 0; j < KEY_SZ; j++, idx++) {
			for (int k = 0; k < KEY_SZ; k++) {
				modArr[idx] += temp[k] * reverseArr[k][j];
			}
		}
	}
	
	for (int i = 0; i < modArr.size(); i++) {
		if (idxArr[i].second) 
			result[idxArr[i].first] = (modArr[i] % 26) + 65;
		else 
			result[idxArr[i].first] = tolower((modArr[i] % 26) + 65);
	}

	return result;
}


/*
*   ***** caution *****
* 
*  Text : shortexample
*  Key  : HILL
* 
*  Text vector = { s, h, o, r, t, .... e }
* 
*	Key Matrix = | H L |    Not | H I |  !!!!!
*				 | I L |        | L L |  !!!!!
*/
int main(void) {

	vector<string> texts = { "ATTACK","shortexample","A1T25TACK", "Lemonade"};
	vector<string> keys = { "CDDG","HILL","CDDG", "DGEH"};
	for (int i = 0; i < texts.size(); i++) {
		cout << "Original Text : " << texts[i] << "\n";
		string entext = encryption(texts[i], keys[i]);
		cout << "Encryption : " << entext << "\n";

		string detext = decryption(entext, keys[i]);

		cout << "Decryption : " << detext << "\n\n";
		cout << "�ѤѤѤѤѤѤѤѤѤѤѤ�\n\n";
	}

	return 0;
}