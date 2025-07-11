/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/
//#include "vector_scene.h"
#include "trigonometry_scene.h"
#include "polarscene.h"
#include "fireworks_scene.h"
#include "vector_scene.h"
#include "spring_scene.h"
#include "angry_birds_scene.h"
//#include "pool_scene.h"

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 720, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	//Scene* scene = new TrigonometryScene("trigonometry", 1280, 720);
	//Scene* scene = new PolarScene("polar", 1280, 720);
	//Scene* scene = new FireworksScene("fireworks", 1280, 720);
	//Scene* scene = new VectorScene("vector", 1280, 720);
	//Scene* scene = new SpringScene("spring", 1280, 720);
	Scene* scene = new AngryBirdsScene("angry_birds", 1280, 720);
	scene->Initialize();

	SetTargetFPS(60);
	float timeAccum = 0.0f;

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		scene->Update();
		timeAccum += std::min(GetFrameTime(), 0.9f);
		while (timeAccum >= Scene::fixedTimestep)
		{
			scene->FixedUpdate();
			timeAccum -= Scene::fixedTimestep;
		}
		scene->BeginDraw();
		scene->Draw();
		scene->DrawGUI();
		scene->EndDraw();
	}

	// cleanup
	delete scene;
	CloseWindow();
	return 0;
}
