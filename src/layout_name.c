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
#include "raymath.h"
#include "raygui.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int layout_name_main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    bool showTextBox = false;
    int textBoxTextLength = 0;
    char textBoxText[256] = "Text box";
    bool textBoxEditMode = false;

    int spinnerValue = 0;
    bool spinnerEditMode = false;

    int listViewScrollIndex = 0;
    int listViewActive = -1;
    int listViewExScrollIndex = 0;
    int listViewExActive = 2;

    float sliderValue = 50.0f;
    float sliderBarValue = 50.0f;

    float progressValue = 0.0f;

    bool forceSquaredChecked = false;
    int dropDownBoxActive = 0;
    bool dropDownEditMode = false;

    Vector2 anchor01 = { 72, 48 };
    Vector2 anchor02 = { 96, 96 };
    Vector2 anchor03 = { 96, 288 };
    Vector2 anchor04 = { 96, 384 };

    bool windowBoxActive = true;

    float massValue = 1.0f;
    float sizeValue = 0.5f;
    float gravityScaleValue = 1.0f;
    float dampingValue = 0.2f;
    float restitutionValue = 0.5f;
    bool bodyTypeEditMode = false;
    int bodyTypeActive = 0;
    float springDampingValue = 0.5f;
    float stiffnessValue = 1.0f;
    float gravitationValue = 0.0f;
    float gravityValue = 0.0f;
    bool simulateActive = true;
    bool resetPressed = false;
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // layout_name: gui drawing
            //----------------------------------------------------------------------------------
            // Window Box: windowBoxActive
            if (windowBoxActive)
            {
                windowBoxActive = !GuiWindowBox((Rectangle){ 24, 24, 280, 352 }, "Window Box");

                GuiGroupBox((Rectangle){ 40, 48, 248, 320 }, "Group Box");

                GuiLabel((Rectangle){ 56, 72, 216, 24 }, "This is a label");

                GuiButton((Rectangle){ 56, 104, 216, 24 }, "Button");

                if (GuiButton((Rectangle){ 56, 136, 216, 24 }, "Button"))
                {
                    showTextBox = !showTextBox;
                }

                GuiLabel((Rectangle){ 56, 168, 216, 24 }, "DropDownBox");

                if (GuiDropdownBox((Rectangle){ 56, 192, 216, 24 }, "ONE;TWO;THREE;FOUR", &dropDownBoxActive, dropDownEditMode)) dropDownEditMode = !dropDownEditMode;

                GuiLabel((Rectangle){ 56, 224, 216, 24 }, "ValueBox & Spinner");

                GuiValueBox((Rectangle){ 56, 248, 108, 24 }, NULL, &spinnerValue, 0, 100, spinnerEditMode);
                spinnerEditMode = GuiSpinner((Rectangle){ 172, 248, 108, 24 }, NULL, &spinnerValue, 0, 100, spinnerEditMode);

                GuiLabel((Rectangle){ 56, 280, 216, 24 }, "ListView");

                GuiListView((Rectangle){ 56, 304, 216, 80 }, "Charmander;Bulbasaur;#44#;Squirtel;MissingNo.", &listViewScrollIndex, &listViewActive);

                // Define an array of strings for the list view
                const char *listViewExItems[] = { "This", "is", "a", "ListViewEx", "Control" };
                int listViewExItemCount = sizeof(listViewExItems) / sizeof(listViewExItems[0]);

                GuiListViewEx((Rectangle){ 56, 392, 216, 80 }, listViewExItems, listViewExItemCount, &listViewExScrollIndex, &listViewExActive, NULL);

                GuiLabel((Rectangle){ 56, 480, 216, 24 }, "ProgressBar");

                GuiProgressBar((Rectangle){ 56, 504, 216, 24 }, NULL, NULL, &progressValue, 0, 100);
                GuiLabel((Rectangle){ 56, 528, 216, 24 }, "Slider");

                GuiSlider((Rectangle){ 56, 552, 216, 24 }, "TEST", TextFormat("%2.2f", sliderValue), &sliderValue, -50, 100);
                GuiSliderBar((Rectangle){ 56, 584, 216, 24 }, NULL, TextFormat("%2.2f", sliderBarValue), &sliderBarValue, 0, 100);

                GuiLabel((Rectangle){ 56, 616, 216, 24 }, "CheckBox");

                forceSquaredChecked = GuiCheckBox((Rectangle){ 56, 640, 24, 24 }, "FORCE_SQUARED", forceSquaredChecked);

                GuiLabel((Rectangle){ 56, 672, 216, 24 }, "Toggle");

                GuiToggle((Rectangle){ 56, 696, 216, 24 }, "FORCE_SQUARED", forceSquaredChecked);

                GuiLabel((Rectangle){ 56, 728, 216, 24 }, "ToggleGroup");

                GuiToggleGroup((Rectangle){ 56, 752, 216, 24 }, "#1#ONE\n#3#TWO\n#8#THREE\n#23#", &bodyTypeActive);
            }

            // Text Box: showTextBox
            if (showTextBox)
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
                int result = GuiTextBox((Rectangle){ GetScreenWidth()/2 - 100, GetScreenHeight()/2 - 50, 200, 100 }, textBoxText, 256, textBoxEditMode);
                if (result == 1) textBoxEditMode = !textBoxEditMode;
            }
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

