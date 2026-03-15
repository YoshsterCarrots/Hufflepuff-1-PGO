#include "/public/read.h" // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep
#include <iostream>       // IWYU pragma: keep
#include <fstream>        // IWYU pragma: keep
using namespace std;


int main() {
	ifstream videos("USvideos.csv");
	ofstream outputFile("titles.txt");
	string currLine;

	getline(videos, currLine);
	while (getline(videos, currLine)) {
		int commaCount = 0;
		bool isInQuote = false;
		for (char c : currLine) {
			if (commaCount > 2) {
				break;
			}
			else if (c == '"') {
				isInQuote = !isInQuote;
			}
			else if (!isInQuote && c == ',') {
				commaCount++;
			}
			else if (commaCount == 2) {
				outputFile << c;
			}
		}
		outputFile << '\n';
	}

	outputFile.close();
}
