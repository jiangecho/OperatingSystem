/******************************************************************************************
 * �����ļ���������ָ�����ļ�д��ӳ���ļ���ָ��λ����
 * ��д��л�ϲ�
 * email��xieyubo@126.com
 * ʹ�÷���
 * make_togethger ӳ���ļ��� λ�� ��д����ļ���
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
