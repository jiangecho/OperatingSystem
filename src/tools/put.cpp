#include <fstream>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
	char ch;
	unsigned int count = 0;
	if (argc == 1) {
		cout << "Usage: put original position file";
	} else {
		unsigned int pos = atoi(argv[2]);
		ofstream outfile(argv[1], ios_base::in | ios_base::out);
		outfile.seekp(pos);
		ifstream infile(argv[3]);
		while (infile.get(ch)) {
			outfile.put(ch);
		}
		infile.close();
		outfile.close();
	}
}
