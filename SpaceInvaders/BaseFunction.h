#pragma once
class BaseFunction
{
private:
	static HANDLE hStdOut;//HANDLE - С помощью дескприторов можно ссылаться на окна, объекты ядра, графические объекты
public:
	BaseFunction(){}
	BaseFunction(HANDLE hStdOut)
	{
		this->hStdOut = hStdOut;
	}
	//Установка цвета
	void SetColor(enum Color text, enum Color background)
	{
		SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	}
	//Для установки курсора
	void SetCursor(short x, short y)
	{
		COORD myCoords = { x,y };//инициализируем передаваемыми значениями объект координат
		SetConsoleCursorPosition(hStdOut, myCoords);
	}
	//Для отключения консоли
	void Hidecursor(bool Cursor)
	{
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 10;
		info.bVisible = Cursor;
		SetConsoleCursorInfo(consoleHandle, &info);
	}
	//Для устоновки размера шрифта
	//int FontSize размер шрифта
	void SetFontSize(int FontSize)
	{
		CONSOLE_FONT_INFOEX info = { 0 };
		info.cbSize = sizeof(info);
		info.dwFontSize.Y = FontSize;
		info.FontWeight = FW_NORMAL;
		wcscpy_s(info.FaceName, L"Lucida Console");

		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
	}
	//Для отключения или включения выделения текста в консоле
	void HighlightingText(bool flags) {
		DWORD prev_mode;
		HANDLE hInput;
		hInput = GetStdHandle(STD_INPUT_HANDLE);
		GetConsoleMode(hInput, &prev_mode);
		flags == true ? SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE)) :
			SetConsoleMode(hInput, ENABLE_QUICK_EDIT_MODE);
	}
	//Для воспроизведения звука
	//const wchar_t* nameMusic - передаем путь к файлу L"D://Music/file.wav"
	void Music(const wchar_t* nameMusic)
	{
		//Если файл не может быть найден, функция воспроизводит звук по умолчанию
		PlaySound(nameMusic, NULL, SND_FILENAME /*| SND_ASYNC*/);
		//SND_ASYNC Звук воспроизводится асинхронно
	}
};
HANDLE BaseFunction::hStdOut = 0;
