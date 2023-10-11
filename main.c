//---------------------------------------------------------
// file:	main.c
// author:	Parth Khanija
// email:	parth.khanija@digipen.edu
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "palettes.h"
#include "button.h"
#include <stdio.h>
#include <stdlib.h>

#define bulletCount 50

CP_Color purples[10];
CP_Color gray[10];
CP_Color blues[10];

float degrees;
CP_Vector turretPos;
CP_Vector mousePos;
CP_Vector aim;

typedef struct bullet {
	CP_Vector position;
	CP_Vector velocity;
	int isAlive;
}bullet;

bullet bull;
bullet bullets[bulletCount];

// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void game_init(void)
{
	CP_System_SetWindowSize(1200, 800);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_NoStroke();

	load_grayscale_palette(gray);
	load_purple_palette(purples);
	load_blues_palette(blues);

	turretPos = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() + 15.0f);

	for (int i = 0; i < bulletCount; i++) {
		bullets[i].isAlive = 0;
	}
}

void game_update(void)
{
	mousePos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	aim = CP_Vector_Subtract(mousePos, turretPos);
	aim.y = -aim.y;
	degrees = CP_Vector_Angle(aim, CP_Vector_Set(10, 0));

	CP_Graphics_ClearBackground(gray[2]);

	//bullet
	CP_Settings_Fill(gray[9]);
	//if (CP_Input_MouseClicked()) {
	//	//CP_Vector dir = aim;
	//	bull.isAlive = 1;
	//	bull.position = turretPos;
	//	bull.velocity = CP_Vector_Normalize(aim);
	//}
	//if (bull.isAlive == 1) {
	//	
	//	bull.position.x += bull.velocity.x * 50.0f;
	//	bull.position.y -= bull.velocity.y * 50.0f;
	//	//bull.position = CP_Vector_Add(bull.position, CP_Vector_Scale(bull.velocity, -10.0f));
	//	CP_Graphics_DrawEllipse(bull.position.x, bull.position.y, 20.0f, 20.0f);
	//}

	//for (int i = 0; i < sizeof(bullets); i++) {
	//	
	//}
	//bullets
	if (CP_Input_MouseClicked()) {
		for (int i = 0; i < bulletCount; i++) {
			if (bullets[i].isAlive == 0) {
				bullets[i].isAlive = 1;
				bullets[i].position = turretPos;
				bullets[i].velocity = CP_Vector_Normalize(aim);
				break;
			}
		}
	}
	for (int i = 0; i < bulletCount; i++) {
		if (bullets[i].isAlive == 1) {

			bullets[i].position.x += bullets[i].velocity.x * 50.0f;
			bullets[i].position.y -= bullets[i].velocity.y * 50.0f;
			//bull.position = CP_Vector_Add(bull.position, CP_Vector_Scale(bull.velocity, -10.0f));
			CP_Graphics_DrawEllipse(bullets[i].position.x, bullets[i].position.y, 20.0f, 20.0f);
		}
		if (bullets[i].position.x < 0.0f || bullets[i].position.x > CP_System_GetWindowWidth() || bullets[i].position.y < 0.0f) {
			bullets[i].isAlive = 0;
		}
	}


	CP_Settings_Fill(gray[8]);
	CP_Graphics_DrawEllipse(turretPos.x, turretPos.y, 150.0f, 150.0f);

	CP_Graphics_DrawRectAdvanced(turretPos.x, turretPos.y, 250.0f, 30.0f, -degrees, 0.0f);

	
	



	//texts
	CP_Settings_TextSize(30.0f);
	char buffer[50] = { 0 };
	sprintf_s(buffer, _countof(buffer), "mouse pos: %lf , %lf", mousePos.x, mousePos.y);
	CP_Font_DrawText(buffer, 300, 30);

	char buffer3[50] = { 0 };
	sprintf_s(buffer3, _countof(buffer3), "aim vec: %lf , %lf", aim.x, aim.y);
	CP_Font_DrawText(buffer3, 300, 70);

	char buffer2[50] = { 0 };
	sprintf_s(buffer2, _countof(buffer2), "isalive: %i", bullets[0].isAlive);
	CP_Font_DrawText(buffer2, 300, 50);

}


void game_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
