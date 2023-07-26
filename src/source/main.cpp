#include "raylib.h"

#include "Global.h"

#include "Game.h"
#include "HomeScreen.h"
#include "GameOverScreen.h"
#include "SelectionScreen.h"

WindowState CurrentWindow = HOME_SCREEN;
Game game;
HomeScreen home;
GameOverScreen gameOver;
SelectionScreen selection;
Vector2 currentMousePosition;

// process input - check for mouse and keyboard input and change
// update - check condition to see if game should be continued

void ProcessInput()
{
    currentMousePosition = GetMousePosition();
    switch (CurrentWindow) 
    {
        case SELECTION_SCREEN:
        {
            WindowState newWindowState = selection.CheckMouseAction(currentMousePosition);
            switch (newWindowState)
            {   
                case GAME_SCREEN:
                {
                    game = Game(N_ROWS, N_COLS, N_BOMBS);
                    break;
                }
                case HOME_SCREEN:
                {
                    home = HomeScreen();
                    break;
                }
            }
            CurrentWindow = newWindowState;
            break;
        }
        case GAMEOVER_SCREEN:
        {
            WindowState newWindowState = gameOver.CheckMouseAction(currentMousePosition);
            switch (newWindowState)
            {   
                case GAME_SCREEN:
                {
                    game.ResetGame();
                    break;
                }
                case HOME_SCREEN:
                {
                    home = HomeScreen();
                    break;
                }
            }
            CurrentWindow = newWindowState;
            break;
        }
        case GAME_SCREEN: 
        {
            WindowState newWindowState = game.CheckMouseAction(currentMousePosition);
            switch (newWindowState)
            {   
                case GAMEOVER_SCREEN:
                {
                    gameOver = GameOverScreen(game);
                    break;
                }
                case HOME_SCREEN:
                {
                    home = HomeScreen();
                    break;
                }
            }
            CurrentWindow = newWindowState;
            break;
        }
        case HOME_SCREEN:
        {
            WindowState newWindowState = home.CheckMouseAction(currentMousePosition);
            switch (newWindowState)
            {   
                case SELECTION_SCREEN:
                {
                    selection = SelectionScreen();
                    break;
                }
                case GAME_SCREEN:
                {
                    game = Game(N_ROWS, N_COLS, N_BOMBS);
                    break;
                }
                case LOAD_GAME_SCREEN:
                {
                    game = Game("../build/savefile.dat");
                    newWindowState = GAME_SCREEN;
                    break;
                }
            }
            CurrentWindow = newWindowState;
            break;
        }
    }
}

void UpdateGame()
{
    switch (CurrentWindow) 
    {
        case SELECTION_SCREEN:
            break;
        case GAMEOVER_SCREEN:
            break;
        case GAME_SCREEN:
        {
            WindowState newWindowState = game.Update();
            if (newWindowState == GAMEOVER_SCREEN)
            {
                gameOver = GameOverScreen(game);
            }
            CurrentWindow = newWindowState;
            break;
        }
        case HOME_SCREEN:
            break;
    }
}

void GenerateOutput()
{
    BeginDrawing();
    ClearBackground(BLUE);
    DrawTexture(Assets::backgroundTexture, 0, 0, WHITE);

    switch (CurrentWindow) 
    {
        case SELECTION_SCREEN:
        {
            selection.Draw();
            break;
        }
        case GAMEOVER_SCREEN:
        {
            game.Draw();
            gameOver.Draw();
            break;
        }
        case GAME_SCREEN:
        {
            game.Draw();
            break;
        }
        case HOME_SCREEN:
        {
            home.Draw();
            break;
        }
    }

    EndDrawing();
}

void Initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minesweeper");
    Assets::LoadAssets();
    SetWindowIcon(Assets::iconImage);
    PersonalBestScore::LoadData();
    game = Game();
    home = HomeScreen();
}

void RunLoop()
{
    while (!WindowShouldClose())
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void ShutDown()
{
    CloseWindow();
}

int main()
{
    Initialise();
    RunLoop();
    ShutDown();
    return 0;
}