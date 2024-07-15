//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.c
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
#include "Level1Scene.h"
#include "Stream.h"
#include "Level2Scene.h"
#include "Mesh.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "DGL.h"
#include "Transform.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

static const DGL_Vec2 posMesh = { 0.0f, 0.0f };
static const DGL_Vec2 scaleMesh = { 100.0f, 100.0f };

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level1Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	int numLives;

} Level1Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static DGL_Vec2 posCamera = { 0, 0 };
static Mesh* my_mesh;
static Sprite* my_sprite;
static SpriteSource* my_sprite_source;
static Transform* my_transform;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level1SceneLoad(void);
static void Level1SceneInit(void);
static void Level1SceneUpdate(float dt);
static void Level1SceneExit(void);
static void Level1SceneUnload(void);
static void Level1SceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level1Scene instance =
{
	// Initialize the base structure:
	{ "Level1", Level1SceneLoad, Level1SceneInit, Level1SceneUpdate, Level1SceneRender, Level1SceneExit, Level1SceneUnload },

	// Initialize any scene-specific variables:
	0	// numLives
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Level1Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* Level1SceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level1SceneLoad(void)
{
	// Load the number of lives from the file
	Stream s = StreamOpen("Data/Level1_Lives.txt");
	if (s)
	{
		instance.numLives = StreamReadInt(s);
		StreamClose(&s);
	}

	// Create a mesh
	my_mesh = MeshCreate();
	MeshBuildQuad(my_mesh, 50.0f, 50.0f, 1.0f, 1.0f, "booboo");

	// Create a sprite
	my_sprite = SpriteCreate();
	SpriteSetMesh(my_sprite, my_mesh);

	// Create a sprite source
	my_sprite_source = SpriteSourceCreate();
	SpriteSourceLoadTexture(my_sprite_source, 1, 1, "ball.png");
	SpriteSetSpriteSource(my_sprite, my_sprite_source);

	// Set the transform
	my_transform = TransformCreate();

	Vector2D new_pos = { 5.0f, 15.0f };
	TransformSetTranslation(my_transform, &new_pos);
	float new_rot = 3.14159f / 4.0f;
	TransformSetRotation(my_transform, new_rot);
	Vector2D new_scale = { 2.0f, 4.0f };
	TransformSetScale(my_transform, &new_scale);

	TransformGetTranslation(my_transform);
	TransformGetRotation(my_transform);
	TransformGetScale(my_transform);
}

// Initialize the entities and variables used by the scene.
static void Level1SceneInit()
{
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level1SceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	// Decrement lives
	// instance.numLives -= 1;

	// Check if we are out of lives - switch to Level 2
	if (instance.numLives <= 0)
	{
		SceneSystemSetNext(Level2SceneGetInstance());
	}
}

// Render any objects associated with the scene.
void Level1SceneRender(void)
{
	DGL_Camera_SetPosition(&posCamera);

	SpriteRender(my_sprite, my_transform);
}

// Free any objects associated with the scene.
static void Level1SceneExit()
{
}

// Unload any resources used by the scene.
static void Level1SceneUnload(void)
{
	MeshFree(&my_mesh);
	TransformFree(&my_transform);
	SpriteFree(&my_sprite);
	SpriteSourceFree(&my_sprite_source);
}