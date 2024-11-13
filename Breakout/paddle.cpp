#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "paddle.h"

void UpdatePaddle(Paddle& paddle, float elapsedTime)
{
	if (Play::KeyDown(Play::KEY_LEFT) || Play::KeyDown(Play::KEY_A))
	{
		paddle.position.x -= PADDLE_SPEED * elapsedTime;
	}
	if (Play::KeyDown(Play::KEY_RIGHT) || Play::KeyDown(Play::KEY_D))
	{
		paddle.position.x += PADDLE_SPEED * elapsedTime;
	}

	// Keep inside screen
	if (paddle.position.x + PADDLE_WIDTH / 2 > DISPLAY_WIDTH)
	{
		paddle.position.x = DISPLAY_WIDTH - PADDLE_WIDTH / 2;
	}
	else if (paddle.position.x - PADDLE_WIDTH / 2 < 0)
	{
		paddle.position.x = PADDLE_WIDTH / 2;
	}
}

void DrawPaddle(const Paddle& paddle)
{
	Play::Point2D bottomLeft = Play::Point2D(paddle.position.x - PADDLE_WIDTH / 2, paddle.position.y - PADDLE_HEIGHT / 2);
	Play::Point2D topRight = bottomLeft + Play::Point2D(PADDLE_WIDTH, PADDLE_HEIGHT);
	Play::DrawRect(bottomLeft, topRight, Play::cCyan, true);
}

bool IsColliding(const Paddle& paddle, const Play::GameObject& object)
{
	Play::Point2D bottomLeft = Play::Point2D(paddle.position.x - PADDLE_WIDTH / 2, paddle.position.y - PADDLE_HEIGHT / 2);
	Play::Point2D topRight = bottomLeft + Play::Point2D(PADDLE_WIDTH, PADDLE_HEIGHT);

	const float dx = object.pos.x - Max(bottomLeft.x, Min(object.pos.x, topRight.x));
	const float dy = object.pos.y - Max(topRight.y, Min(object.pos.y, bottomLeft.y));
	return (dx * dx + dy * dy) < (object.radius * object.radius);
}

float Min(float a, float b)
{
	return (a < b) ? a : b;
}

float Max(float a, float b)
{
	return (a > b) ? a : b;
}