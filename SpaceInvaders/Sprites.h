﻿#pragma once
//пространство имен std
using namespace std;
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