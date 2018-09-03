#include <iostream>
#include <string>
#include <chrono>
#include <windows.h>

#include "GameEngine.hpp"

#define world_height 24
#define world_width 80

char world[world_height][world_width] = { {} };
char defaultWorld[world_height][world_width] = { {} };
Ascii::Rand rng;

float TargetFPS = 10.f;

Ascii::Vector2 getApplePos()
{
	Ascii::Vector2 pos(rng.range(1, world_width - 1), rng.range(1, world_height - 1));
	if (world[pos.y][pos.x] == ' ')
		return pos;
	else
		return getApplePos();
}

int main()
{
	Ascii::Vector2 pos(0, 0);

	age::init("Snake");
	age::setCursorVisible(false);

	enum direction
	{
		RIGHT = 0,
		LEFT = 1,
		UP = 2,
		DOWN = 3
	};

	std::vector<short> snakeDirections = {
		RIGHT, RIGHT, RIGHT, 
		RIGHT, RIGHT, RIGHT
	};

	std::vector<short> lastSnakeDirections = snakeDirections;

	std::vector<Ascii::Vector2> snakePositions = {
		Ascii::Vector2(42, 12),
		Ascii::Vector2(41, 12),
		Ascii::Vector2(40, 12),
		Ascii::Vector2(39, 12),
		Ascii::Vector2(38, 12),
		Ascii::Vector2(37, 12),
	};

	int snakeLength = 6;
	int direction = 0;
	int score = 0;

	bool gameOver = false;

	for (int i = 0; i < world_height; i++)
	{
		for (int j = 0; j < world_width; j++)
		{
			char ch = ' ';

			if (j == 0 || j == world_width - 1)
			{
				ch = '|';
			}
			else if (i == 0 || i == world_height - 1)
			{
				ch = '-';
			}

			if (ch != ' ')
			{
				world[i][j] = ch;
				defaultWorld[i][j] = ch;
				age::print(ch, pos);
			}
			else
			{
				world[i][j] = ' ';
				defaultWorld[i][j] = ' ';
				age::print(' ', pos);
			}

			pos.x++;
		}
		std::cout << "\n";
		pos.x = 0;
		pos.y++;
	}

	for (int i = 0; i < snakeLength; i++)
	{
		age::print('o', snakePositions[i], Ascii::Colours::RED);
	}

	Ascii::Vector2 applePosition(getApplePos());

	age::print('*', applePosition, Ascii::Colours::GREEN);
	world[applePosition.y][applePosition.x] = '*';

	Ascii::Vector2 scoreLocation(0, 24);
	age::print("Score: 0", scoreLocation);

	auto start = std::chrono::high_resolution_clock::now();
	while (1) {
		if (GetAsyncKeyState('W') & 0x8000)
		{
			direction = 2;
		}
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			direction = 1;
		}
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			direction = 3;
		}
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			direction = 0;
		}

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		if (diff.count() > 1.f / TargetFPS && !gameOver)
		{
			bool addNew = false;

			switch (direction)
			{
			case 0:
				TargetFPS = 10.f;
				snakeDirections[0] = RIGHT;
				break;
			case 1:
				TargetFPS = 10.f;
				snakeDirections[0] = LEFT;
				break;
			case 2:
				TargetFPS = 7.5f;
				snakeDirections[0] = UP;
				break;
			case 3:
				TargetFPS = 7.5f;
				snakeDirections[0] = DOWN;
				break;
			}

			for (int i = 0; i < snakeLength; i++)
			{
				Ascii::Vector2 sp = snakePositions[i];
				age::print(' ', sp);
				world[sp.y][sp.x] = ' ';
			}

			for (int i = snakeLength - 1; i >= 0; i--)
			{
				if (i != 0)
				{
					snakeDirections[i] = lastSnakeDirections[i - 1];
				}

				switch(snakeDirections[i])
				{
				case RIGHT:
					snakePositions[i].x += 1;
					break;
				case LEFT:
					snakePositions[i].x -= 1;
					break;
				case DOWN:
					snakePositions[i].y += 1;
					break;
				case UP:
					snakePositions[i].y -= 1;
					break;
				}

				Ascii::Vector2 sp = snakePositions[i];

				if (world[sp.y][sp.x] == '*')
				{
					world[sp.y][sp.x] = ' ';
					applePosition = getApplePos();
					world[applePosition.y][applePosition.x] = '*';
					age::print('*', applePosition, Ascii::Colours::GREEN);

					score++;
					age::print("Score: " + std::to_string(score), scoreLocation);

					addNew = true;
				}
				else if (world[sp.y][sp.x] != ' ' && world[sp.y][sp.x] != '*')
				{
					i = -1;
					gameOver = true;

					for (int j = 0; j < snakeLength; j++)
					{
						Ascii::Vector2 sp2 = snakePositions[j];
						char newch = defaultWorld[sp2.y][sp2.x];
						age::print(newch, sp2);
						world[sp2.y][sp2.x] = newch;
					}

					snakeDirections.clear();
					snakePositions.clear();
				}
				else
				{
					lastSnakeDirections[i] = snakeDirections[i];

					age::print('o', sp, Ascii::Colours::RED);
					world[sp.y][sp.x] = 'o';
				}
			}

			if (addNew)
			{
				Ascii::Vector2 newPosition(0, 0);
				Ascii::Vector2 lastPosition = snakePositions[snakeLength - 1];

				switch (snakeDirections[snakeLength - 1])
				{
				case RIGHT:
					newPosition = Ascii::Vector2(lastPosition.x - 1, lastPosition.y);
					break;
				case LEFT:
					newPosition = Ascii::Vector2(lastPosition.x + 1, lastPosition.y);
					break;
				case UP:
					newPosition = Ascii::Vector2(lastPosition.x, lastPosition.y + 1);
					break;
				case DOWN:
					newPosition = Ascii::Vector2(lastPosition.x, lastPosition.y - 1);
					break;
				}

				snakePositions.push_back(newPosition);
				snakeDirections.push_back(snakeDirections[snakeLength - 1]);
				lastSnakeDirections.push_back(snakeDirections[snakeLength - 1]);
				snakeLength++;
			}

			start = std::chrono::high_resolution_clock::now();
		}
	};

	return 0;
}