#ifndef GAMECODE_H
#define	GAMECODE_H

#include "stdafx.h"
#include "server.h"

///////////snake///////////
class SNAKE {
public:
	int N, M;
	int size;
	int w;
	int h;
	int dir, num, nu;
	struct Snake
	{
		int x, y;
	}s[100];
	struct Fruit
	{
		int x, y;
	}f;
	void Tick();
	void resetgame();
	void snake();
	SNAKE();
	~SNAKE();
};



///////////tetris///////////
class TETRIS {
public:
	static const int M = 20;
	static const int N = 10;
	int field[M][N] = { 0 };
	int figures[7][4] = {
	1,3,5,7,
	2,4,5,7,
	3,5,4,6,
	3,5,4,7,
	2,3,5,7,
	3,5,7,6,
	2,3,4,5
	};
	struct Point {
		int x, y;
	}a[4], b[4], c[4];
	sf::Texture t, bk, f;

	void resetgame();
	bool Check();
	void Rotate();
	void Tick(int&,int&);
	void Checklines();
	virtual void tetris();
	TETRIS();
};

class DTETRIS_S :public TETRIS {
public:
	virtual void tetris();
};

class DTETRIS_C :public TETRIS {
public:
	virtual void tetris(client*);
};

class WAN_TETRIS :public TETRIS {
public:
	virtual void tetris(WAN_client*);
};




///////////doodle jump///////////
class DOODLEJUMP {
public:
	struct point
	{
		int x, y;
	};
	void doodlejump();
};




//////////Mahjong Solitaire/////////
class MAHJONG {
public:
	sf::Texture t1, t2;
	int field[50][50][50] = { 0 };
	int& f(int x, int y, int z);
	int& f(sf::Vector3i v);
	bool isOpen(int x, int y, int z);
	void loadfromfile();
	void createmap();
	void resetgame();
	virtual void mahjong();
	MAHJONG();
};

class MAHJONG_S :public MAHJONG {
public:
	int _k[10][31][18] = { 0 };
	int _h[10][31][18] = { 0 };
	void mahjong();
};

class MAHJONG_C :public MAHJONG {
public:
	int _k[10][31][18] = { 0 };
	int _h[10][31][18] = { 0 };
	void mahjong(client*);
};
class WAN_MAHJONG :public MAHJONG {
public:
	int _k[10][31][18] = { 0 };
	int _h[10][31][18] = { 0 };
	void mahjong(WAN_client*);
};


#endif

