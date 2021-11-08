#pragma once
#include "string"
#include "iostream"
#include "windows.h"
#include "sstream"
using namespace std;
class SMOKOT {
public:
	int string_to_int(string x)
	{

		std::stringstream ss;
		ss << x;
		int return_int = 0;
		ss >> return_int;
		return return_int;
	}

	char * int_to_char(int x)
	{
		char buff[2048] = "";
		cout << endl;
		itoa(x, buff, 10);
		return buff;
	}

	int char_to_int(char * x)
	{
		int out;
		out = atoi(x);
		return out;
	}



	char * string_to_char(std::string x) // оепебнд STRING б CHAR
	{
		int size = x.size(); size++;
		char * ch = new char[size];
		ZeroMemory(ch, size);
		for (int i = 0; i < size; i++) {
			ch[i] = x[i];
		}
		ch[size] = '\0';
		char * out = ch;
		//delete[] ch;
		return ch;
	}

	std::string char_to_string(char*x) // оепебнд CHAR б STRING
	{
		int size = strlen(x);
		std::string word = "";
		for (int i = 0; i < size; i++)
		{
			word += x[i];
		}
		return word;
	}
	void msg_box(LPCSTR word, LPCSTR title) // сопныеммши MessageBox
	{
		MessageBox(NULL, title, word, NULL);
	}

	void draw_dot(int x, int y, COLORREF ref, int pen_size)
	{
		HDC dc = GetWindowDC(GetForegroundWindow());

		HPEN pen = CreatePen(PS_SOLID, pen_size, ref);

		SelectObject(dc, pen);

		POINT point;

		MoveToEx(dc, x, y, &point);
		LineTo(dc, x, y);

	}
	void draw_line(int x, int y, int x2, int y2, COLORREF color, int pen_size)
	{
		HDC dc = GetWindowDC(GetForegroundWindow());

		HPEN pen = CreatePen(PS_SOLID, pen_size, color);

		SelectObject(dc, pen);

		POINT point;

		MoveToEx(dc, x, y, &point);
		LineTo(dc, x2, y2);

	}
	void draw_text(int x, int y, char * str)
	{
		HDC dc = GetWindowDC(GetForegroundWindow());

		TextOut(dc, x, y, str, strlen(str));
	}

};


