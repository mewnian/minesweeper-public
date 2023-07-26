#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"

#include <utility>

// Constant
#define INF 1e18

// Default config
extern int N_ROWS;
extern int N_COLS;
extern int N_BOMBS;

extern const int MIN_ROWS;
extern const int MIN_COLS;
extern const int MIN_BOMBS;

extern const int MAX_ROWS;
extern const int MAX_COLS;

// Current window state
#define HOME_SCREEN 1
#define GAME_SCREEN 2
#define GAMEOVER_SCREEN 3
#define LOAD_GAME_SCREEN 4
#define SELECTION_SCREEN 5

using WindowState = short;

// Click state
#define NO_CLICK 0 
#define LEFT_CLICK 1
#define RIGHT_CLICK 2
#define HOLD_CLICK 3

using ClickState = short;

// Game state
#define GAME_NOT_STARTED 0
#define GAME_ONGOING 1
#define GAME_OVER_LOSE -1
#define GAME_OVER_WIN 2
#define GAME_PAUSED 3

using GameState = short;

// Cell state
#define CELL_NUM_EMPTY(BOMB_NEIGHBORS) (BOMB_NEIGHBORS)
#define CELL_BOMB 9
#define CELL_BOMB_OPENED 10
#define CELL_NOT_OPENED 11
#define CELL_HIGHLIGHTED 12
#define CELL_FLAGGED 13
#define CELL_FLAGGED_WRONG 14

using CellState = short;

using SaveConfig = std::tuple<int, int, int, int, int>;

extern const float SCREEN_WIDTH;
extern const float SCREEN_HEIGHT;
extern const float BOARD_MARGIN_TOP;
extern const float BOARD_MARGIN_BOTTOM;
extern const float BOARD_MARGIN_LEFT;
extern const float BOARD_MARGIN_RIGHT;
extern const float BOARD_CANVAS_WIDTH;
extern const float BOARD_CANVAS_HEIGHT;

namespace Assets
{
    extern Texture2D cellTexture;
    extern Texture2D backgroundTexture;
    extern Texture2D saveButtonTexture;
    extern Texture2D pauseButtonTexture;
    extern Texture2D playButtonTexture;
    extern Texture2D backButtonTexture;
    extern Texture2D playAgainButtonTexture;
    extern Texture2D mainMenuButtonTexture;
    extern Texture2D newGameButtonTexture;
    extern Texture2D loadSavedGameButtonTexture;
    extern Texture2D resumeButtonTexture;
    extern Texture2D easyModeTexture;
    extern Texture2D mediumModeTexture;
    extern Texture2D hardModeTexture;
    extern Texture2D decreaseButtonTexture;
    extern Texture2D increaseButtonTexture;
    extern Image iconImage;
    extern Font fontSignika;

    void LoadAssets();
}

#endif