#pragma once
class BaseFunction
{
private:
	static HANDLE hStdOut;//HANDLE - � ������� ������������ ����� ��������� �� ����, ������� ����, ����������� �������
public:
	BaseFunction(){}
	BaseFunction(HANDLE hStdOut)
	{
		this->hStdOut = hStdOut;
	}
	//��������� �����
	void SetColor(enum Color text, enum Color background)
	{
		SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	}
	//��� ��������� �������
	void SetCursor(short x, short y)
	{
		COORD myCoords = { x,y };//�������������� ������������� ���������� ������ ���������
		SetConsoleCursorPosition(hStdOut, myCoords);
	}
	//��� ���������� �������
	void Hidecursor(bool Cursor)
	{
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 10;
		info.bVisible = Cursor;
		SetConsoleCursorInfo(consoleHandle, &info);
	}
	//��� ��������� ������� ������
	//int FontSize ������ ������
	void SetFontSize(int FontSize)
	{
		CONSOLE_FONT_INFOEX info = { 0 };
		info.cbSize = sizeof(info);
		info.dwFontSize.Y = FontSize;
		info.FontWeight = FW_NORMAL;
		wcscpy_s(info.FaceName, L"Lucida Console");

		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
	}
	//��� ���������� ��� ��������� ��������� ������ � �������
	void HighlightingText(bool flags) {
		DWORD prev_mode;
		HANDLE hInput;
		hInput = GetStdHandle(STD_INPUT_HANDLE);
		GetConsoleMode(hInput, &prev_mode);
		flags == true ? SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE)) :
			SetConsoleMode(hInput, ENABLE_QUICK_EDIT_MODE);
	}
	//��� ��������������� �����
	//const wchar_t* nameMusic - �������� ���� � ����� L"D://Music/file.wav"
	void Music(const wchar_t* nameMusic)
	{
		//���� ���� �� ����� ���� ������, ������� ������������� ���� �� ���������
		PlaySound(nameMusic, NULL, SND_FILENAME /*| SND_ASYNC*/);
		//SND_ASYNC ���� ��������������� ����������
	}
};
HANDLE BaseFunction::hStdOut = 0;
