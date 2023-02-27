#pragma once
#include "Game.h"
#include "RacketComponent.h"
#include "BallComponent.h"
#include <d2d1.h>
#include <dwrite.h>

#define RIGHT_BOT

enum GameState
{
	PONG_STATE_NORMAL,
	PONG_STATE_COOLDOWN,
	PONG_STATE_GAMEOVER
};

class PongGame : public Game
{
protected:
	void Update() override;
	unsigned s1;
	unsigned s2;
public:
	std::chrono::steady_clock::time_point ContinueTime;
	unsigned ballHits;
	RacketComponent* racket1;
	RacketComponent* racket2;
	BallComponent* ball;
	GameState state;
	PongGame();
	void IncScore(bool p);
};
