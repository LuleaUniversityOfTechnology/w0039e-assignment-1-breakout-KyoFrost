#pragma once

#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "constants.h"
#include "paddle.h"

void SpawnBall();

void SetupScene();

void StepFrame(float elapsedTime);