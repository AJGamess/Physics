/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "trigonometry.h"
#include "vector_scene.h"
#include "spring_scene.h"

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

	//Scene* scene = new TrigonometryScene("Trigonometry", 1280, 720);
	Scene* scene = new SpringScene("Spring", 1280, 720);
	scene->Initialize();	// initialize the scene

	float timeAccum = 0.0f;
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		scene->Update();	// update the game state
		timeAccum += std::min(GetFrameTime(), 0.5f);	// get the time since the last frame
		while (timeAccum >= Scene::fixedTimeStep)	// fixed time step for physics
		{
			scene->FixedUpdate();
			timeAccum -= Scene::fixedTimeStep;
		}
		scene->BeginDraw();	// start drawing
		scene->Draw();	// draw the game state
		scene->DrawGUI();	// draw the GUI
		scene->EndDraw();	// end drawing

	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
