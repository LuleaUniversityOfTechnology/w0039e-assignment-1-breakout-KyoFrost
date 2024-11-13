#pragma once

const int DISPLAY_WIDTH = 640;
const int DISPLAY_HEIGHT = 360;
const int DISPLAY_SCALE = 2;

const int BALL_SIZE = 8;
const int BALL_SPEED = 2.0f;

const int BRICK_WIDTH = 16;
const int BRICK_HEIGHT = 10;
const int BRICK_ROWS = 8;
const int BRICK_COLUMNS = 35;
const int BRICK_SPACING = 1;
const int BRICK_START_Y = 22;

enum ObjectType
{
	TYPE_BALL,
	TYPE_BRICK
};

