//------------------------------------------------------------------------------
//
// File Name:	Level2Scene.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 1
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Scene.h"
#include "SceneSystem.h"
#include "Level2Scene.h"
#include "Stream.h"
#include "SandboxScene.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level2Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	int numLives;
	int numHealth;

} Level2Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level2SceneLoad(void);
static void Level2SceneInit(void);
static void Level2SceneUpdate(float dt);
static void Level2SceneExit(void);
static void Level2SceneUnload(void);
static void Level2SceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level2Scene instance =
{
	// Initialize the base structure:
	{ "Level2", Level2SceneLoad, Level2SceneInit, Level2SceneUpdate, Level2SceneRender, Level2SceneExit, Level2SceneUnload },

	// Initialize any scene-specific variables:
	0,	// numLives
	0	// numHealth
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Level2Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* Level2SceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level2SceneLoad(void)
{
	// Load the number of lives from a file
	Stream s = StreamOpen("Data/Level2_Lives.txt");
	if (s)
	{
		instance.numLives = StreamReadInt(s);
		StreamClose(&s);
	}
}

// Initialize the entities and variables used by the scene.
static void Level2SceneInit()
{
	// Load the number of health from a file
	Stream s = StreamOpen("Data/Level2_Health.txt");
	if (s)
	{
		instance.numHealth = StreamReadInt(s);
		StreamClose(&s);
	}
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level2SceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	// Decrement health
	instance.numHealth -= 1;

	// Check if the player has run out of health
	if (instance.numHealth <= 0)
	{
		instance.numLives -= 1;

		// If we have lives left, restart the scene
		if (instance.numLives > 0)
		{
			SceneSystemRestart();
		}
		// Otherwise, switch to the Sandbox scene
		else
		{
			SceneSystemSetNext(SandboxSceneGetInstance());
		}
	}
}

// Render any objects associated with the scene.
void Level2SceneRender(void)
{
}

// Free any objects associated with the scene.
static void Level2SceneExit()
{
}

// Unload any resources used by the scene.
static void Level2SceneUnload(void)
{
}

