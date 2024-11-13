#pragma once

#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "constants.h"

struct Paddle
{
	Play::Point2D position;
};

void UpdatePaddle(Paddle& paddle, float elapsedTime);

void DrawPaddle(const Paddle& paddle);

bool IsColliding(const Paddle& paddle, const Play::GameObject& object);

float Min(float a, float b);
float Max(float a, float b);