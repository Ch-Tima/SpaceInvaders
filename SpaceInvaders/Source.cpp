#include <iostream> // cout
#include<Windows.h>//Sleep(), COORD, HANDLE, SetConsoleTitle(), SetConsoleCP()...

#include <conio.h>//Работа с клавишами _getch
#include<fstream>//Работа с файлами
#include<string>//Работа со строками

#include<vector>//vector реализация динамического массива
#include<algorithm>//sort для сортировки Vector

#include <thread>//Для работы с потоками
#include<mutex> //"mutex" Cинхронизация потоков

#include <tchar.h> //Установка заголовка окна

//пространство имен std
using namespace std;


mutex mtx;//Для синхронизации потоков для совместной отрисоки изображения в консоли
#pragma comment(lib, "winmm")// Для звуков “Music()”

// enum - это спецификация списка имён, принадлежащих конкретному перечислению 
enum Color { Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };

enum Napravlenie { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, esc = 27, Space = 32, NumLock = 144 };
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//получает дискриптор активного окна
//HANDLE - С помощью дескприторов можно ссылаться на окна, объекты ядра, графические объекты

//Установка цвета
void SetColor(Color text, Color background)
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

struct User
{
	string Login;
	string Password;
	int score = 0;
};
// struct Sprites тут хранятся изображения Invader и всякие надписи
struct Sprites
{
	char InvadersTypeA[3][6] =
	{
			'.','.','.','.','.','.',
			'.','{','@','@','}','.',
			'.','/','"','"','\\','.'
	};
	char InvadersTypeB[3][6] =
	{
			'.','.','.','.','.','.',
			'.','d','o','o','b','.',
			'.','∆','/','\\','∆','.',
	};

	char InvadersTypeC[3][6] =
	{
		'.','.','.','.','.','.',
		'.','/','M','M','\\','.',
		'.','|','~','~','|','.'
	};
	char InvadersTypeG[3][8] =
	{
		'.','.','.','.','.','.','.','.',
		'.','_','/','M','M','\\','_','.',
		'.','q','w','A','A','w','p','.'
	};

	int GameOver[8][78] =
	{
0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,1,1,0,0,0,0,0,0,2,2,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,0,0,0,0,0,2,2,1,1,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,
2,1,1,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,1,1,0,2,2,1,1,2,2,1,1,2,2,1,1,0,1,1,2,2,2,1,1,2,1,1,0,0,0,0,0,0,2,1,1,2,1,1,0,0,0,2,1,1,0,1,1,2,2,2,1,1,2,2,1,1,2,2,1,
2,1,1,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,2,1,1,0,2,1,1,0,2,1,1,2,1,1,1,1,1,1,1,2,1,1,0,0,0,0,0,0,2,1,1,2,2,1,1,0,2,1,1,0,2,1,1,1,1,1,1,1,0,2,1,1,0,2,0,
2,2,1,1,0,0,2,2,2,2,1,1,0,1,1,2,2,2,2,1,1,0,0,2,1,1,0,2,1,1,0,2,1,1,2,1,1,2,2,2,2,0,2,2,1,1,0,0,0,0,0,1,1,0,0,2,2,1,1,1,1,0,0,2,1,1,2,2,2,2,0,0,2,1,1,0,0,0,
0,2,2,1,1,1,1,1,1,1,1,0,2,2,1,1,1,1,1,1,1,1,0,1,1,1,0,2,1,1,0,2,1,1,2,2,1,1,1,1,1,1,0,2,2,1,1,1,1,1,1,1,0,0,0,0,2,2,1,1,0,0,0,2,2,1,1,1,1,1,1,2,1,1,1,0,0,0,
0,0,2,2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,0,2,2,2,0,0,2,2,0,0,2,2,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,0,0,0,0,0,2,2,2,2,2,2,0,2,2,2,0,0,0,0
	};

	int YouWon[8][57] =
	{
0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,2,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,2,2,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,
0,0,2,2,1,1,0,0,0,0,1,1,2,2,2,2,1,1,2,1,1,0,0,2,1,1,0,0,2,2,1,1,0,0,1,0,2,1,1,0,1,1,2,2,2,2,1,1,2,2,1,1,2,2,2,1,1,
0,0,0,2,1,1,0,0,0,2,1,1,0,0,0,2,1,1,2,1,1,0,0,2,1,1,0,0,0,2,1,1,0,1,1,1,2,1,1,2,1,1,0,0,0,2,1,1,0,2,1,1,0,0,2,1,1,
0,0,0,2,1,1,0,0,0,2,1,1,0,0,0,2,1,1,2,1,1,0,0,2,1,1,0,0,0,2,1,1,1,1,2,1,1,1,1,2,1,1,0,0,0,2,1,1,0,2,1,1,0,0,2,1,1,
0,0,0,2,1,1,0,0,0,2,2,1,1,1,1,1,1,0,2,2,1,1,1,1,1,1,0,0,0,1,1,1,2,0,2,2,2,1,1,2,2,1,1,1,1,1,1,0,0,1,1,1,0,0,2,1,1,
0,0,0,2,2,0,0,0,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,0,0,0,2,2,2,0,0,0,0,2,2,2,0,0,2,2,2,2,2,2,0,0,2,2,2,0,0,0,2,2,0,
	};

	string NameGame[8] =
	{
	"  _____                            _____                         _                   \n",
	" / ____|                          |_   _|                       | |                  \n",
	"| (___   _ __    __ _   ___  ___    | |   _ __ __   __ __ _   __| |  ___  _ __  ___  \n",
	" \\___ \\ | '_ \\  / _` | / __|/ _ \\   | |  | '_ \\\\ \\ / // _` | / _` | / _ \\| '__|/ __| \n",
	" ____) || |_) || (_| || (__|  __/  _| |_ | | | |\\ V /| (_| || (_| ||  __/| |   \\__ \\ \n",
	"|_____/ | .__/  \\__,_| \\___|\\___| |_____||_| |_| \\_/  \\__,_| \\__,_| \\___||_|   |___/ \n",
	"        | |                                                                          \n",
	"        |_|                                                                          \n"
	};

};
// struct Shelter тут хранятся изображения убежища и параметры
struct Shelter
{
	int x, y;//Координаты
	//Размер убежища
	static const int SizeX = 7;
	static const int SizeY = 4;
	//убежище
	char shelter[SizeY][SizeX] =
	{
		'/','W','W','W','W','W','\\',
		'W','W','W','W','W','W','W',
		'W','W','.','.','.','W','W',
		'W','W','.','.','.','W','W'
	};
};

class LaserGun;

class Invaders
{
	char Invader[3][6];//Массив с внешним видом захватчика
	int Point;//Баллы
	COORD coordInvader;//координаты захватчика Invader
public:
	//Конструктор по умолчанию
	Invaders()
	{
		for (short i = 0; i < 3; i++)
		{
			for (short j = 0; j < 6; j++)
			{
				Invader[i][j] = '?';
			}
		}
		Point = 0;
		coordInvader.X = 0;
		coordInvader.Y = 0;
	}
	~Invaders()
	{

		Point = 0;
		coordInvader.X = 0;
		coordInvader.Y = 0;
	}
	//Запись внешнего вида захватчика
	void InvaderType(char InvaderSprites[3][6])
	{
		for (short i = 0; i < 3; i++)
		{
			for (short j = 0; j < 6; j++)
			{
				Invader[i][j] = InvaderSprites[i][j];
			}
		}
	}
	//Установка координат
	void setCoord(int x, int y)
	{
		coordInvader.X = x;
		coordInvader.Y = y;
	}
	//Установка баллов
	void setPoint(int Point = 0) { this->Point = Point; }


	void Clear()
	{
		for (short i = 0; i < 3; i++)
		{
			for (short j = 0; j < 6; j++)
			{
				mtx.lock();
				SetCursor(Black, Black);
				SetCursor(coordInvader.X + j, coordInvader.Y + i);
				cout << " ";
				mtx.unlock();
			}
		}
	}
	void Shoot(LaserGun& CoordPlayer, vector<Shelter>& shelter);
	//Отрисовка Invader
	void DrawInvaders()
	{
		int TempX, TempY;
		TempX = coordInvader.X;
		TempY = coordInvader.Y;


		for (short i = 0; i < 3; i++)
		{
			for (short j = 0; j < 6; j++)
			{
				mtx.lock();
				SetCursor(coordInvader.X + j, coordInvader.Y + i);
				Invader[i][j] == '.' ? SetColor(Black, Black) : SetColor(White, Black);
				cout << Invader[i][j];
				mtx.unlock();
			}
		}
	}
	//Возврат баллов
	int getPoint() { return Point; }
	//Возврат координат
	COORD getCoord() { return coordInvader; }
};
class MysteryShip
{
	//Внешний вид корабля
	char SpriteMysteryInvaders[3][8] =
	{
	'.','.','.','.','.','.','.','.',
	'.','_','/','M','M','\\','_','.',
	'.','q','w','A','A','w','p','.'
	};
	int Point;//Количество баллов за убийство
	COORD CoordMysteryInvaders;//Координаты корабля
	bool MoveLeft;
	bool Active;
	bool killed;
public:
	MysteryShip()
	{
		Point = 300;
		CoordMysteryInvaders.X = 90;
		CoordMysteryInvaders.Y = 4;
		MoveLeft = true;
		Active = false;
		killed = false;
	}
	~MysteryShip() {}

	void setKilled(bool killed) { this->killed = killed; }
	//Отрисовка и движения корабля
	void MovementMysteryShip()
	{
		Sleep(rand() % 4500);
		Active = true;
		int i = 0;
		if (MoveLeft == true)
		{

			do
			{
				if (i < 4)
				{
					thread music(Music, L"Music/ufo_lowpitch.wav");
					music.detach();
					++i;
				}
				for (short i = 0; i < 3; i++)
				{
					for (short j = 0; j < 8; j++)
					{
						mtx.lock();
						if (SpriteMysteryInvaders[i][j] == '.')
							SetColor(Black, Black);
						else
							SetColor(Red, Black);
						SetCursor(CoordMysteryInvaders.X + j, CoordMysteryInvaders.Y + i);
						cout << SpriteMysteryInvaders[i][j];
						mtx.unlock();
					}
				}
				Sleep(85);
				--CoordMysteryInvaders.X;
			} while (CoordMysteryInvaders.X > -1 && killed != true);
			if (CoordMysteryInvaders.X <= 0)
			{
				for (short i = 0; i < 3; i++)
				{
					for (short j = 0; j < 8; j++)
					{
						mtx.lock();
						SetColor(Black, Black);
						SetCursor(CoordMysteryInvaders.X + j, CoordMysteryInvaders.Y + i);
						cout << "x";
						mtx.unlock();
					}
				}
				MoveLeft = false;
			}

		}
		else
		{
			do
			{
				if (i < 4)
				{
					thread music(Music, L"Music/ufo_lowpitch.wav");
					music.detach();
					++i;
				}
				for (short i = 0; i < 3; i++)
				{
					for (short j = 0; j < 8; j++)
					{
						mtx.lock();
						if (SpriteMysteryInvaders[i][j] == '.')
							SetColor(Black, Black);
						else
							SetColor(Red, Black);
						SetCursor(CoordMysteryInvaders.X + j, CoordMysteryInvaders.Y + i);
						cout << SpriteMysteryInvaders[i][j];
						mtx.unlock();
					}
				}
				Sleep(85);
				++CoordMysteryInvaders.X;

			} while (CoordMysteryInvaders.X < 91 && killed != true);
			if (CoordMysteryInvaders.X >= 90)
			{
				for (short i = 0; i < 3; i++)
				{
					for (short j = 0; j < 8; j++)
					{
						mtx.lock();
						SetColor(Black, Black);
						SetCursor(CoordMysteryInvaders.X + j, CoordMysteryInvaders.Y + i);
						cout << "x";
						mtx.unlock();
					}
				}
				MoveLeft = true;
			}

		}

		if (killed == true)
		{
			for (short i = 0; i < 3; i++)
			{
				for (short j = 0; j < 8; j++)
				{
					mtx.lock();
					SetColor(Black, Black);
					SetCursor(CoordMysteryInvaders.X + j, CoordMysteryInvaders.Y + i);
					cout << "x";
					mtx.unlock();
				}
			}
			if (MoveLeft == true)
			{
				CoordMysteryInvaders.X = 0;
				MoveLeft = false;
			}
			else
			{
				CoordMysteryInvaders.X = 90;
				MoveLeft = true;
			}
			killed = false;
		}

		Active = false;
	}
	//Возврат количество баллов
	int getPoint() { return Point; }
	//Возврат информации, о активности корабля
	bool getActive() { return Active; }
	//Возврат координат корабля
	COORD getCoord() { return CoordMysteryInvaders; }
};
class LaserGun
{
	int lives;//количество жизни игрока
	int score;//количество баллов
	COORD Gun;//Координаты игрока

	int NumberShots;//количество выстрелов, каждые 14 выстрел появляется MysteryShip

	bool EndGame;

public:
	LaserGun()//Конструктор по умолчанию
	{
		lives = 3;
		score = 0;
		Gun.X = 25;
		Gun.Y = 35;
		NumberShots = 0;
		EndGame = false;
	}
	~LaserGun()
	{

	}
	//Установка координат игрока
	void setCoordGun(int x, int y)
	{
		Gun.X = x;
		Gun.Y = y;
	}
	//Для нанесения урона, Damage - количество урона
	void setDamage(int Damage = 1) { lives -= Damage; }
	//Добавление баллов игроку столько сколько было передано в int score
	void setScore(int score) { this->score += score; }
	void setNumberShots(int NumberShots = 0) { this->NumberShots = NumberShots; }
	void setEndGame(bool EndGame) { this->EndGame = EndGame; }


	/*Shoot
	* vector<Invaders>& invad массив где находятся экземпляры классов с захватчиками
	* vector<Shelter>& shelter массив где хранятся координаты и состояния убежищ
	* bool& obj для определения результата попал ли игрок в объект
	* MysteryShip& MysteryShip экземпляр класса с таинственным кораблем
	*/
	void Shoot(vector<Invaders>& invad, vector<Shelter>& shelter, bool& obj, MysteryShip& MysteryShip)
	{

		COORD Bullet;//Координаты пули
		//Центруем чтобы пуля вылетала ровно из дула
		Bullet.X = 3 + Gun.X;
		Bullet.Y = 1 + Gun.Y;
		do
		{
			mtx.lock();//mtx.lock() приостанавливает все другие потоки пока не исполнится вель код до mtx.unlock();
			//Отрисовка пули
			SetColor(White, Black);//Установка цвета текста и заднего фона
			SetCursor(Bullet.X, --Bullet.Y);//Установка курсора
			cout << "";
			//Стерам пулю
			SetCursor(Bullet.X, ++Bullet.Y);
			cout << " ";
			mtx.unlock();//Если не использовать mtx.lock(); и mtx.unlock(); то пуля может нарисовать не в том месте где надо

			--Bullet.Y;
			//Проверка если пуля за игровым полям
			if (Bullet.Y == 3)
			{
				obj = true;
			}
			//Если пуля возле убежища
			else if (Bullet.Y < 32 && Bullet.Y > 25)
			{
				for (short i = 0; i < shelter.size(); i++)
				{//Проверяем координаты убежищ и координаты пули на совпадения
					if (shelter[i].x <= Bullet.X && shelter[i].x + 6 >= Bullet.X && shelter[i].y <= Bullet.Y && shelter[i].y + 3 >= Bullet.Y && shelter[i].shelter[Bullet.Y - shelter[i].y][Bullet.X - shelter[i].x] != '.')
					{
						//Если координаты совпали то уничтожаем блох у убежища и заменить на пустоту
						shelter[i].shelter[Bullet.Y - shelter[i].y][Bullet.X - shelter[i].x] = '.';
						//Сообщаем что мы попали в объект
						obj = true;
						break;
					}
				}
			}
			//Если таинственный корабль октивен то ппроверяем мы попали в него
			else if (MysteryShip.getActive() == true && Bullet.Y > 1 && Bullet.Y < 7)
			{
				//Провекрат па попадания по MysteryShip
				if (MysteryShip.getCoord().X + 1 <= Bullet.X && MysteryShip.getCoord().X + 7 >= Bullet.X && 
					MysteryShip.getCoord().Y <= Bullet.Y && MysteryShip.getCoord().Y + 2 >= Bullet.Y)
				{
					//если true
					score += MysteryShip.getPoint();//добавляем игроку баллы
					obj = true;//Говорим что мы попали в объект
					MysteryShip.setKilled(true);
					break;
				}
			}
			//Если все остальные проверки не сработали проверить попали ли мы в Invader
			else
			{
				for (short i = 0; i < invad.size(); i++)
				{
					if (invad[i].getCoord().X + 1 <= Bullet.X && invad[i].getCoord().X + 4 >= Bullet.X && invad[i].getCoord().Y <= Bullet.Y && invad[i].getCoord().Y + 2 >= Bullet.Y)
					{
						//Включаем звук смерти Invaders
						thread music(Music, L"Music/invader_killed.wav");
						score += invad[i].getPoint();//добавляем игроку баллы
						invad[i].Clear();//Стерам захватчика
						invad.erase(invad.begin() + i);//Удаляем его из максима invad
						music.detach();//Завершить поток с музыкой
						music.~thread();
						obj = true;//Говорим что мы попали в объект
						break;
					}
				}
			}

			Sleep(40);
		} while (obj != true);
		mtx.lock();//Затерам пулю
		SetColor(Black, Black);
		SetCursor(Bullet.X, Bullet.Y);
		cout << "x";
		mtx.unlock();
		++NumberShots;//подсчет количества выстрелов, каждые 14 выстрелов появляется MysteryShip
	}

	//Отрисовка орудия
	void DrawLaserGun()
	{
		for (short i = 0; i < 3; i++)
		{
			for (short j = 0; j <= 6; j++)
			{
				mtx.lock();
				if (j == 0 || j == 6)
				{
					SetCursor(Gun.X + j, Gun.Y + i);
					SetColor(Black, Black);
					cout << "D";
				}
				else if (i == 0 && j != 3)
				{
					SetCursor(Gun.X + j, Gun.Y + i);
					SetColor(Black, Black);
					cout << "D";
				}
				else
				{
					SetCursor(Gun.X + j, Gun.Y + i);
					SetColor(Green, Green);
					cout << "D";
				}
				mtx.unlock();
			}
		}
	}

	//getLives() возвращает количество здоровья
	int getLives() { return lives; }
	//getScore() возвращает количество баллов
	int getScore() { return score; }
	//getNumberShots() возвращает количество выстрелов игроком
	int getNumberShots() { return NumberShots; }
	//getCoord() возвращает координаты игрока
	COORD getCoord() { return Gun; }
	bool getEndGame() { return EndGame; }
};
/*
* LaserGun& CoordPlayer ссылка на экземпляр class Laser Gun для определения координат игрока
* vector<Shelter>& shelter массив с координатами убежища для проверки на попадания пули
*/
void Invaders::Shoot(LaserGun& CoordPlayer, vector<Shelter>& shelter)
{
	bool obj = false;
	COORD Bullet;
	Bullet.X = 2 + coordInvader.X;
	Bullet.Y = 3 + coordInvader.Y;
	do
	{	//Отрисовка пули
		mtx.lock();
		SetColor(White, Black);
		SetCursor(Bullet.X, ++Bullet.Y);
		cout << "*";
		SetColor(Black, Black);
		SetCursor(Bullet.X, --Bullet.Y);
		cout << " ";
		++Bullet.Y;
		mtx.unlock();


		if (Bullet.Y == 38)//Если пуля за границей экрана
		{
			obj = true;
		}
		if (Bullet.Y < 34 && Bullet.Y > 27)//Если пуля возле убежища
		{
			for (short i = 0; i < shelter.size(); i++)
			{
				//Если попали в убежище
				if (shelter[i].x <= Bullet.X && shelter[i].x + 6 >= Bullet.X && shelter[i].y <= Bullet.Y && shelter[i].y + 3 >= Bullet.Y && shelter[i].shelter[Bullet.Y - shelter[i].y][Bullet.X - shelter[i].x] != '.')
				{
					shelter[i].shelter[Bullet.Y - shelter[i].y][Bullet.X - shelter[i].x] = '.';
					obj = true;
					break;
				}
			}
		}
		//проверка попали в игрока
		if (CoordPlayer.getCoord().X <= Bullet.X && CoordPlayer.getCoord().X + 5 >= Bullet.X && CoordPlayer.getCoord().Y == Bullet.Y)
		{
			CoordPlayer.setDamage(1);//Наносим урон игроку
			obj = true;//Говорим что мы попали в объект
			break;
		}
		Sleep(40);
	} while (obj != true);

	mtx.lock();//Затерам пулю
	SetColor(Black, Black);
	SetCursor(Bullet.X, Bullet.Y);
	cout << "x";
	mtx.unlock();

}

/*InvaderBehavior
* LaserGun? LG Ссылка на экземпляр класса
* vector<Invaders>& invad массив где находятся экземпляры классов с захватчиками
* vector<Shelter>& shelter массив где хранятся координаты и состояния убежищ
* MysteryShip& MysteryShip экземпляр класса с таинственным кораблем
*/
void InvaderBehavior(LaserGun& LG, vector<Invaders>& invad, vector<Shelter>& shelter, MysteryShip& MysteryShip)
{
	int movement = 0;//movement направление 0 - вправо, 1- в лево 
	int InvaderShoot;//номер Invader который будет стрелять
	bool CollisionObjPlayer = false;//Для проверки был ли удар по игроку

	int DescentInvaders = 0;

	
	do
	{
		if (LG.getNumberShots() > 14)
		{
			thread ActiveMysteryShip(&MysteryShip::MovementMysteryShip, ref(MysteryShip));
			LG.setNumberShots();
			ActiveMysteryShip.detach();
		}

		if (invad.size() > 0)
			InvaderShoot = rand() % invad.size();
		else
			break;
		
		//Движения вправо
		if (invad[invad.size() - 1].getCoord().X != 90 && movement == 0)
		{

			for (short i = 0; i < invad.size(); i++)
			{
				invad[i].setCoord(invad[i].getCoord().X + 1, invad[i].getCoord().Y);
				invad[i].DrawInvaders();

				//Если номер InvaderShoot == invad[i] то этот Invader стреляет
				if (i == InvaderShoot)
				{
					Invaders Invader = invad[i];
					thread shoot(&Invaders::Shoot, Invader, ref(LG), ref(shelter));//Запуск потока, в котором отрисовывается пуля и проверяется на попадания по объектам
					shoot.detach();
				}
			}
			//Движения вниз если добрались до границы
			if (invad[invad.size() - 1].getCoord().X >= 90 && movement != true)
			{
				for (short i = 0; i < invad.size(); i++)
				{
					invad[i].setCoord(invad[i].getCoord().X, invad[i].getCoord().Y + 1);
				}
				movement = 1;
				++DescentInvaders;
			}

		}

		//Движения влево
		if (invad[0].getCoord().X != 3 && movement == 1)
		{
			for (short i = 0; i < invad.size(); i++)
			{
				invad[i].setCoord(invad[i].getCoord().X - 1, invad[i].getCoord().Y);
				invad[i].DrawInvaders();

				//Если номер InvaderShoot == invad[i] то этот Invader стреляет
				if (i == InvaderShoot)
				{
					Invaders Invader = invad[i];
					thread shoot(&Invaders::Shoot, Invader, ref(LG), ref(shelter));//Запуск потока, в котором отрисовывается пуля и проверяется на попадания по объектам
					shoot.detach();
				}
			}
			//Движения вниз если добрались до границы
			if (invad[0].getCoord().X <= 3)
			{
				for (short i = 0; i < invad.size(); i++)
				{
					invad[i].setCoord(invad[i].getCoord().X, invad[i].getCoord().Y + 1);
				}
				movement = 0;
				++DescentInvaders;
			}
		}

		//CollisionObjPlayer == true, то есть если попали в игрока...
		if (CollisionObjPlayer == true)
		{
			LG.setDamage(1);//Уменьшаем здоровья у игрока
			CollisionObjPlayer = false;
		}


		//Изменения звука и скорости 
		if (DescentInvaders < 4)
		{
			thread music(Music, L"Music/fastinvader1.wav");
			Sleep(700);
			music.detach();
		}
		else if (DescentInvaders >= 4 && DescentInvaders <= 8)
		{
			thread music(Music, L"Music/fastinvader2.wav");
			Sleep(550);
			music.detach();
		}
		else if (DescentInvaders >= 9 && DescentInvaders <= 12)
		{
			thread music(Music, L"Music/fastinvader3.wav");
			Sleep(250);
			music.detach();
		}
		else
		{
			thread music(Music, L"Music/fastinvader4.wav");
			Sleep(75);
			music.detach();
		}
		//Проверка если Invader уже столкнулись с игроком
		if (invad.size() > 0 && invad[invad.size() - 1].getCoord().Y >= LG.getCoord().Y )
		{
			LG.setDamage(3);
			LG.setEndGame(true);
		}

	} while (LG.getLives() > 0 && invad.size() > 0 && LG.getEndGame() == false);
	MysteryShip.setKilled(true);
}

/* DrawObjShelter - отрисовка убежищ
* vector<Shelter>& shelter массив где хранятся координаты и параметры убежищ
*  bool &GameEnd - для остановки цикла после окончания игры
*/
void DrawObjShelter(vector<Shelter>& shelter, bool& GameEnd)
{
	int k = 0;
	while (GameEnd == false)
	{

		for (short i = 0; i < shelter[k].SizeY; i++)
		{
			for (short j = 0; j < shelter[k].SizeX; j++)
			{
				mtx.lock();
				shelter[k].shelter[i][j] == '.' ? SetColor(Black, Black) : SetColor(Green, Black);
				SetCursor(shelter[k].x + j, shelter[k].y + i);
				cout << shelter[k].shelter[i][j];
				mtx.unlock();
			}
		}

		++k;
		if (k == 4)
			k = 0;

		Sleep(200);
	}
}

/*Menu
* функция меню для вывода меню и работы с меню
* MenuItem массив пунктов меню
* X и Y для управления курсором...
* num или number количество пунктов в меню
*/
void Menu(string* MenuItem, short y, short x, short num, short coordYInHeight = 10)
{
	for (int i = 0; i < num; i++)
	{
		if (y == i)
		{
			SetColor(Red, Black);
			SetCursor(x, i + coordYInHeight);
			cout << ">" << MenuItem[i] << "<\n";
		}
		else
		{
			SetColor(White, Black);
			SetCursor(x, i + coordYInHeight);
			cout << " " << MenuItem[i] << " \n";
		}
	}
}

//DrawPlayerStats отображение показателей игрока
void DrawPlayerStats(LaserGun& LG)
{
	do
	{
		mtx.lock();
		SetColor(White, Black);
		SetCursor(20, 2);
		cout << "SCORE:" << LG.getScore();
		SetCursor(65, 2);
		cout << "HP:" << LG.getLives();
		mtx.unlock();
		Sleep(250);
	} while (LG.getLives() > 0 && LG.getEndGame() == false);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));
	Hidecursor(FALSE);//Отключения курсора в консоли

	SetConsoleTitle(_T("Space Invaders"));//Установка заголовка окна

	SetFontSize(16);//установка размера шрифта
	system("mode con cols=78 lines=32");//Установка размера окна

	int key;//для хранения ID клавиш
	int x, y;

	//Авторизацция и Регистрация//
	fstream ReaderWriter;//Для чтения и записи файла
	ifstream reader;//Для чтения файла
	ofstream writer;//Для записи в файл

	User UserObj;
	vector<User>US;//Масси игроков для рейтинговой таблицы...
	string Login;//Тут временно хранится Логин пользователя

	Sprites DrawSprites;//struct Sprites тут хранятся изображения Invader и всякие надписи



	//Проверка на существования файла
	reader.open("Users.txt");//Открытия файла для чтения
	if (reader.is_open() == false)//Если файла нет то он создается
		ofstream("Users.txt");
	reader.close();//Закрытие файла

	//=//Тут происходит авторизация и регистрация//=//
	string AuthorizRegist[2] = { "Авторизацию","Регистрация" };//Пункты меню для функции Menu
	bool successfully = false;
	x = 25, y = 0;
	while (successfully == false)
	{
		do//Выбор авторизация или регистрация
		{
			Menu(AuthorizRegist, y, x, 2);
			key = _getch();
			switch (key)
			{
			case Up:
				if (y > 0)
					y--;
				break;
			case Down:
				if (y < 1)
					y++;
				break;
			}
		} while (key != Enter);
		system("cls");
		SetColor(White, Black);
		//Авторизацию
		if (y == 0)
		{
			Hidecursor(TRUE);
			do
			{
				reader.open("Users.txt");//открытия файла на чтения
				string login;
				string pas;
				//Ввод логина и пароля
				SetCursor(x, 10);
				cout << "Авторизация\n";
				SetCursor(x, 11);
				cout << "LOGIN: ";
				getline(cin, login);
				SetCursor(x, 12);
				cout << "PASSWORD: ";
				getline(cin, pas);

				if (reader.peek() != EOF)
				{
					while (!reader.eof())//читаем пока не конец файла
					{
						reader >> UserObj.Login >> UserObj.Password >> UserObj.score;
						US.push_back(UserObj);
						//Проверка на совпадения
						if (UserObj.Login == login && UserObj.Password == pas)
						{
							Login = UserObj.Login;
							successfully = true;
						}
					}
				}
				if (successfully == false)
				{
					US.erase(US.begin(), US.end());//Очистка
					cout << "Error!\n";
					cout << "Для выхода из этого режима нажмите ESC или Enter чтобы продолжить\n";
					key = _getch();
				}
				reader.close();
				system("cls");
			} while (key != esc && successfully != true);
		}
		//Регистрация
		if (y == 1)
		{
			Hidecursor(TRUE);
			bool test = false, SuccesRegis = false;//Successful registration
			while (SuccesRegis == false)
			{
				string login;
				string password;
				//Ввод логина и пароля
				SetCursor(x, 10);
				cout << "Регистрация\n";
				SetCursor(x, 11);
				cout << "LOGIN: ";
				getline(cin, login);
				SetCursor(x, 12);
				cout << "PASSWORD: ";
				getline(cin, password);
				reader.open("Users.txt");
				while (!reader.eof())
				{
					reader >> UserObj.Login >> UserObj.Password >> UserObj.score;
					if (login == UserObj.Login)//Проверка на совпадения одинаково Логина
						test = true;
				}
				reader.close();
				if (test == false)
				{
					writer.open("Users.txt", ios::app);//Добавления пользователя в базу
					writer << login << " " << password << " " << UserObj.score << '\n';
					writer.close();
					SuccesRegis = true;
				}
				if (test == true)
				{
					cout << "Error!\n";
					cout << "Для выхода из этого режима нажмите ESC или Enter чтобы продолжить\n";
					key = _getch();
					if (key == esc)
					{
						system("cls");
						break;
					}
					Sleep(500);
					test = false;
					system("cls");
				}
			}
		}
		system("cls");
	}

	US.erase(US.end() - 1);

	//Сортировка Игроков для рейтинговой таблицы
	sort(US.rbegin(), US.rend(), [](const User& dot1, const User& dot2) -> bool
		{
			return dot1.score < dot2.score;
		});
	Hidecursor(FALSE);//Отключения курсора в консоли

	//Основной цикл игры
	while (successfully == true)
	{
		SetFontSize(16);
		system("mode con cols=78 lines=32");//Установка размера консоли

		system("cls");//Очистка консоли

		//Меню//
		SetColor(White, Black);
		for (short i = 0; i < 8; i++)
		{
			SetCursor(0, 2 + i);
			cout << DrawSprites.NameGame[i];
		}


		x = 30, y = 0;
		string MenuItems[3] = { "Play","Rating Table","Exit" };//Пункты меню
		bool startGame = false;
		do
		{
			do
			{
				Menu(MenuItems, y, x, 3);
				key = _getch();

				switch (key)
				{
				case Up:
					if (y > 0)
						--y;
					break;
				case Down:
					if (y < 2)
						++y;
					break;
				}

				Sleep(10);
			} while (key != Enter);
			switch (y)
			{
			case 0:
			{
				system("cls");
				SetColor(White, Black);
				for (short i = 0; i < 8; i++)
				{
					SetCursor(0, 2 + i);
					cout << DrawSprites.NameGame[i];
				}
				for (short k = 0; k < 3; k++)
				{
					for (short i = 0; i < 3; i++)
					{
						for (short j = 0; j < 6; j++)
						{
							SetCursor(j + 25, 15 + i + 4 * k);
							if (k == 0)
							{
								if (DrawSprites.InvadersTypeA[i][j] == '.')
									SetColor(Black, Black);
								else
									SetColor(White, Black);
								cout << DrawSprites.InvadersTypeA[i][j];
								if (i == 1)
								{
									SetColor(White, Black);
									SetCursor(j + 26, 15 + i + 4 * k);
									cout << " = 30 Point";
								}
							}
							if (k == 1)
							{
								if (DrawSprites.InvadersTypeB[i][j] == '.')
									SetColor(Black, Black);
								else
									SetColor(White, Black);
								cout << DrawSprites.InvadersTypeB[i][j];
								if (i == 1)
								{
									SetColor(White, Black);
									SetCursor(j + 26, 15 + i + 4 * k);
									cout << " = 20 Point";
								}
							}
							if (k == 2)
							{
								if (DrawSprites.InvadersTypeC[i][j] == '.')
									SetColor(Black, Black);
								else
									SetColor(White, Black);
								cout << DrawSprites.InvadersTypeC[i][j];
								if (i == 1)
								{
									SetColor(White, Black);
									SetCursor(j + 26, 15 + i + 4 * k);
									cout << " = 10 Point";
								}
							}
						}
					}
				}

				SetColor(Red, Black);
				SetCursor(30, 12);
				cout << "START";

				key = _getch();
				if (key == Enter)
					startGame = true;
				else
				{
					system("cls");
					break;
				}

				break;
			}
			case 1:
				system("cls");
				SetCursor(25, 4);
				cout << "Name:\t\t" << "Score:\n";
				while (key != esc)
				{
					int i = 0;
					for (User val : US)
					{
						SetCursor(23, 5 + i);
						cout << i << ") " << val.Login;
						SetCursor(40, 5 + i);
						cout << val.score << "\n";
						i++;
					}
					cout << "esc - exit";
					key = _getch();
				}
				system("cls");
				break;
			case 2:
				//Для выхода из приложения
				PostMessage(GetConsoleWindow(), WM_QUIT, 0, 0);//Закрытия окна
				break;
			}
		} while (startGame != true);

		startGame = false;



		//Игровой Цыкал //
		bool GameEnd = false;
		do
		{
			GameEnd = false;
			system("cls");

			SetFontSize(13);
			Sleep(1);
			system("mode con cols=97 lines=39");

			LaserGun LG;//Создания игрока

			LG.setEndGame(false);//Установка что игра началась
			LG.DrawLaserGun();//Рисуем орудия игрока
			x = LG.getCoord().X;
			y = LG.getCoord().Y;
			bool СollisionObj = true;

			//Отрисовка нижней границы//
			SetColor(Red, Green);
			for (short i = 0; i < 97; i++)
			{
				SetCursor(0 + i, 38);
				cout << "#";
			}

			//Создания инопланетян//
			MysteryShip MysteryShip;//Создания Таинственного корабля

			vector<Invaders> Invad;//Создания Захватчиков корабля
			Invaders Invaders;
			Sprites ObjSpritesInvaders;
			for (short k = 0; k < 4; k++)
			{
				for (short i = 0; i < 10; i++)
				{
					if (k == 0)
					{//A
						Invaders.InvaderType(ObjSpritesInvaders.InvadersTypeA);//Установка внешнего вида
						Invaders.setPoint(30);//Количества очьков за убийства 
					}
					if (k == 1)
					{//B
						Invaders.InvaderType(ObjSpritesInvaders.InvadersTypeB);
						Invaders.setPoint(20);
					}
					if (k == 2)
					{//B
						Invaders.InvaderType(ObjSpritesInvaders.InvadersTypeB);
						Invaders.setPoint(20);
					}
					if (k == 3)
					{//C
						Invaders.InvaderType(ObjSpritesInvaders.InvadersTypeC);
						Invaders.setPoint(10);
					}
					if (k == 4)
					{//C
						Invaders.InvaderType(ObjSpritesInvaders.InvadersTypeC);
						Invaders.setPoint(10);
					}
					Invaders.setCoord(i * 5, 7 + k * 3);//координаты Invaders
					Invad.push_back(move(Invaders));//Записываем в массив
				}
			}

			vector<Shelter>shelter;//Тут хранятся убежища и их параметры
			Shelter objShelter;
			for (short i = 0; i < 4; i++)
			{
				//Установка координат убежищ
				objShelter.x = 7 + (25 * i);
				objShelter.y = 28;
				shelter.push_back(objShelter);//Сохраняем 
			}


			//Создания потока InvaderBehavior Поведение захватчика
			thread InvadersThread(InvaderBehavior, ref(LG), ref(Invad), ref(shelter), ref(MysteryShip));
			//Создания потока с отрисовкой убежищ
			thread DrawObjShelters(DrawObjShelter, ref(shelter), ref(GameEnd));
			//Создания потока с выводом информации о количестве баллов и жизней игрока
			thread PlayerStats(DrawPlayerStats, ref(LG));


			//Игровой цикла с уповления орудием
			do
			{
				LG.DrawLaserGun();//Отрисовка игрока

				//обработка нажатий клавиш
				key = _getch();
				switch (key)
				{
				case Left:
					if (x > 0)
						LG.setCoordGun(--x, y);
					break;
				case Right:
					if (x < 90)
						LG.setCoordGun(++x, y);
					break;
				case Space:
					if (СollisionObj == true)
					{
						СollisionObj = false;
						//Создания потока с звуком выстрела
						thread music(Music, L"Music/shoot.wav");
						//Создания потока с функцией Shoot для выстрела 
						thread shoot(&LaserGun::Shoot, &LG, ref(Invad), ref(shelter), ref(СollisionObj), ref(MysteryShip));
						Sleep(50);
						shoot.detach();
						music.detach();
					}
					break;

				}

				Sleep(10);

			} while (LG.getLives() > 0 && key != esc && Invad.size() > 0);

			//Игра окончена
			Sleep(100);
			GameEnd = true;
			LG.setEndGame(true);

			thread music(Music, L"Music/explosion.wav");

			InvadersThread.detach();
			DrawObjShelters.detach();
			PlayerStats.detach();

			music.detach();

			SetColor(White, Black);



			//Если игрок проиграл выводим "Game Over"
			if (LG.getLives() <= 0 || key == esc)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 78; j++)
					{
						SetCursor(10 + j, 5 + i);
						if (DrawSprites.GameOver[i][j] == 0)
							SetColor(Black, Black);
						if (DrawSprites.GameOver[i][j] == 1)
							SetColor(LightRed, LightRed);
						if (DrawSprites.GameOver[i][j] == 2)
							SetColor(Red, Red);
						cout << DrawSprites.GameOver[i][j];

					}
				}

			}
			//Если игрок победил выводим "You Won"
			if (LG.getLives() > 0 && Invad.size() <= 0)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 57; j++)
					{
						SetCursor(20 + j, 5 + i);
						if (DrawSprites.YouWon[i][j] == 0)
							SetColor(Black, Black);
						if (DrawSprites.YouWon[i][j] == 1)
							SetColor(LightRed, LightRed);
						if (DrawSprites.YouWon[i][j] == 2)
							SetColor(Red, Red);
						cout << DrawSprites.YouWon[i][j];

					}
				}
			}

			//Сортировка Игроков для рейтинговой таблицы
			sort(US.rbegin(), US.rend(), [](const User& dot1, const User& dot2) -> bool
				{
					return dot1.score < dot2.score;
				});

			//обновления результата игрока
			ReaderWriter.open("Users.txt", ofstream::out | ofstream::trunc);
			for (short i = 0; i < US.size(); i++)
			{
				if (US[i].Login == Login && US[i].score < LG.getScore())
				{
					US[i].score = LG.getScore();
					ReaderWriter << US[i].Login << " " << US[i].Password << " " << US[i].score << '\n';
				}
				else
				{
					ReaderWriter << US[i].Login << " " << US[i].Password << " " << US[i].score << '\n';
				}
			}
			ReaderWriter.close();

			string PostGameMenu[2] = { "Play again","Menu" };
			x = 40, y = 0;
			do
			{
				Menu(PostGameMenu, y, x, 2, 20);
				key = _getch();
				switch (key)
				{
				case Up:
					if (y > 0)
						--y;
					break;
				case Down:
					if (y < 1)
						++y;
					break;
				}

				Sleep(10);
			} while (key != Enter);

			if (y == 1)
				break;

			system("cls");



		} while (true);

	}





	//exit(0);
	Hidecursor(TRUE);
}