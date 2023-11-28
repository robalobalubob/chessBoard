//
// Created by Jermiah Burtlow on 10/17/23.
//

#include "DefaultInclude.h"

#ifndef UNTITLED_MOVELIST_H
#define UNTITLED_MOVELIST_H

#define COL1 0x0101010101010101
#define COL2 0x0202020202020202
#define COL3 0x0404040404040404
#define COL4 0x0808080808080808
#define COL5 0x1010101010101010
#define COL6 0x2020202020202020
#define COL7 0x4040404040404040
#define COL8 0x8080808080808080
#define ROW1 0x00000000000000FF
#define ROW2 0x000000000000FF00
#define ROW3 0x0000000000FF0000
#define ROW4 0x00000000FF000000
#define ROW5 0x000000FF00000000
#define ROW6 0x0000FF0000000000
#define ROW7 0x00FF000000000000
#define ROW8 0xFF00000000000000
typedef uint64_t ulong;

class MoveList {
public:
    MoveList()= default;
    static ulong get_moves(std::pair<int,int> piecetype, std::pair<int,int> coords, ulong white, ulong black, ulong& t){
        ulong rows[8] = {ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8};
        ulong col[8] = {COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8};
        ulong cur_moves = 0;
        ulong pos = coords.first * 8 + coords.second;
        pos = (ulong)1 << pos;
        t = pos;
        if(piecetype.second == 0){
            cur_moves = getMovesPawn(piecetype, white, black, cur_moves, pos);
        }
        if(piecetype.second == 1){
            cur_moves = GetRookMoves(piecetype, coords, white, black, cur_moves);
            //cur_moves -= cur_moves&black;
        }
        return cur_moves;
    }


    static ulong
    GetRookMoves(const std::pair<int, int> &piecetype, const std::pair<int, int> &coords, ulong white, ulong black,
                 ulong cur_moves) {
        ulong rows[8] = {ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8};
        ulong col[8] = {COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8};
        ulong enem = piecetype.first ? white : black;
        ulong ally = piecetype.first ? black : white;
        int x = coords.first;//row of the rook
        int y = coords.second;//col of the rook
        bool aval = true;
        //cur_moves = cur_moves | rows[x] | col[y];
        for(int i = y-1; i >=0; i--){
            if((rows[x] & col[i]) & (enem | ally))
            {
                if((rows[x] & col[i]) & enem){
                    cur_moves = cur_moves | (rows[x] & col[i]);
                }
                break;
            }else{
                cur_moves = cur_moves | (rows[x] & col[i]);
            }
        }
        for(int i = y+1; i <= 7; i++){
            if((rows[x] & col[i]) & (enem | ally))
            {
                if((rows[x] & col[i]) & enem){
                    cur_moves = cur_moves | (rows[x] & col[i]);
                }
                break;
            }else{
                cur_moves = cur_moves | (rows[x] & col[i]);
            }
        }
        for(int i = x+1; i <= 7; i++){
            if((rows[i] & col[y]) & (enem | ally))
            {
                if((rows[i] & col[y]) & enem){
                    cur_moves = cur_moves | (rows[i] & col[y]);
                }
                break;
            }else{
                cur_moves = cur_moves | (rows[i] & col[y]);
            }
        }
        for(int i = x-1; i >= 0; i--){
            if((rows[i] & col[y]) & (enem | ally))
            {
                if((rows[i] & col[y]) & enem){
                    cur_moves = cur_moves | (rows[i] & col[y]);
                }
                break;
            }else{
                cur_moves = cur_moves | (rows[i] & col[y]);
            }
        }
        return cur_moves;
    }


    static ulong getMovesPawn(const std::pair<int, int> &piecetype, ulong white, ulong black, ulong cur_moves, ulong pos) {
        if(piecetype.first) {
            if (pos >> 8 < 256 && (!(pos << 16 & (white | black))) && (!(pos << 8 & (white | black)))) {
                cur_moves += pos << 16;
            }
            if (!(pos << 8 & (white | black))) {
                cur_moves += pos << 8;
            }
            if (!(pos & COL1) && (pos << 7 & white)) {
                cur_moves += pos << 7;
            }
            if (!(pos & COL8) && (pos << 9 & white)) {
                cur_moves += pos << 9;
            }
            //cur_moves = cur_moves << 8;
        }else{
            cur_moves = GetWhiteMoves(white, black, cur_moves, pos);
        }
        return cur_moves;
    }


    static ulong GetWhiteMoves(ulong white, ulong black, ulong cur_moves, ulong pos) {
        if (pos >> 48 < 256 && (!(pos >> 16 & (white | black))) && (!(pos >> 8 & (white | black)))) {
            cur_moves += pos >> 16;
        }
        if (!(pos >> 8 & (white | black))) {
            cur_moves += pos >> 8;
        }
        if (!(pos & COL1) && (pos >> 7 & black)) {
            cur_moves += pos >>7;
        }
        if (!(pos & COL8) && (pos >> 9 & black)) {
            cur_moves += pos >> 9;
        }
        return cur_moves;
    }


    static ulong convCoordstoMask(std::pair<int,int> coords){
        int tmp = coords.first * 8 + coords.second;
        ulong ret = (ulong)1 << tmp;
        return ret;
    }
    static std::pair<int,int> convMasktoCoords(ulong mask){
        std::pair<int,int> ret;
        ulong rows[8] = {ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8};
        ulong col[8] = {COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8};
        for( int i = 0; i < 8; i++){
            if(rows[i] & mask){
                ret.first = i;
            }
            if(col[i] & mask){
                ret.second = i;
            }
        }
        return ret;
    }
private:
};




#endif //UNTITLED_MOVELIST_H

