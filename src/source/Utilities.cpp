#include "Utilities.h"

#include <fstream>
#include <cmath>

#include "Global.h"

namespace PersonalBestScore
{
    std::map< std::tuple<int, int, int>, float > BestScore;

    void LoadData()
    {
        std::ifstream inf;
        inf.open("../build/highscore.dat");
        if (inf)
        {
            int rows, cols, bombs; float score;
            while (inf >> rows >> cols >> bombs >> score) 
            {
                if (MIN_ROWS <= rows && rows <= MAX_ROWS && MIN_COLS <= cols && cols <= MAX_COLS && MIN_BOMBS <= bombs && bombs <= rows * cols - 1)
                    BestScore[std::make_tuple(rows, cols, bombs)] = score;
            }
        }
    }

    bool UpdateData(int rows, int cols, int bombs, float score)
    {    
        if (!(MIN_ROWS <= rows && rows <= MAX_ROWS && MIN_COLS <= cols && cols <= MAX_COLS && MIN_BOMBS <= bombs && bombs <= rows * cols - 1)) return false;
        float compScore = std::round(score * 1000.0f) / 1000.0f;
        if (BestScore.find(std::make_tuple(rows, cols, bombs)) != BestScore.end() 
            && score >= BestScore[std::make_tuple(rows, cols, bombs)]) 
            return false;
        BestScore[std::make_tuple(rows, cols, bombs)] = compScore;
        std::ofstream ouf;
        ouf.open("../build/highscore.dat");
        if (ouf)
        {
            bool firstLine = true;
            for (auto e : BestScore)
            {
                std::tuple<int, int, int> eFirst; float score; std::tie(eFirst, score) = e;
                int rows, cols, bombs; std::tie(rows, cols, bombs) = eFirst;
                if (!firstLine) ouf << std::endl;
                firstLine = false;
                ouf << rows << " " << cols << " " << bombs << " " << score;
            }
        }
        return true;
    }

    float GetPersonalBest(int rows, int cols, int bombs)
    {
        auto e = std::make_tuple(rows, cols, bombs);
        if (BestScore.find(e) != BestScore.end())
            return BestScore[e];
        return INFINITY;
    }
}

namespace Random 
{
    std::mt19937 mt{ static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };

    int randInt(int l_bound, int r_bound)   
    {
        std::uniform_int_distribution<> rnd(l_bound, r_bound);
        return rnd(mt);
    }
}

bool IsSaveFileValid(const char* filename)
{
    std::ifstream inf;
    inf.open(filename);
    if (!inf) return false;

    int b_rows, b_cols, b_bombs, b_opens, b_flags;
    if (!(inf >> b_rows >> b_cols >> b_bombs >> b_opens >> b_flags)) return false;
    if (b_rows < MIN_ROWS || b_rows > MAX_ROWS) return false;
    if (b_cols < MIN_COLS || b_cols > MAX_COLS) return false;
    if (b_bombs < MIN_BOMBS || b_bombs > b_rows * b_cols - 1) return false;
    if (b_opens < 0 || b_opens > MAX_ROWS * MAX_COLS) return false;
    if (b_flags < 0 || b_flags > b_bombs) return false;

    int cnt_bombs = 0, cnt_opens = 0, cnt_flags = 0;
    std::vector< std::vector<int> > b_board(b_rows, std::vector<int>(b_cols, 0));
    for (int i = 0; i < b_rows; ++i)
        for (int j = 0; j < b_cols; ++j)
        {
            if (!(inf >> b_board[i][j])) return false;
            if (b_board[i][j] < -2 || b_board[i][j] > 2) return false;
            cnt_bombs += (b_board[i][j] == -1 || b_board[i][j] == -2);
            cnt_opens += (b_board[i][j] == 1);
            cnt_flags += (b_board[i][j] == 2 || b_board[i][j] == -2);
        }
    if (cnt_bombs != b_bombs || cnt_opens != b_opens || cnt_flags != b_flags) return false;

    float b_timer;
    if (!(inf >> b_timer)) return false;

    return true;
}