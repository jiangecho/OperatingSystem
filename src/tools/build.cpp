#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	char ch;
	argv++;
	unsigned int count = 0;
	if (argc == 1) {
		cout << "Usage: build target file..." << endl;
	} else {
		ofstream outfile(*argv++, ios_base::binary);
		for (int i = 2; i < argc; ++i) {
			ifstream infile(*argv++);
			while (infile.get(ch)) {
				outfile.put(ch);
				count++;
			}
			infile.close();
		}
		ch = 0;
		while (count++ != 1474560) {
			outfile.put(ch);
		}
		outfile.close();
	}
}
