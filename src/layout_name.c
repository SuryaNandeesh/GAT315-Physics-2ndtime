/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    bool WindowBox000Active = true;
    float massSliderValueValue = 0.0f;
    float sizeSliderValueValue = 0.0f;
    float gravityScaleSliderValueValue = 0.0f;
    float dampingSliderValueValue = 0.0f;
    bool bodyTypeDropdownBoxEditMode = false;
    int bodyTypeDropdownBoxActive = 0;
    float worldGravitySliderValueValue = 0.0f;
    float restitutionSliderValueValue = 0.0f;
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            if (bodyTypeDropdownBoxEditMode) GuiLock();

            if (WindowBox000Active)
            {
                WindowBox000Active = !GuiWindowBox((Rectangle){ 80, 56, 216, 584 }, "SAMPLE TEXT");
                GuiPanel((Rectangle){ 104, 88, 144, 328 }, NULL);
                GuiLabel((Rectangle){ 112, 96, 120, 24 }, "MASS");
                GuiSlider((Rectangle){ 112, 128, 120, 16 }, NULL, NULL, &massSliderValueValue, 0, 100);
                GuiLabel((Rectangle){ 112, 160, 120, 24 }, "SIZE");
                GuiSlider((Rectangle){ 112, 192, 120, 16 }, NULL, NULL, &sizeSliderValueValue, 0, 100);
                GuiLabel((Rectangle){ 112, 224, 120, 24 }, "GRAVITY SCALE");
                GuiSlider((Rectangle){ 112, 256, 120, 16 }, NULL, NULL, &gravityScaleSliderValueValue, 0, 100);
                GuiLabel((Rectangle){ 112, 288, 120, 24 }, "DAMPING");
                GuiSlider((Rectangle){ 112, 320, 120, 16 }, NULL, NULL, &dampingSliderValueValue, 0, 100);
                GuiLine((Rectangle){ 88, 424, 184, 16 }, NULL);
                GuiSlider((Rectangle){ 104, 616, 120, 16 }, NULL, NULL, &worldGravitySliderValueValue, 0, 100);
                GuiLabel((Rectangle){ 104, 584, 120, 24 }, "WORLD GRAVITY");
                GuiSlider((Rectangle){ 112, 384, 120, 16 }, NULL, NULL, &restitutionSliderValueValue, 0, 100);
                if (GuiDropdownBox((Rectangle){ 104, 448, 144, 24 }, "DYNAMIC;STATIC;KINEMATIC", &bodyTypeDropdownBoxActive, bodyTypeDropdownBoxEditMode)) bodyTypeDropdownBoxEditMode = !bodyTypeDropdownBoxEditMode;
            }
            GuiLabel((Rectangle){ 112, 352, 120, 24 }, "RESTITUTION");
            
            GuiUnlock();
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------

