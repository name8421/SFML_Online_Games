#include "gamecode.h"
#include <Windows.h>
#include "server.h"

using namespace sf;

SNAKE::SNAKE() {
	N = 25;
	M = 25;
	size = 16;
	w = size * N;
	h = size * (M + 2);
	dir = 0;
	num = 2;
	nu = 2;
	f.x = 0;
	f.y = 0;
	for (int i = 0; i < 100; i++) {
		s[i].x = 0;
		s[i].y = 0;
	}

}
SNAKE::~SNAKE() {
}



void SNAKE::Tick()
{
	for (int i = num; i > 0; i--)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}
	if (dir == 0) //KeyDown
	{
		s[0].y += 1;
	}
	if (dir == 1) //KeyLeft
	{
		s[0].x -= 1;
	}
	if (dir == 2) //KeyRight
	{
		s[0].x += 1;
	}
	if (dir == 3) //KeyUp
	{
		s[0].y -= 1;
	}

	if (s[0].x == f.x && (s[0].y == f.y))
	{
		num++;
		f.x = rand() % N;
		f.y = rand() % M;
	}

	if (s[0].x >= N)					//穿过边界从对面边界出现
	{
		s[0].x = 0;
	}
	if (s[0].x < 0)
	{
		s[0].x = N - 1;
	}
	if (s[0].y >= M)
	{
		s[0].y = 0;
	}
	if (s[0].y < 0)
	{
		s[0].y = M - 1;
	}

	for (int i = 1; i < num; i++)		//蛇头吃到蛇身断除尾部
	{
		if (s[0].x == s[i].x && s[0].y == s[i].y)
		{
			num = i;
		}
	}
}
void SNAKE::resetgame() {
	num = 2;
	nu = num;
	s[0].x = 0;
	s[0].y = 0;
	dir = 0;
}


void SNAKE::snake()
{
	//resetgame();

	srand(time(0));

	RenderWindow window(VideoMode(w, h), "Snake Game!", sf::Style::Close);
	window.setFramerateLimit(60);

	Texture t1, t2, t3, t4;
	t1.loadFromFile("Resources/Images/games/snake/white.png");
	t2.loadFromFile("Resources/Images/games/snake/purple.png");
	t3.loadFromFile("Resources/Images/games/snake/red.png");
	t4.loadFromFile("Resources/Images/games/snake/green.png");

	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);
	Sprite sprite4(t4);

	Clock clock;
	float timer = 0, delay = 0.2;


	Font font;
	Text text;
	if (!font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}

	String score = "Score:";
	text.setFont(font);
	text.setString("Score:0");
	text.setFillColor(Color(255, 255, 255));
	text.setPosition(((float)M / 2 - 3) * size + 0.5f, w);


	f.x = rand() % N; f.y = rand() % M;

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
				return;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			int helper = MessageBox(NULL, TEXT("游戏说明"), TEXT("游戏说明"), MB_OK);
		}

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;



		if (Keyboard::isKeyPressed(Keyboard::Left) && dir != 2)
		{
			dir = 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && dir != 1)
		{
			dir = 2;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up) && dir != 0)
		{
			dir = 3;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && dir != 3)
		{
			dir = 0;
		}


		if (timer > delay)
		{
			timer = 0;
			Tick();
			if (num != nu && delay > 0.01)
			{
				nu = num;
				delay = 0.2 - (num - 2) * 0.005;
			}
		}

		////draw////
		window.clear();

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				sprite1.setPosition(i * size, j * size);
				window.draw(sprite1);
			}
		}

		for (int i = 0; i < num; i++)
		{
			if (i == 0)
			{
				sprite3.setPosition(s[i].x * size, s[i].y * size); window.draw(sprite3);
			}
			else
			{
				sprite2.setPosition(s[i].x * size, s[i].y * size);
				window.draw(sprite2);
			}
		}

		sprite4.setPosition(f.x * size, f.y * size);
		window.draw(sprite4);
		text.setString(score + std::to_string(num - 2));
		window.draw(text);

		window.display();

	}

}









TETRIS::TETRIS() {
	for (int i = 0; i < 4; i++) {
		a[i].x = 0; a[i].y = 0;
		b[i].x = 0; b[i].y = 0;
		c[i].x = 0; c[i].y = 0;
	}
	t.loadFromFile("Resources/Images/games/tetris/tiles.png");
	bk.loadFromFile("Resources/Images/games/tetris/background.png");
	f.loadFromFile("Resources/Images/games/tetris/frame.png");

}

void TETRIS::resetgame() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			field[i][j] = 0;
		}
	}
}

bool TETRIS::Check()
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
			return 0;
		else if (field[a[i].y][a[i].x])
			return 0;
	return 1;
}

void TETRIS::Rotate() {
	Point p = a[1]; //center of rotation
	for (int i = 0; i < 4; i++)
	{
		int x = a[i].y - p.y;
		int y = a[i].x - p.x;
		a[i].x = p.x - x;
		a[i].y = p.y + y;
	}
	if (!Check())
	{
		for (int i = 0; i < 4; i++)
			a[i] = b[i];
	}
}

void TETRIS::Tick(int& colorNum, int& n) {
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i]; a[i].y += 1;
	}
	if (!Check())
	{
		for (int i = 0; i < 4; i++) {
			if (field[b[i].y][b[i].x] != 0) {
				//int died = MessageBox(NULL, TEXT("you loss"), TEXT("游戏"), MB_OK);
				resetgame();
				break;
			}
			field[b[i].y][b[i].x] = colorNum;

		}


		colorNum = 1 + rand() % 7;
		n = rand() % 7;
		for (int i = 0; i < 4; i++)
			a[i] = c[i];
		for (int i = 0; i < 4; i++)
		{
			c[i].x = figures[n][i] % 2;
			c[i].y = figures[n][i] / 2;
		}

	}
}

void TETRIS::Checklines() {
	int k = M - 1;
	for (int i = M - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < N; j++)
		{
			if (field[i][j])
				count++;
			field[k][j] = field[i][j];
		}
		if (count < N)
			k--;
	}
}


void TETRIS::tetris()
{
	resetgame();


	srand(time(0));

	RenderWindow window(VideoMode(320, 480), "Tetris", Style::Titlebar | Style::Close);

	Sprite s(t), background1(bk), frame(f);
	s.setTextureRect(IntRect(0, 0, 18, 18));

	int dx = 0;
	bool rotate = 0;
	int colorNum = 1 + rand() % 7;
	float timer = 0, delay = 0.3;
	int n = rand() % 7;

	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}
	n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		c[i].x = figures[n][i] % 2;
		c[i].y = figures[n][i] / 2;
	}

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::KeyPressed)
			{
				if (e.key.code == Keyboard::Up)
					rotate = true;
				else if (e.key.code == Keyboard::Left)
					dx = -1;
				else if (e.key.code == Keyboard::Right)
					dx = 1;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
			delay = 0.05;

		/// <-- Move --> ///
		for (int i = 0; i < 4; i++)
		{
			b[i] = a[i];
			a[i].x += dx;
		}
		if (!Check())
		{
			for (int i = 0; i < 4; i++)
				a[i] = b[i];
		}

		/// <-- Rotate --> ///
		if (rotate)
		{
			this->Rotate();
		}

		/// <-- Tick --> ///
		if (timer > delay)
		{
			Tick(colorNum, n);
			timer = 0;
		}


		//////check lines//////
		Checklines();

		dx = 0; rotate = 0; delay = 0.3;

		///////draw/////

		window.clear(Color::White);
		window.draw(background1);




		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0)
					continue;
				s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				s.setPosition(j * 18, i * 18);
				s.move(28, 31);
				window.draw(s);
			}
		}
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			s.setPosition(c[i].x * 18, c[i].y * 18);
			s.move(280, 140);
			window.draw(s);
		}
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			s.setPosition(a[i].x * 18, a[i].y * 18);
			s.move(28, 31);
			window.draw(s);
		}




		window.draw(frame);
		window.display();
	}
}

void DTETRIS_S::tetris()
{
	resetgame();


	srand(time(0));

	RenderWindow window(VideoMode(650, 480), "Tetris", Style::Titlebar | Style::Close);

	Sprite s(t), background1(bk), background2(bk), frame1(f), frame2(f);
	background2.setPosition(330, 0);
	frame2.setPosition(330, 0);
	s.setTextureRect(IntRect(0, 0, 18, 18));

	int dx = 0;
	bool rotate = 0;
	int colorNum = 1 + rand() % 7;
	float timer = 0, delay = 0.3, ctimer = 0, cdelay = 1.0;
	int cr = rand() % 256, cg = rand() % 256, cb = rand() % 256;

	int n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}
	n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		c[i].x = figures[n][i] % 2;
		c[i].y = figures[n][i] / 2;
	}

	Clock clock;


	room host;
	host.gtype = room::gametype::TETRIS;
	//host.status = room::roomstatus::GAMING;
	//host.remote_add = host.local_add;


	int remote_field[M][N] = { 0 }, remote_colorNum = 0;
	Point remote_a[4] = { 0 }, remote_c[4] = { 0 };

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		ctimer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::KeyPressed)
			{
				if (e.key.code == Keyboard::Up)
					rotate = true;
				else if (e.key.code == Keyboard::Left)
					dx = -1;
				else if (e.key.code == Keyboard::Right)
					dx = 1;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
			delay = 0.05;

		/// <-- Move --> ///
		for (int i = 0; i < 4; i++)
		{
			b[i] = a[i];
			a[i].x += dx;
		}
		if (!Check())
		{
			for (int i = 0; i < 4; i++)
				a[i] = b[i];
		}

		/// <-- Rotate --> ///
		if (rotate)
		{
			this->Rotate();
		}

		/// <-- Tick --> ///
		if (timer > delay)
		{
			Tick(colorNum, n);
			timer = 0;
		}

		//////check lines//////
		Checklines();

		dx = 0; rotate = 0; delay = 0.3;


		host.run();

		if (host.status == room::roomstatus::GAMING) {
			///////get data////////
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					host.packet >> remote_field[i][j];
				}
			}
			for (int i = 0; i < 4; i++) {
				host.packet >> remote_c[i].x >> remote_c[i].y;
			}
			for (int i = 0; i < 4; i++) {
				host.packet >> remote_a[i].x >> remote_a[i].y;
			}
			host.packet >> remote_colorNum;


			///////send data////////
			host.packet.clear();
			host.packet << host.GAMEDATA;
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					host.packet << field[i][j];
				}
			}
			for (int i = 0; i < 4; i++) {
				host.packet << c[i].x << c[i].y;
			}
			for (int i = 0; i < 4; i++) {
				host.packet << a[i].x << a[i].y;
			}
			host.packet << colorNum;
			host.socket.send(host.packet, host.remote_add, host.remote_port);
		}


		///////draw/////

		window.clear(Color(cr, cg, cb));
		window.draw(background1);
		window.draw(background2);


		//player 1
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0)
					continue;
				s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				s.setPosition(j * 18, i * 18);
				s.move(28, 31);
				window.draw(s);
			}
		}
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			s.setPosition(c[i].x * 18, c[i].y * 18);
			s.move(280, 140);
			window.draw(s);
		}
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			s.setPosition(a[i].x * 18, a[i].y * 18);
			s.move(28, 31);
			window.draw(s);
		}
		window.draw(frame1);

		//player 2

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (remote_field[i][j] == 0)
					continue;
				s.setTextureRect(IntRect(remote_field[i][j] * 18, 0, 18, 18));
				s.setPosition(j * 18 + 330, i * 18);
				s.move(28, 31);
				window.draw(s);
			}
		}
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(remote_colorNum * 18, 0, 18, 18));
			s.setPosition(remote_c[i].x * 18 + 330, remote_c[i].y * 18);
			s.move(280, 140);
			window.draw(s);
		}
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(remote_colorNum * 18, 0, 18, 18));
			s.setPosition(remote_a[i].x * 18 + 330, remote_a[i].y * 18);
			s.move(28, 31);
			window.draw(s);
		}
		window.draw(frame2);







		window.display();
	}
}

void DTETRIS_C::tetris(client* guest)
{
	resetgame();


	srand(time(0));

	RenderWindow window(VideoMode(650, 480), "Tetris", Style::Titlebar | Style::Close);

	Sprite s(t), background1(bk), background2(bk), frame1(f), frame2(f);
	background2.setPosition(330, 0);
	frame2.setPosition(330, 0);
	s.setTextureRect(IntRect(0, 0, 18, 18));

	int dx = 0;
	bool rotate = 0;
	int colorNum = 1 + rand() % 7;
	float timer = 0, delay = 0.3, ctimer = 0, cdelay = 1.0;
	int cr = rand() % 256, cg = rand() % 256, cb = rand() % 256;

	int n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}
	n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		c[i].x = figures[n][i] % 2;
		c[i].y = figures[n][i] / 2;
	}

	Clock clock;




	int remote_field[M][N] = { 0 }, remote_colorNum = 0;
	Point remote_a[4] = { 0 }, remote_c[4] = { 0 };

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		ctimer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::KeyPressed)
			{
				if (e.key.code == Keyboard::Up)
					rotate = true;
				else if (e.key.code == Keyboard::Left)
					dx = -1;
				else if (e.key.code == Keyboard::Right)
					dx = 1;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
			delay = 0.05;

		/// <-- Move --> ///
		for (int i = 0; i < 4; i++)
		{
			b[i] = a[i];
			a[i].x += dx;
		}
		if (!Check())
		{
			for (int i = 0; i < 4; i++)
				a[i] = b[i];
		}

		/// <-- Rotate --> ///
		if (rotate)
		{
			this->Rotate();
		}

		/// <-- Tick --> ///
		if (timer > delay)
		{
			Tick(colorNum, n);
			timer = 0;
		}

		//////check lines//////
		Checklines();

		dx = 0; rotate = 0; delay = 0.3;


		//guest->run();
		///////send data////////
		if (guest->status == client::clientstatus::PLAYING) {
			guest->packet.clear();
			guest->packet << guest->GAMEDATA;
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					guest->packet << field[i][j];
				}
			}
			for (int i = 0; i < 4; i++) {
				guest->packet << c[i].x << c[i].y;
			}
			for (int i = 0; i < 4; i++) {
				guest->packet << a[i].x << a[i].y;
			}
			guest->packet << colorNum;
			guest->socket.send(guest->packet, guest->remote_add, guest->remote_port);
		}
		///////get data////////
		guest->run();
		if (guest->status == client::clientstatus::PLAYING && !guest->packet.endOfPacket()) {
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					guest->packet >> remote_field[i][j];
				}
			}
			for (int i = 0; i < 4; i++) {
				guest->packet >> remote_c[i].x >> remote_c[i].y;
			}
			for (int i = 0; i < 4; i++) {
				guest->packet >> remote_a[i].x >> remote_a[i].y;
			}
			guest->packet >> remote_colorNum;
		}

		///////draw/////

		window.clear(Color(cr, cg, cb));
		window.draw(background1);
		window.draw(background2);


		//player 1
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0)
					continue;
				s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				s.setPosition(j * 18, i * 18);
				s.move(28, 31);
				window.draw(s);
			}
		}
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			s.setPosition(c[i].x * 18, c[i].y * 18);
			s.move(280, 140);
			window.draw(s);
		}
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			s.setPosition(a[i].x * 18, a[i].y * 18);
			s.move(28, 31);
			window.draw(s);
		}
		window.draw(frame1);

		//player 2

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (remote_field[i][j] == 0)
					continue;
				s.setTextureRect(IntRect(remote_field[i][j] * 18, 0, 18, 18));
				s.setPosition(j * 18 + 330, i * 18);
				s.move(28, 31);
				window.draw(s);
			}
		}
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(remote_colorNum * 18, 0, 18, 18));
			s.setPosition(remote_c[i].x * 18 + 330, remote_c[i].y * 18);
			s.move(280, 140);
			window.draw(s);
		}
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(remote_colorNum * 18, 0, 18, 18));
			s.setPosition(remote_a[i].x * 18 + 330, remote_a[i].y * 18);
			s.move(28, 31);
			window.draw(s);
		}
		window.draw(frame2);







		window.display();
	}
}



void WAN_TETRIS::tetris(WAN_client* client)
{
	resetgame();


	srand(time(0));

	RenderWindow window(VideoMode(650, 480), "ROOM-" + std::to_string(client->roomNumber) + " Tetris", Style::Titlebar | Style::Close);

	Sprite s(t), background1(bk), background2(bk), frame1(f), frame2(f);
	background2.setPosition(330, 0);
	frame2.setPosition(330, 0);
	s.setTextureRect(IntRect(0, 0, 18, 18));

	int dx = 0;
	bool rotate = 0;
	int colorNum = 1 + rand() % 7;
	float timer = 0, delay = 0.3, ctimer = 0, cdelay = 1.0;
	int cr = rand() % 256, cg = rand() % 256, cb = rand() % 256;

	int n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}
	n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		c[i].x = figures[n][i] % 2;
		c[i].y = figures[n][i] / 2;
	}

	Clock clock;




	int remote_field[M][N] = { 0 }, remote_colorNum = 0;
	Point remote_a[4] = { 0 }, remote_c[4] = { 0 };

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		ctimer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::KeyPressed)
			{
				if (e.key.code == Keyboard::Up)
					rotate = true;
				else if (e.key.code == Keyboard::Left)
					dx = -1;
				else if (e.key.code == Keyboard::Right)
					dx = 1;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
			delay = 0.05;

		/// <-- Move --> ///
		for (int i = 0; i < 4; i++)
		{
			b[i] = a[i];
			a[i].x += dx;
		}
		if (!Check())
		{
			for (int i = 0; i < 4; i++)
				a[i] = b[i];
		}

		/// <-- Rotate --> ///
		if (rotate)
		{
			this->Rotate();
		}

		/// <-- Tick --> ///
		if (timer > delay)
		{
			Tick(colorNum, n);
			timer = 0;
		}

		//////check lines//////
		Checklines();

		dx = 0; rotate = 0; delay = 0.3;

		client->run();
		if (client->status == WAN_client::clientstatus::PLAYING) {
			/////////send data////////
			sf::Packet pac;
			pac << client->roomNumber << client::gametype::TETRIS;
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					pac << field[i][j];
				}
			}
			for (int i = 0; i < 4; i++) {
				pac << c[i].x << c[i].y;
			}
			for (int i = 0; i < 4; i++) {
				pac << a[i].x << a[i].y;
			}
			pac << colorNum;

			if (client->uSocket.send(pac, client->server_add, client->server_port) == sf::Socket::Done) {
				//std::cout << 1;
			}
			///////get data////////
			pac.clear();
			sf::IpAddress _ip;
			unsigned short _port;
			if (client->uSocket.receive(pac, _ip, _port) == sf::Socket::Done) {
				//std::cout << 1;
				UINT32 t;
				pac >> t;
				pac >> t;
				for (int i = 0; i < M; i++) {
					for (int j = 0; j < N; j++) {
						pac >> remote_field[i][j];
					}
				}
				for (int i = 0; i < 4; i++) {
					pac >> remote_c[i].x >> remote_c[i].y;
				}
				for (int i = 0; i < 4; i++) {
					pac >> remote_a[i].x >> remote_a[i].y;
				}
				pac >> remote_colorNum;

			}
		}


		///////draw/////

		window.clear(Color(cr, cg, cb));
		window.draw(background1);
		window.draw(background2);


		//player 1
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0)
					continue;
				s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				s.setPosition(j * 18, i * 18);
				s.move(28, 31);
				window.draw(s);
			}
		}
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			s.setPosition(c[i].x * 18, c[i].y * 18);
			s.move(280, 140);
			window.draw(s);
		}
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			s.setPosition(a[i].x * 18, a[i].y * 18);
			s.move(28, 31);
			window.draw(s);
		}
		window.draw(frame1);

		//player 2
		if (client->status == WAN_client::clientstatus::PLAYING) {
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (remote_field[i][j] == 0)
						continue;
					s.setTextureRect(IntRect(remote_field[i][j] * 18, 0, 18, 18));
					s.setPosition(j * 18 + 330, i * 18);
					s.move(28, 31);
					window.draw(s);
				}
			}
			for (int i = 0; i < 4; i++)
			{
				s.setTextureRect(IntRect(remote_colorNum * 18, 0, 18, 18));
				s.setPosition(remote_c[i].x * 18 + 330, remote_c[i].y * 18);
				s.move(280, 140);
				window.draw(s);
			}
			for (int i = 0; i < 4; i++)
			{
				s.setTextureRect(IntRect(remote_colorNum * 18, 0, 18, 18));
				s.setPosition(remote_a[i].x * 18 + 330, remote_a[i].y * 18);
				s.move(28, 31);
				window.draw(s);
			}
			window.draw(frame2);
		}
		


		window.display();


	}
}






void DOODLEJUMP::doodlejump() {
	srand(time(0));

	RenderWindow app(VideoMode(400, 533), "Doodle Jump!", sf::Style::Titlebar | sf::Style::Close);
	app.setFramerateLimit(60);

	Texture t1, t2, t3;
	t1.loadFromFile("Resources/Images/games/doodlejump/background.png");
	t2.loadFromFile("Resources/Images/games/doodlejump/platform.png");
	t3.loadFromFile("Resources/Images/games/doodlejump/doodle.png");

	Sprite sBackground(t1), sPlat(t2), sPers(t3);

	point plat[20];

	for (int i = 0; i < 10; i++)
	{
		plat[i].x = rand() % 400;
		plat[i].y = rand() % 533;
	}

	int x = 100, y = 100, h = 200;
	float dx = 0, dy = 0;

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) x += 3;
		if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 3;

		dy += 0.2;
		y += dy;
		if (y > 500)  dy = -10;

		if (y < h)
			for (int i = 0; i < 10; i++)
			{
				y = h;
				plat[i].y = plat[i].y - dy;
				if (plat[i].y > 533) { plat[i].y = 0; plat[i].x = rand() % 400; }
			}

		for (int i = 0; i < 10; i++)
			if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
				&& (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))  dy = -10;

		sPers.setPosition(x, y);

		app.draw(sBackground);
		app.draw(sPers);
		for (int i = 0; i < 10; i++)
		{
			sPlat.setPosition(plat[i].x, plat[i].y);
			app.draw(sPlat);
		}

		app.display();
	}
}



//////////Mahjong Solitaire/////////
MAHJONG::MAHJONG(){
	t1.loadFromFile("Resources/Images/games/mahjong/tiles.png");
	t2.loadFromFile("Resources/Images/games/mahjong/background.png");
}
int& MAHJONG::f(int x, int y, int z) {
	return field[y + 2][x + 2][z];
}
int& MAHJONG::f(sf::Vector3i v) {
	return f(v.x, v.y, v.z);
}
bool MAHJONG::isOpen(int x, int y, int z) {
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if (f(x + 2, y + i, z) > 0 && f(x - 2, y + j, z) > 0) return 0;

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if (f(x + i, y + j, z + 1) > 0) return 0;

	return 1;
}
void MAHJONG::loadfromfile() {
	std::fstream myfile("Resources/Images/games/mahjong/map.txt");
	for (int y = 0; y < 18; y++)
		for (int x = 0; x < 30; x++)
		{
			char a;
			myfile >> a;
			int n = a - '0';
			for (int z = 0; z < n; z++)
				if (f(x - 1, y - 1, z)) f(x - 1, y, z) = f(x, y - 1, z) = 0;
				else f(x, y, z) = 1;
		}
}
void MAHJONG::createmap() {
	for (int k = 1;; k++)
	{
		std::vector<Vector3i> opens;
		for (int z = 0; z < 10; z++)
			for (int y = 0; y < 18; y++)
				for (int x = 0; x < 30; x++)
					if (f(x, y, z) > 0 && isOpen(x, y, z)) opens.push_back(Vector3i(x, y, z));

		int n = opens.size();
		if (n < 2) break;
		int a = 0, b = 0;
		while (a == b) { a = rand() % n; b = rand() % n; }
		this->f(opens[a]) = -k;  if (k > 34) k++;
		this->f(opens[b]) = -k;
		k %= 42;
	}

	for (int z = 0; z < 10; z++)
		for (int y = 0; y < 18; y++)
			for (int x = 0; x < 30; x++) this->f(x, y, z) *= -1;
}
void MAHJONG::resetgame() {
	this->loadfromfile();
	this->createmap();
}
void MAHJONG::mahjong() {
	srand(time(0));

	RenderWindow app(VideoMode(740, 570), "Mahjong Solitaire!", sf::Style::Titlebar | sf::Style::Close);
	
	Sprite s(t1), sBackground(t2);
	int w = 48, h = 66;
	int stepX = w / 2 - 2, stepY = h / 2 - 2;
	float offX = 4.6, offY = 7.1; // z offset
	Vector3i v1, v2;
	std::vector<Vector3i> moves;


	////load from file////
	this->loadfromfile();

	////create map//////
	this->createmap();



	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
			
			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::R) {
					this->resetgame();
					continue;
				}
			}

			//move back
			if (e.type == Event::MouseButtonReleased)
				if (e.key.code == Mouse::Right)
				{
					int n = moves.size();
					if (n == 0) continue;
					f(moves[n - 1]) *= -1; moves.pop_back();
					f(moves[n - 2]) *= -1; moves.pop_back();
				}

			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
					for (int z = 0; z < 10; z++)
					{
						Vector2i pos = Mouse::getPosition(app) - Vector2i(30, 0); // 30 - desk offset
						int x = (pos.x - z * offX) / stepX;
						int y = (pos.y + z * offY) / stepY;

						for (int i = 0; i < 2; i++)
							for (int j = 0; j < 2; j++)
								if (f(x - i, y - j, z) > 0 && isOpen(x - i, y - j, z))
									v1 = Vector3i(x - i, y - j, z);

						if (v1 == v2) continue;

						int a = f(v1), b = f(v2);
						if (a == b || (a > 34 && a < 39 && b>34 && b < 39) || (a >= 39 && b >= 39))
						{
							f(v1) *= -1; moves.push_back(v1);
							f(v2) *= -1; moves.push_back(v2);
						}
						v2 = v1;
					}
		}

		app.clear();
		app.draw(sBackground);
		for (int z = 0; z < 10; z++)
			for (int x = 30; x >= 0; x--)
				for (int y = 0; y < 18; y++)
				{
					int k = f(x, y, z) - 1;
					if (k < 0) continue;
					s.setTextureRect(IntRect(k * w, 0, w, h));
					if (isOpen(x, y, z)) s.setTextureRect(IntRect(k * w, h, w, h));
					s.setPosition(x * stepX + z * offX, y * stepY - z * offY);
					s.move(30, 0); //desk offset
					app.draw(s);
				}

		app.display();
	}
}


void MAHJONG_S::mahjong() {
	srand(time(0));

	RenderWindow app(VideoMode(1480, 570), "Mahjong Solitaire!", sf::Style::Titlebar | sf::Style::Close);

	Sprite s(t1), sBackground(t2);
	Sprite _sBackground(t2);
	_sBackground.setPosition(740, 0);
	int w = 48, h = 66;
	int stepX = w / 2 - 2, stepY = h / 2 - 2;
	float offX = 4.6, offY = 7.1; // z offset
	Vector3i v1, v2;
	std::vector<Vector3i> moves;


	////load from file////
	this->loadfromfile();

	////create map//////
	this->createmap();


	room host;
	host.gtype = room::gametype::MAHJONG;

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::R) {
					this->resetgame();
					continue;
				}
			}


			//move back
			if (e.type == Event::MouseButtonReleased)
				if (e.key.code == Mouse::Right)
				{
					int n = moves.size();
					if (n == 0) continue;
					f(moves[n - 1]) *= -1; moves.pop_back();
					f(moves[n - 2]) *= -1; moves.pop_back();
				}

			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
					for (int z = 0; z < 10; z++)
					{
						Vector2i pos = Mouse::getPosition(app) - Vector2i(30, 0); // 30 - desk offset
						int x = (pos.x - z * offX) / stepX;
						int y = (pos.y + z * offY) / stepY;

						for (int i = 0; i < 2; i++)
							for (int j = 0; j < 2; j++)
								if (f(x - i, y - j, z) > 0 && isOpen(x - i, y - j, z))
									v1 = Vector3i(x - i, y - j, z);

						if (v1 == v2) continue;

						int a = f(v1), b = f(v2);
						if (a == b || (a > 34 && a < 39 && b>34 && b < 39) || (a >= 39 && b >= 39))
						{
							f(v1) *= -1; moves.push_back(v1);
							f(v2) *= -1; moves.push_back(v2);
						}
						v2 = v1;
					}
		}



		app.clear();
		app.draw(sBackground);
		app.draw(_sBackground);
		

		host.run();
		for (int z = 0; z < 10; z++) {
			for (int x = 30; x >= 0; x--) {
				for (int y = 0; y < 18; y++) {
					if (host.status == room::roomstatus::GAMING)
						host.packet >> _k[z][x][y] >> _h[z][x][y];
					if (_h[z][x][y] == 2)
						continue;
					s.setTextureRect(IntRect(_k[z][x][y] * w, _h[z][x][y], w, h));
					s.setPosition(x * stepX + z * offX + 740, y * stepY - z * offY);
					s.move(30, 0);
					if (host.status == room::roomstatus::GAMING)
					app.draw(s);
				}
			}
		}

		host.packet.clear();
		host.packet << room::packettype::GAMEDATA;
		for (int z = 0; z < 10; z++)
			for (int x = 30; x >= 0; x--)
				for (int y = 0; y < 18; y++)
				{
					int k = f(x, y, z) - 1;
					host.packet << k;
					if (k < 0) {
						host.packet << 2;
						continue;
					}
					int _h = 0;
					s.setTextureRect(IntRect(k * w, 0, w, h));
					if (isOpen(x, y, z)) {
						s.setTextureRect(IntRect(k * w, h, w, h));
						_h = 1;
					}
					host.packet << _h;
					s.setPosition(x * stepX + z * offX, y * stepY - z * offY);
					s.move(30, 0); //desk offset
					app.draw(s);
				}
		
		
		if (host.status == room::roomstatus::GAMING) {
			host.socket.send(host.packet, host.remote_add, host.remote_port);
			host.packet.clear();
		}
		app.display();
	}
}



void MAHJONG_C::mahjong(client* guest) {
	srand(time(0));

	RenderWindow app(VideoMode(1480, 570), "Mahjong Solitaire!", sf::Style::Titlebar | sf::Style::Close);

	Sprite s(t1), sBackground(t2);
	Sprite _sBackground(t2);
	_sBackground.setPosition(740, 0);
	int w = 48, h = 66;
	int stepX = w / 2 - 2, stepY = h / 2 - 2;
	float offX = 4.6, offY = 7.1; // z offset
	Vector3i v1, v2;
	std::vector<Vector3i> moves;


	////load from file////
	this->loadfromfile();

	////create map//////
	this->createmap();



	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::R) {
					this->resetgame();
					continue;
				}
			}

			//move back
			if (e.type == Event::MouseButtonReleased)
				if (e.key.code == Mouse::Right)
				{
					int n = moves.size();
					if (n == 0) continue;
					f(moves[n - 1]) *= -1; moves.pop_back();
					f(moves[n - 2]) *= -1; moves.pop_back();
				}

			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
					for (int z = 0; z < 10; z++)
					{
						Vector2i pos = Mouse::getPosition(app) - Vector2i(30, 0); // 30 - desk offset
						int x = (pos.x - z * offX) / stepX;
						int y = (pos.y + z * offY) / stepY;

						for (int i = 0; i < 2; i++)
							for (int j = 0; j < 2; j++)
								if (f(x - i, y - j, z) > 0 && isOpen(x - i, y - j, z))
									v1 = Vector3i(x - i, y - j, z);

						if (v1 == v2) continue;

						int a = f(v1), b = f(v2);
						if (a == b || (a > 34 && a < 39 && b>34 && b < 39) || (a >= 39 && b >= 39))
						{
							f(v1) *= -1; moves.push_back(v1);
							f(v2) *= -1; moves.push_back(v2);
						}
						v2 = v1;
					}
		}



		app.clear();
		app.draw(sBackground);
		app.draw(_sBackground);


		guest->run();
		 
		for (int z = 0; z < 10; z++) {
			for (int x = 30; x >= 0; x--) {
				for (int y = 0; y < 18; y++) {
					if (guest->status == client::clientstatus::PLAYING)
						guest->packet >> _k[z][x][y] >> _h[z][x][y];
					if (_h[z][x][y] == 2)
						continue;
					s.setTextureRect(IntRect(_k[z][x][y] * w, _h[z][x][y], w, h));
					s.setPosition(x * stepX + z * offX + 740, y * stepY - z * offY);
					s.move(30, 0);
					if (guest->status == client::clientstatus::PLAYING)
					app.draw(s);
				}
			}
		}

		guest->packet.clear();
		guest->packet << client::packettype::GAMEDATA;
		for (int z = 0; z < 10; z++)
			for (int x = 30; x >= 0; x--)
				for (int y = 0; y < 18; y++)
				{
					int k = f(x, y, z) - 1;
					guest->packet << k;
					if (k < 0) {
						guest->packet << 2;
						continue;
					}
					int _h = 0;
					s.setTextureRect(IntRect(k * w, 0, w, h));
					if (isOpen(x, y, z)) {
						s.setTextureRect(IntRect(k * w, h, w, h));
						_h = 1;
					}
					guest->packet << _h;
					s.setPosition(x * stepX + z * offX, y * stepY - z * offY);
					s.move(30, 0); //desk offset
					app.draw(s);
				}
		if (guest->status == client::clientstatus::PLAYING) {
			guest->socket.send(guest->packet, guest->remote_add, guest->remote_port);
			guest->packet.clear();
		}
		app.display();
	}
}

void WAN_MAHJONG::mahjong(WAN_client* client) {
	srand(time(0));

	RenderWindow app(VideoMode(1480, 570), "ROOM-" + std::to_string(client->roomNumber) + " Mahjong Solitaire", Style::Titlebar | Style::Close);

	Sprite s(t1), sBackground(t2);
	Sprite _sBackground(t2);
	_sBackground.setPosition(740, 0);
	int w = 48, h = 66;
	int stepX = w / 2 - 2, stepY = h / 2 - 2;
	float offX = 4.6, offY = 7.1; // z offset
	Vector3i v1, v2;
	std::vector<Vector3i> moves;


	////load from file////
	this->loadfromfile();

	////create map//////
	this->createmap();



	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::R) {
					this->resetgame();
					continue;
				}
			}

			//move back
			if (e.type == Event::MouseButtonReleased)
				if (e.key.code == Mouse::Right)
				{
					int n = moves.size();
					if (n == 0) continue;
					f(moves[n - 1]) *= -1; moves.pop_back();
					f(moves[n - 2]) *= -1; moves.pop_back();
				}

			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
					for (int z = 0; z < 10; z++)
					{
						Vector2i pos = Mouse::getPosition(app) - Vector2i(30, 0); // 30 - desk offset
						int x = (pos.x - z * offX) / stepX;
						int y = (pos.y + z * offY) / stepY;

						for (int i = 0; i < 2; i++)
							for (int j = 0; j < 2; j++)
								if (f(x - i, y - j, z) > 0 && isOpen(x - i, y - j, z))
									v1 = Vector3i(x - i, y - j, z);

						if (v1 == v2) continue;

						int a = f(v1), b = f(v2);
						if (a == b || (a > 34 && a < 39 && b>34 && b < 39) || (a >= 39 && b >= 39))
						{
							f(v1) *= -1; moves.push_back(v1);
							f(v2) *= -1; moves.push_back(v2);
						}
						v2 = v1;
					}
		}



		app.clear();
		app.draw(sBackground);
		app.draw(_sBackground);





		client->run();
		sf::Packet pac;
		sf::IpAddress _ip;
		unsigned short _port;
		sf::Socket::Status st = client->uSocket.receive(pac, _ip, _port);
		if (st == sf::Socket::Status::Done) {
			uint32_t t;
			pac >> t;
			pac >> t;
		}
		for (int z = 0; z < 10; z++) {
			for (int x = 30; x >= 0; x--) {
				for (int y = 0; y < 18; y++) {
					if (st==sf::Socket::Status::Done)
						pac >> _k[z][x][y] >> _h[z][x][y];
					if (_h[z][x][y] == 2)
						continue;
					s.setTextureRect(IntRect(_k[z][x][y] * w, _h[z][x][y], w, h));
					s.setPosition(x * stepX + z * offX + 740, y * stepY - z * offY);
					s.move(30, 0);
					if (client->status == WAN_client::clientstatus::PLAYING)
						app.draw(s);
				}
			}
		}

		pac.clear();
		pac << client->roomNumber << client::gametype::MAHJONG;
		for (int z = 0; z < 10; z++)
			for (int x = 30; x >= 0; x--)
				for (int y = 0; y < 18; y++)
				{
					int k = f(x, y, z) - 1;
					pac << k;
					if (k < 0) {
						pac << 2;
						continue;
					}
					int _h = 0;
					s.setTextureRect(IntRect(k * w, 0, w, h));
					if (isOpen(x, y, z)) {
						s.setTextureRect(IntRect(k * w, h, w, h));
						_h = 1;
					}
					pac << _h;
					s.setPosition(x * stepX + z * offX, y * stepY - z * offY);
					s.move(30, 0); //desk offset
					app.draw(s);
				}
		if (client->status == WAN_client::clientstatus::PLAYING) {
			client->uSocket.send(pac, client->server_add, client->server_port);
		}
		app.display();
	}
}