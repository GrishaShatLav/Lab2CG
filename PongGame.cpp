#include "PongGame.h"
#include "Keys.h"
#include <string>

static float DifficultyCurve(unsigned ballHits)
{
    return 5.0f / (1.0f + exp(- static_cast<float>(ballHits) / 8.0f + 4.0f)) + 1.0f;
}

void PongGame::Update()
{
    ball->Speed = DifficultyCurve(ballHits);
    if (InputDev->IsKeyDown(Keys::Escape))
        isExitRequested = true;
    if (state == PONG_STATE_COOLDOWN && std::chrono::steady_clock::now() >= ContinueTime)
        state = PONG_STATE_NORMAL;
	if (InputDev->IsKeyDown(Keys::W) && racket1->GetY() < 0.8f)
		racket1->SetY(racket1->GetY() + DeltaTime * racket1->Speed);
	if (InputDev->IsKeyDown(Keys::S) && racket1->GetY() > -0.8f)
		racket1->SetY(racket1->GetY() - DeltaTime * racket1->Speed);

#ifdef RIGHT_BOT
    if (abs(racket2->GetY() - ball->GetY()) > 0.1f)
    {
        if (racket2->GetY() < ball->GetY() && racket2->GetY() < 0.8f)
            racket2->SetY(racket2->GetY() + DeltaTime * racket2->Speed);
        if (racket2->GetY() > ball->GetY() && racket2->GetY() > -0.8f)
            racket2->SetY(racket2->GetY() - DeltaTime * racket2->Speed);
    }
#else
    if (InputDev->IsKeyDown(DirectX::Keyboard::Keys::Up) && racket2->GetY() < 0.8f)
        racket2->SetY(racket2->GetY() + DeltaTime * racket2->Speed);
    if (InputDev->IsKeyDown(DirectX::Keyboard::Keys::Down) && racket2->GetY() > -0.8f)
        racket2->SetY(racket2->GetY() - DeltaTime * racket2->Speed);
#endif
    
    Game::Update();
}

PongGame::PongGame() : Game(L"MyGame", 800, 800)
{
	srand(static_cast<unsigned>(time(nullptr)));
	racket1 = new RacketComponent(this);
	racket1->SetX(-0.9f);
	racket2 = new RacketComponent(this);
	racket2->SetX(0.9f);
	ball = new BallComponent(this);
	Components.push_back(racket1);
	Components.push_back(racket2);
	Components.push_back(ball);
    state = PONG_STATE_COOLDOWN;
    ContinueTime = std::chrono::steady_clock::now() + std::chrono::seconds(1);
    ballHits = 0;
}

void PongGame::IncScore(bool p)
{
	if (p)
		s1 += 1;
	else
		s2 += 1;
    std::cout << "P1: " << s1 << ", P2: " << s2 << "\n";
    if (s1 > 10 || s2 > 10)
    {
        state = PONG_STATE_GAMEOVER;
        if (s1 > 10)
            std::cout << "P1 won\n";
        if (s2 > 10)
            std::cout << "P2 won\n";
    }
}
