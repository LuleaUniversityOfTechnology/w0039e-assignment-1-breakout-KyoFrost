#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"

void SpawnBall()
{
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, 60 }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, 1 }) * BALL_SPEED;
}

void SetupScene()
{
	int startX = (DISPLAY_WIDTH - BRICK_COLUMNS * (BRICK_WIDTH + BRICK_SPACING) + BRICK_WIDTH) / 2;
	int startY = DISPLAY_HEIGHT - BRICK_START_Y - BRICK_ROWS * (BRICK_HEIGHT + BRICK_SPACING) + BRICK_HEIGHT / 2;
	for (int y = 0; y < BRICK_ROWS; ++y)
	{
		for (int x = 0; x < BRICK_COLUMNS; ++x)
		{
			int xPos = x * (BRICK_WIDTH + BRICK_SPACING) + startX;
			int yPos = y * (BRICK_HEIGHT + BRICK_SPACING) + startY;
			const int objectId = Play::CreateGameObject(ObjectType::TYPE_BRICK, { xPos, yPos }, 6, "brick");
		}
	}
}

void StepFrame(float elapsedTime)
{
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	for (const int& ballId : ballIds)
	{
		Play::GameObject& ball = Play::GetGameObject(ballId);
		if (ball.pos.x + BALL_SIZE >= DISPLAY_WIDTH ) // Collision right
		{
			ball.velocity.x = -abs(ball.velocity.x); // Move left
			ball.pos.x = DISPLAY_WIDTH - BALL_SIZE;
		}
		else if (ball.pos.x <= 0) // Collision left
		{
			ball.velocity.x = abs(ball.velocity.x); // Move right
			ball.pos.x = 0;
		}

		if (ball.pos.y + BALL_SIZE >= DISPLAY_HEIGHT ) // Collision top
		{
			ball.velocity.y = -abs(ball.velocity.y); // Move down
			ball.pos.y = DISPLAY_HEIGHT - BALL_SIZE;
		}
		else if (ball.pos.y <= 0) // Collision bottom
		{
			ball.velocity.y = abs(ball.velocity.y); // Move up
			ball.pos.y = 0;
		}
		Play::UpdateGameObject(ball);
	
		Play::DrawObject(ball);
	}

	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	for (const int& brickId : brickIds)
	{
		Play::GameObject& brick = Play::GetGameObject(brickId);
		Play::UpdateGameObject(brick);
		Play::DrawObject(brick);

		// Check collision between brick and balls
		for (const int& ballId : ballIds)
		{
			Play::GameObject& ball = Play::GetGameObject(ballId);
			if (Play::IsColliding(ball, brick))
			{
				Play::DestroyGameObject(brickId);
				ball.velocity.y *= -1;
			}
		}
	}
}

