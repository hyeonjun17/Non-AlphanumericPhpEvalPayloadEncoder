#include <iostream>
using namespace std;

void appendEncodedChar(string& encodedString, char ch);
void appendEncodedChar(string& encodedString, char ch, string& filterString);

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		cout << "./encoder.exe <payload> <character that application is filtering(if necessary)[format: \%c \%c ..]>" << endl;
		return -1;
	}

	string payloadString(argv[1]);
	string encodedString("");

	if (argc == 2) {
		for (int i = 0; i < payloadString.length() - 1; i++) {
			appendEncodedChar(encodedString, payloadString[i]);
			encodedString.append(".");
		}
		appendEncodedChar(encodedString, payloadString[payloadString.length() - 1]);
	}
	else {
		string filterString("");
		for (int i = 2; i < argc; i++) {
			filterString.append(argv[i]);
		}
		for (int i = 0; i < payloadString.length() - 1; i++) {
			appendEncodedChar(encodedString, payloadString[i], filterString);
			encodedString.append(".");
		}
		appendEncodedChar(encodedString, payloadString[payloadString.length() - 1], filterString);
	}

	cout << encodedString;

	return 0;
}

void appendEncodedChar(string& encodedString, char ch) {
	for (int i = 33; i <= 64; i++) {
		for (int j = 33; j <= 64; j++) {
			if ((i ^ j) == ch) {
				encodedString.append("('");
				char buffer[2] = { 0 };
				if (i == '\'') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = i;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)i;
					encodedString.append(buffer);
				}
				encodedString.append("'^'");
				if (j == '\'') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = j;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)j;
					encodedString.append(buffer);
				}
				encodedString.append("')");
				return;
			}
		}
		for (int j = 91; j <= 96; j++) {
			if ((i ^ j) == ch) {
				encodedString.append("('");
				char buffer[2] = { 0 };
				if (i == '\'') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = i;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)i;
					encodedString.append(buffer);
				}
				encodedString.append("'^'");
				if (j == '\\') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = j;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)j;
					encodedString.append(buffer);
				}
				encodedString.append("')");
				return;
			}
		}
		for (int j = 123; j <= 126; j++) {
			if ((i ^ j) == ch) {
				encodedString.append("('");
				char buffer[2] = { 0 };
				if (i == '\'') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = i;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)i;
					encodedString.append(buffer);
				}
				encodedString.append("'^'");
				buffer[0] = (char)j;
				encodedString.append(buffer);
				encodedString.append("')");
				return;
			}
		}
	}
	for (int i = 91; i <= 96; i++) {
		for (int j = 91; j <= 96; j++) {
			if ((i ^ j) == ch) {
				encodedString.append("('");
				char buffer[2] = { 0 };
				if (i == '\\') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = i;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)i;
					encodedString.append(buffer);
				}
				encodedString.append("'^'");
				if (j == '\\') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = j;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)j;
					encodedString.append(buffer);
				}
				encodedString.append("')");
				return;
			}
		}
		for (int j = 123; j <= 126; j++) {
			if ((i ^ j) == ch) {
				encodedString.append("('");
				char buffer[2] = { 0 };
				if (i == '\\') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = i;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)i;
					encodedString.append(buffer);
				}
				encodedString.append("'^'");
				buffer[0] = (char)j;
				encodedString.append(buffer);
				encodedString.append("')");
				return;
			}
		}
	}
	for (int i = 123; i <= 126; i++) {
		for (int j = 123; j <= 126; j++) {
			if ((i ^ j) == ch) {
				char buffer[10] = "(' '^' ')";
				buffer[2] = i;
				buffer[6] = j;
				encodedString.append(buffer);
				return;
			}
		}
	}
	char buffer[6] = "(' ')";
	buffer[2] = ch;
	encodedString.append(buffer);
	return;
}

void appendEncodedChar(string& encodedString, char ch, string& filterString) {
	for (int i = 33; i <= 64; i++) {
		if (filterString.find((char)i) != string::npos) {
			continue;
		}
		for (int j = 33; j <= 64; j++) {
			if (filterString.find((char)j) != string::npos) {
				continue;
			}
			if ((i ^ j) == ch) {
				encodedString.append("('");
				char buffer[2] = { 0 };
				if (i == '\'') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = i;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)i;
					encodedString.append(buffer);
				}
				encodedString.append("'^'");
				if (j == '\'') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = j;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)j;
					encodedString.append(buffer);
				}
				encodedString.append("')");
				return;
			}
		}
		for (int j = 91; j <= 96; j++) {
			if (filterString.find((char)j) != string::npos) {
				continue;
			}
			if ((i ^ j) == ch) {
				encodedString.append("('");
				char buffer[2] = { 0 };
				if (i == '\'') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = i;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)i;
					encodedString.append(buffer);
				}
				encodedString.append("'^'");
				if (j == '\\') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = j;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)j;
					encodedString.append(buffer);
				}
				encodedString.append("')");
				return;
			}
		}
		for (int j = 123; j <= 126; j++) {
			if (filterString.find((char)j) != string::npos) {
				continue;
			}
			if ((i ^ j) == ch) {
				encodedString.append("('");
				char buffer[2] = { 0 };
				if (i == '\'') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = i;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)i;
					encodedString.append(buffer);
				}
				encodedString.append("'^'");
				buffer[0] = (char)j;
				encodedString.append(buffer);
				encodedString.append("')");
				return;
			}
		}
	}
	for (int i = 91; i <= 96; i++) {
		if (filterString.find((char)i) != string::npos) {
			continue;
		}
		for (int j = 91; j <= 96; j++) {
			if (filterString.find((char)j) != string::npos) {
				continue;
			}
			if ((i ^ j) == ch) {
				encodedString.append("('");
				char buffer[2] = { 0 };
				if (i == '\\') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = i;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)i;
					encodedString.append(buffer);
				}
				encodedString.append("'^'");
				if (j == '\\') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = j;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)j;
					encodedString.append(buffer);
				}
				encodedString.append("')");
				return;
			}
		}
		for (int j = 123; j <= 126; j++) {
			if (filterString.find((char)j) != string::npos) {
				continue;
			}
			if ((i ^ j) == ch) {
				encodedString.append("('");
				char buffer[2] = { 0 };
				if (i == '\\') {
					char tmpBuffer[3] = { 0 };
					tmpBuffer[0] = '\\';
					tmpBuffer[1] = i;
					encodedString.append(tmpBuffer);
				}
				else {
					buffer[0] = (char)i;
					encodedString.append(buffer);
				}
				encodedString.append("'^'");
				buffer[0] = (char)j;
				encodedString.append(buffer);
				encodedString.append("')");
				return;
			}
		}
	}
	for (int i = 123; i <= 126; i++) {
		if (filterString.find((char)i) != string::npos) {
			continue;
		}
		for (int j = 123; j <= 126; j++) {
			if (filterString.find((char)j) != string::npos) {
				continue;
			}
			if ((i ^ j) == ch) {
				char buffer[10] = "(' '^' ')";
				buffer[2] = i;
				buffer[6] = j;
				encodedString.append(buffer);
				return;
			}
		}
	}
	char buffer[6] = "(' ')";
	buffer[2] = ch;
	encodedString.append(buffer);
	return;
}