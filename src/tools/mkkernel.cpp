/******************************************************************************************
 * �����ļ��������������õ��Ķ����ļ����ӳ�һ�� 1.44M �� img ӳ���ļ�
 * ��д��л�ϲ�
 * email��xieyubo@126.com
 * ʹ�÷���
 * make_pyos_kernel ӳ���ļ��� ��һ�������ӵ��ļ� �ڶ��������ӵ��ļ� �����������ӵ��ļ� ...
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
