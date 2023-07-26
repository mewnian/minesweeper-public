#include <cstdlib>
#include <utility>

#include "Global.h"

// Constant
#define INF 1e18

// Default config
int N_ROWS = 9;
int N_COLS = 9;
int N_BOMBS = 10;

const int MIN_ROWS = 3;
const int MIN_COLS = 3;
const int MIN_BOMBS = 1;

const int MAX_ROWS = 24;
const int MAX_COLS = 30;

const float SCREEN_WIDTH = 1280.0f;
const float SCREEN_HEIGHT = 720.0f;
const float BOARD_MARGIN_TOP = 120.0f;
const float BOARD_MARGIN_BOTTOM = 20.0f;
const float BOARD_MARGIN_LEFT = 20.0f;
const float BOARD_MARGIN_RIGHT = 20.0f;
const float BOARD_CANVAS_WIDTH = SCREEN_WIDTH - BOARD_MARGIN_LEFT - BOARD_MARGIN_RIGHT;
const float BOARD_CANVAS_HEIGHT = SCREEN_HEIGHT - BOARD_MARGIN_TOP - BOARD_MARGIN_BOTTOM;

namespace Assets
{
    Texture2D cellTexture;
    Texture2D backgroundTexture;
    Texture2D saveButtonTexture;
    Texture2D pauseButtonTexture;
    Texture2D playButtonTexture;
    Texture2D backButtonTexture;
    Texture2D playAgainButtonTexture;
    Texture2D mainMenuButtonTexture;
    Texture2D newGameButtonTexture;
    Texture2D loadSavedGameButtonTexture;
    Texture2D resumeButtonTexture;
    Texture2D easyModeTexture;
    Texture2D mediumModeTexture;
    Texture2D hardModeTexture;
    Texture2D decreaseButtonTexture;
    Texture2D increaseButtonTexture;
    Image iconImage;
    Font fontSignika;

    void LoadAssets()
    { 
        Image backgroundImage = LoadImage("../resources/background.png");
        backgroundTexture = LoadTextureFromImage(backgroundImage);
        fontSignika = LoadFontEx("../resources/font/signika/regular.ttf", 400, NULL, 0);
        cellTexture = LoadTexture("../resources/cells.png");
        saveButtonTexture = LoadTexture("../resources/save_button.png");
        pauseButtonTexture = LoadTexture("../resources/pause_button.png");
        playButtonTexture = LoadTexture("../resources/play_button.png");
        backButtonTexture = LoadTexture("../resources/back_button.png");
        playAgainButtonTexture = LoadTexture("../resources/play_again_button.png");
        mainMenuButtonTexture = LoadTexture("../resources/main_menu_button.png");
        newGameButtonTexture = LoadTexture("../resources/new_game_button.png");
        loadSavedGameButtonTexture = LoadTexture("../resources/load_saved_game_button.png");
        resumeButtonTexture = LoadTexture("../resources/resume_button.png");
        easyModeTexture = LoadTexture("../resources/easy_mode.png");
        mediumModeTexture = LoadTexture("../resources/medium_mode.png");
        hardModeTexture = LoadTexture("../resources/hard_mode.png");
        decreaseButtonTexture = LoadTexture("../resources/decrease_button.png");
        increaseButtonTexture = LoadTexture("../resources/increase_button.png");
        iconImage = LoadImage("../resources/icon.png");
    }
}
