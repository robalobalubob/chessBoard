#pragma once
#pragma warning(disable : 4244)

#include <shobjidl.h>
#include <WinUser.h>
#include <debugapi.h>
#include <wincodec.h>
#include <windows.h>
#include <d2d1.h>
#include <windowsx.h>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>

#ifndef MAX_INT
#define MAX_INT 2147483647
#endif

using std::vector;
using std::string;
using std::pair;

typedef unsigned long long ulong;

enum defMasks : ulong 
{
	COL1 = 0x0101010101010101,
	COL2 = 0x0202020202020202,
	COL3 = 0x0404040404040404,
	COL4 = 0x0808080808080808,
	COL5 = 0x1010101010101010,
	COL6 = 0x2020202020202020,
	COL7 = 0x4040404040404040,
	COL8 = 0x8080808080808080,
	ROW1 = 0x00000000000000FF,
	ROW2 = 0x000000000000FF00,
	ROW3 = 0x0000000000FF0000,
	ROW4 = 0x00000000FF000000,
	ROW5 = 0x000000FF00000000,
	ROW6 = 0x0000FF0000000000,
	ROW7 = 0x00FF000000000000,
	ROW8 = 0xFF00000000000000
};
//#define COL1 0x0101010101010101
//#define COL2 0x0202020202020202
//#define COL3 0x0404040404040404
//#define COL4 0x0808080808080808
//#define COL5 0x1010101010101010
//#define COL6 0x2020202020202020
//#define COL7 0x4040404040404040
//#define COL8 0x8080808080808080
//#define ROW1 0x00000000000000FF
//#define ROW2 0x000000000000FF00
//#define ROW3 0x0000000000FF0000
//#define ROW4 0x00000000FF000000
//#define ROW5 0x000000FF00000000
//#define ROW6 0x0000FF0000000000
//#define ROW7 0x00FF000000000000
//#define ROW8 0xFF00000000000000

enum pieceType
{
    PAWN = 0,
    ROOK = 3,
    KNIGHT = 2,
    BISHOP = 1,
    KING = 5,
    QUEEN = 4
};
enum pieceValues
{
    PAWNval = 1,
    KNIGHTval = 3,
    BISHOPval = 3,
    ROOKval = 5,
    QUEENval = 9,
    KINGval = MAX_INT
};

static ULONGLONG WHITE;
static ULONGLONG BLACK;

static D2D1_POINT_2F convCoordtoPixel(D2D1_POINT_2F coords, D2D1_SIZE_F size, float boardSize) {
    D2D1_POINT_2F sol;
    sol.y = (coords.x * (boardSize/8) - (boardSize/2)) + size.height / 2;
    sol.x = (coords.y * (boardSize / 8) - (boardSize / 2)) + size.width / 2;
    return sol;
}
static D2D1_POINT_2F convPixeltoCoord(D2D1_POINT_2F coords, D2D1_POINT_2F boardcoords, float bsize) {
    D2D1_POINT_2F sol = coords;
    D2D1_POINT_2F pos = boardcoords;
    int p_s = bsize / 8;
    sol.x -= pos.x;
    sol.y -= pos.y;
    sol.x -= (int)sol.x % p_s;
    sol.y -= (int)sol.y % p_s;
    sol.x = (int)sol.x / p_s;
    sol.y = (int)sol.y / p_s;
    float tmp = sol.x;
    sol.x = sol.y;
    sol.y = tmp;
    return sol;
}

//output statement
static void outputnum(float t = 0, int i = 0, D2D1_POINT_2F p2f = { 0,0 }, D2D1_SIZE_F sf = { 0,0 }) {
    string s;
    vector<const char*>p;
    if (t) {
        s = std::to_string(t);
        p.push_back(s.c_str());
        OutputDebugStringA(p.back());
        OutputDebugStringA("\n");
    }
    if (i) {
        s = std::to_string(i);
        p.push_back(s.c_str());
        OutputDebugStringA(p.back());
        OutputDebugStringA("\n");
    }
    if (p2f.x || p2f.y) {
        s = std::to_string(p2f.x);
        p.push_back(s.c_str());
        OutputDebugStringA("{ ");
        OutputDebugStringA(p.back());
        OutputDebugStringA(", ");
        s = std::to_string(p2f.y);
        p.push_back(s.c_str());
        OutputDebugStringA(p.back());
        OutputDebugStringA("}\n");
    }
    if (sf.width || sf.height) {
        s = std::to_string(sf.width);
        p.push_back(s.c_str());
        OutputDebugStringA("{ ");
        OutputDebugStringA(p.back());
        OutputDebugStringA(", ");
        s = std::to_string(sf.height);
        p.push_back(s.c_str());
        OutputDebugStringA(p.back());
        OutputDebugStringA("}\n");
    }
}

static D2D1_RECT_F* createTile(D2D1_SIZE_F size) {
    D2D1_RECT_F* board = new D2D1_RECT_F[64];
    int start = -400 + size.width / 2;
    int starty = -400 + size.height / 2;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i * 8 + j] = D2D1::RectF(start + 100 * j, starty + i * 100, start + 100 * (j + 1), starty + 100 * (i + 1));
        }
    }
    return board;
}

static int getValTop(int t) {
    switch (t) {
    case(ROOK):
        return 5;
    case(KNIGHT):
        return 3;
    case(BISHOP):
        return 3;
    case(QUEEN):
        return 9;
    case(KING):
        return MAX_INT;
    default:
        return -1;
    }
}

//necessary definitions
static std::pair<int, int> basePieceLayout[32] = { {1, ROOK}, {1, KNIGHT}, {1,BISHOP}, {1,QUEEN}, {1,KING}, {1,BISHOP}, {1, KNIGHT}, {1, ROOK}, {1,PAWN}, {1,PAWN}, {1,PAWN}, {1,PAWN}, {1,PAWN}, {1,PAWN}, {1,PAWN}, {1,PAWN},
                           {0,PAWN}, {0,PAWN}, {0,PAWN}, {0,PAWN}, {0,PAWN}, {0,PAWN}, {0,PAWN}, {0,PAWN}, {0, ROOK}, {0, KNIGHT}, {0,BISHOP}, {0,QUEEN}, {0,KING}, {0,BISHOP}, {0, KNIGHT}, {0, ROOK} };
static D2D1_POINT_2F basePieceBoardCoords[32] = { {0,0}, {0,1}, {0,2}, {0,3}, {0,4}, {0,5}, {0,6}, {0,7}, {1,0}, {1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7},
                                           {6,0}, {6,1}, {6,2}, {6,3}, {6,4}, {6,5}, {6,6}, {6,7}, {7,0}, {7,1}, {7,2}, {7,3}, {7,4}, {7,5}, {7,6}, {7,7} };
static const char* piecePNGNames[32] = { "../Test/srcIMG/BL_Rook.png", "../Test/srcIMG/BL_Knight.png", "../Test/srcIMG/BL_Bishop.png", "../Test/srcIMG/BL_Queen.png",
                                 "../Test/srcIMG/BL_King.png", "../Test/srcIMG/BL_Bishop.png", "../Test/srcIMG/BL_Knight.png", "../Test/srcIMG/BL_Rook.png",
                                 "../Test/srcIMG/BL_Pawn.png", "../Test/srcIMG/BL_Pawn.png", "../Test/srcIMG/BL_Pawn.png", "../Test/srcIMG/BL_Pawn.png",
                                 "../Test/srcIMG/BL_Pawn.png", "../Test/srcIMG/BL_Pawn.png", "../Test/srcIMG/BL_Pawn.png", "../Test/srcIMG/BL_Pawn.png",
                                 "../Test/srcIMG/W_Pawn.png", "../Test/srcIMG/W_Pawn.png", "../Test/srcIMG/W_Pawn.png", "../Test/srcIMG/W_Pawn.png",
                                 "../Test/srcIMG/W_Pawn.png", "../Test/srcIMG/W_Pawn.png", "../Test/srcIMG/W_Pawn.png", "../Test/srcIMG/W_Pawn.png",
                                 "../Test/srcIMG/W_Rook.png", "../Test/srcIMG/W_Knight.png", "../Test/srcIMG/W_Bishop.png", "../Test/srcIMG/W_Queen.png",
                                 "../Test/srcIMG/W_King.png", "../Test/srcIMG/W_Bishop.png", "../Test/srcIMG/W_Knight.png", "../Test/srcIMG/W_Rook.png" };
static int piecePNGLength[32] = { 27, 29, 29, 28, 27, 29, 29, 27, 27, 27, 27, 27, 27, 27, 27, 27, 26, 26, 26, 26, 26, 26, 26, 26, 26, 28, 28, 27, 26, 28, 28, 26 };
