/******************************************************************************************
 * 辅助文件，用来将编译后得到的独立文件链接成一个 1.44M 的 img 映象文件
 * 编写：谢煜波
 * email：xieyubo@126.com
 * 使用方法
 * make_pyos_kernel 映象文件名 第一个被链接的文件 第二个被链接的文件 第三个被链接的文件 ...
 *******************************************************************************************/

#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	char ch;
	argv++;
	unsigned int count = 0;
	if (argc == 1) {
		cout << "make_pyos_kernel objfile sourcefile1 sourcefile2 ..." << endl;
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
