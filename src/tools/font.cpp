/******************************************************************************************
 * 辅助文件，用来获得所需要的字库
 * 编写：谢煜波
 * email：xieyubo@126.com
 * 使用方法
 * make_font 英文字库名 输出英文字库名 中文字库名 输出中文字库名
 *******************************************************************************************/

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
	char ch;
	unsigned int count = 0;
	if (argc != 5) {
		cout
				<< "make_font english_font_lib out_english_font_lib chinese_font_lib out_chinese_font_lib";
	} else {
		ofstream out_english_font(argv[2]);
		ofstream out_chinese_font(argv[4]);

		string english = "PYOS MADE IN CHINA";
		for (int i = 0; i < english.length(); ++i) {
			ifstream in_english_font(argv[1]);

			unsigned int pos = english[i] * 16;
			for (int j = 0; j < pos; ++j) {
				in_english_font.get(ch);
			}

			for (int j = 0; j < 16; ++j) {
				in_english_font.get(ch);
				out_english_font.put(ch);
			}

			in_english_font.close();
		}
		out_english_font.close();

		string chinese = "关机哈尔滨工业大学谢煜波";
		for (int i = 0; i < chinese.length(); i += 2) {
			ifstream in_chinese_font(argv[3]);
			unsigned char c1 = chinese[i];
			unsigned char c2 = chinese[i + 1];
			int q = c1 - 0xa0;
			int w = c2 - 0xa0;
			unsigned int pos = (94 * (q - 1) + (w - 1)) * 32;
			for (int j = 0; j < pos; ++j) {
				in_chinese_font.get(ch);
			}

			for (int j = 0; j < 32; ++j) {
				in_chinese_font.get(ch);
				out_chinese_font.put(ch);
			}
			in_chinese_font.close();
		}
		out_chinese_font.close();
	}
}
