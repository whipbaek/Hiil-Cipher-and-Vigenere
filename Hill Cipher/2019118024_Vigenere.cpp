#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string extractAlpha(string plaintext, vector<pair<int, bool>>& idxArr) {
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
string encryption(string plaintext, string key) {

	vector<pair<int, bool>> idxArr; // 알파벳의 위치와, 대소문자 여부 (true -> 대문자, false -> 소문자)
	string alphatext = ""; // 알파벳만 추출

	alphatext = extractAlpha(plaintext, idxArr); // extract alphabet and save idx

	int keyidx = 0;
	for (int i = 0; i < alphatext.size(); i++) {
		if (alphatext[i] + (key[keyidx]-64) > 'Z') {
			int remainder = alphatext[i] + (key[keyidx]-64) - 'Z';
			alphatext[i] = 64 + remainder;
		}
		else {
			alphatext[i] = alphatext[i] + (key[keyidx] - 64);
		}
		keyidx++;
		if (keyidx == key.size()) keyidx = 0;
	}

	vector<int> plainArr(alphatext.size());

	for (int i = 0; i < alphatext.size(); i++) {
		if (idxArr[i].second)
			plaintext[idxArr[i].first] = alphatext[i];
		else
			plaintext[idxArr[i].first] = tolower(alphatext[i]);

	}

	return plaintext;
}
string decryption(string plaintext, string key) {

	vector<pair<int, bool>> idxArr; // 알파벳의 위치와, 대소문자 여부 (true -> 대문자, false -> 소문자)
	string alphatext = ""; // 알파벳만 추출

	alphatext = extractAlpha(plaintext, idxArr); // extract alphabet and save idx

	int keyidx = 0;
	for (int i = 0; i < alphatext.size(); i++) {
		if (alphatext[i] - (key[keyidx] - 64) < 'A') {
			int remainder = 'A' - (alphatext[i] - (key[keyidx] - 64));
			alphatext[i] = 91 - remainder;
		}
		else {
			alphatext[i] = alphatext[i] - (key[keyidx] - 64);
		}
		keyidx++;
		if (keyidx == key.size()) keyidx = 0;
	}

	vector<int> plainArr(alphatext.size());

	for (int i = 0; i < alphatext.size(); i++) {
		if (idxArr[i].second)
			plaintext[idxArr[i].first] = alphatext[i];
		else
			plaintext[idxArr[i].first] = tolower(alphatext[i]);

	}

	return plaintext;
}

int main(void) {
	string plaintext = "ZY";
	string key = "BA";

	string en = encryption(plaintext, key);
	cout << "en : " << en << '\n';

	string de = decryption(en, key);
	cout << "de : " << de << '\n';

	return 0;
}