/******************************************************************************************
 * 辅助文件，用来将指定的文件写入映象文件的指定位置中
 * 编写：谢煜波
 * email：xieyubo@126.com
 * 使用方法
 * make_togethger 映象文件名 位置 欲写入的文件名
 *******************************************************************************************/

#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	char ch;
	unsigned int count = 0;
	if (argc == 1) {
		cout << "make_together object_file position source_file";
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
