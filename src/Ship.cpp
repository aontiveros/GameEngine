// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "../header/Ship.h"
#include "../header/Game.h"
#include "../header/component/AnimSpriteComponent.h"

Ship::Ship(Game* game)
	:Actor(game)
	,mRightSpeed(0.0f)
	,mDownSpeed(0.0f)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
 		game->loadTexture("Assets/Character01.png"),
		game->loadTexture("Assets/Character02.png"),
        game->loadTexture("Assets/Character03.png"),
        game->loadTexture("Assets/Character04.png"),
        game->loadTexture("Assets/Character05.png"),
        game->loadTexture("Assets/Character06.png"),
        game->loadTexture("Assets/Character07.png"),
        game->loadTexture("Assets/Character08.png"),
        game->loadTexture("Assets/Character09.png"),
        game->loadTexture("Assets/Character10.png"),
        game->loadTexture("Assets/Character11.png"),
        game->loadTexture("Assets/Character12.png"),
        game->loadTexture("Assets/Character13.png"),
        game->loadTexture("Assets/Character14.png"),
	};
	asc->setAnimationTextures(anims);
	asc->setAnimationFps(1.0);
	game->addSprite(asc);
	game->addActor(this);
}

void Ship::updateActor(float deltaTime)
{
	Actor::updateActor(deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = getPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;
	// Restrict position to left half of screen
	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 500.0f)
	{
		pos.x = 500.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}
	setPosition(pos);
}

void Ship::processKeyboard(const uint8_t* state)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		mRightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 300.0f;
	}
}
