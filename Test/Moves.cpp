#include "Moves.h"
/*
void moves::GetPawnMoves(Piece* piece, ID2D1HwndRenderTarget* pRenderTarget, ChessBoard& board)
{
	vector<Piece*>& idxPieces;
	vector<D2D1_RECT_F> ret;
	float bsize;
	float psize;
	if (piece->getType().first == 0) {
		D2D1_POINT_2F pCoords = piece->getCoords();
		outputnum(0,0,pCoords);
		D2D1_POINT_2F temp = convPixeltoCoord({ pCoords.x, pCoords.y}, board.getBoardCoords(), board.boardSize_);
		outputnum(0, 0, temp);
		temp.x -= 1;
		D2D1_POINT_2F newCoords = convCoordtoPixel(temp, pRenderTarget->GetSize(), bsize);
		Piece* tpiece = board.findPiece(newCoords);
		if (temp.x >= 0) {
			outputnum(0, 0, newCoords);
			if (tpiece == NULL) {
				ret.push_back(D2D1::RectF(newCoords.x, newCoords.y, newCoords.x + psize, newCoords.y + psize));
			}
			else {
				temp.x = 0;
			}
		}
		if (temp.x == 5) {
			temp = convPixeltoCoord({ pCoords.x , pCoords.y }, board.getBoardCoords(), board.boardSize_);
			temp.x -= 2;
			newCoords = convCoordtoPixel(temp, pRenderTarget->GetSize(), bsize);
			tpiece = board.findPiece(newCoords);
			if (tpiece == NULL) {
				ret.push_back(D2D1::RectF(newCoords.x, newCoords.y, newCoords.x + psize, newCoords.y + psize));
			}
		}
		temp = convPixeltoCoord({ pCoords.x, pCoords.y }, board.getBoardCoords(), board.boardSize_);
		newCoords = convCoordtoPixel({ temp.x - 1, temp.y - 1 }, pRenderTarget->GetSize(), board.boardSize_);
		tpiece = board.findPiece(newCoords);
		if (tpiece != NULL) {
			if (tpiece->getType().first) {
				ret.push_back(D2D1::RectF(newCoords.x, newCoords.y, newCoords.x + psize, newCoords.y + psize));
				idxPieces.push_back(tpiece);
			}
		}
		temp = convPixeltoCoord({ pCoords.x, pCoords.y }, board.getBoardCoords(), board.boardSize_);
		newCoords = convCoordtoPixel({ temp.x - 1, temp.y + 1 }, pRenderTarget->GetSize(), board.boardSize_);
		tpiece = board.findPiece(newCoords);
		if (tpiece != NULL) {
			if (tpiece->getType().first) {
				ret.push_back(D2D1::RectF(newCoords.x, newCoords.y, newCoords.x + psize, newCoords.y + psize));
				idxPieces.push_back(tpiece);
			}
		}


		temp = convPixeltoCoord({ pCoords.x, pCoords.y }, board.getBoardCoords(), board.boardSize_);
		newCoords = convCoordtoPixel({ temp.x, temp.y + 1 }, pRenderTarget->GetSize(), board.boardSize_);
		tpiece = board.findPiece(newCoords);
		D2D1_POINT_2F newCoords2 = convCoordtoPixel({ temp.x, temp.y - 1 }, pRenderTarget->GetSize(), board.boardSize_);
		Piece* tpiece2 = board.findPiece(newCoords2);
		if (temp.x == 3) {
			if (tpiece != NULL) {
				if (tpiece->getType().second == PAWN && tpiece->getType().first) {
					newCoords = convCoordtoPixel({ temp.x - 1, temp.y + 1 }, pRenderTarget->GetSize(), board.boardSize_);
					if (board.findPiece(newCoords) == NULL) {
						ret.push_back(D2D1::RectF(newCoords.x, newCoords.y, newCoords.x + psize, newCoords.y + psize));
					}
				}
			}
			if (tpiece2 != NULL) {
				if (tpiece2->getType().second == PAWN && tpiece2->getType().first) {
					newCoords2 = convCoordtoPixel({ temp.x - 1, temp.y - 1 }, pRenderTarget->GetSize(), board.boardSize_);
					if (board.findPiece(newCoords2) == NULL) {
						ret.push_back(D2D1::RectF(newCoords2.x, newCoords2.y, newCoords2.x + psize, newCoords2.y + psize));
					}
				}
			}
		}
	}
	else {
		D2D1_POINT_2F pCoords = piece->getCoords();
		outputnum(0, 0, pCoords);
		D2D1_POINT_2F temp = convPixeltoCoord({ pCoords.x, pCoords.y }, board.getBoardCoords(), board.boardSize_);
		outputnum(0, 0, temp);
		temp.x += 1;
		D2D1_POINT_2F newCoords = convCoordtoPixel(temp, pRenderTarget->GetSize(), bsize);
		Piece* tpiece = board.findPiece(newCoords);
		if (temp.x <= 7) {
			outputnum(0, 0, newCoords);
			if(tpiece == NULL) {
				ret.push_back(D2D1::RectF(newCoords.x, newCoords.y, newCoords.x + psize, newCoords.y + psize));
			}
			else {
				temp.x = 0;
			}
			//ret.push_back(D2D1::RectF(newCoords.x, newCoords.y, newCoords.x + psize, newCoords.y + psize));
		}
		if (temp.x == 2) {
			temp = convPixeltoCoord({ pCoords.x , pCoords.y }, board.getBoardCoords(), board.boardSize_);
			temp.x += 2;
			newCoords = convCoordtoPixel(temp, pRenderTarget->GetSize(), bsize);
			tpiece = board.findPiece(newCoords);
			if (tpiece == NULL) {
				ret.push_back(D2D1::RectF(newCoords.x, newCoords.y, newCoords.x + psize, newCoords.y + psize));
			}
		}
		temp = convPixeltoCoord({ pCoords.x, pCoords.y }, board.getBoardCoords(), board.boardSize_);
		newCoords = convCoordtoPixel({ temp.x + 1, temp.y + 1 }, pRenderTarget->GetSize(), board.boardSize_);
		tpiece = board.findPiece(newCoords);
		if (tpiece != NULL) {
			if (tpiece->getType().first == 0) {
				ret.push_back(D2D1::RectF(newCoords.x, newCoords.y, newCoords.x + psize, newCoords.y + psize));
				idxPieces.push_back(tpiece);
			}
		}
		temp = convPixeltoCoord({ pCoords.x, pCoords.y }, board.getBoardCoords(), board.boardSize_);
		newCoords = convCoordtoPixel({ temp.x + 1, temp.y - 1 }, pRenderTarget->GetSize(), board.boardSize_);
		tpiece = board.findPiece(newCoords);
		if (tpiece != NULL) {
			if (tpiece->getType().first == 0) {
				ret.push_back(D2D1::RectF(newCoords.x, newCoords.y, newCoords.x + psize, newCoords.y + psize));
				idxPieces.push_back(tpiece);
			}
		}

		temp = convPixeltoCoord({ pCoords.x, pCoords.y }, board.getBoardCoords(), board.boardSize_);
		newCoords = convCoordtoPixel({ temp.x, temp.y + 1 }, pRenderTarget->GetSize(), board.boardSize_);
		tpiece = board.findPiece(newCoords);
		D2D1_POINT_2F newCoords2 = convCoordtoPixel({ temp.x, temp.y - 1 }, pRenderTarget->GetSize(), board.boardSize_);
		Piece* tpiece2 = board.findPiece(newCoords2);
		if (temp.x == 4) {
			if (tpiece != NULL) {
				if (tpiece->getType().second == PAWN && tpiece->getType().first == 0) {
					newCoords = convCoordtoPixel({ temp.x + 1, temp.y + 1 }, pRenderTarget->GetSize(), board.boardSize_);
					if (board.findPiece(newCoords) == NULL) {
						ret.push_back(D2D1::RectF(newCoords.x, newCoords.y, newCoords.x + psize, newCoords.y + psize));
					}
				}
			}
			if (tpiece2 != NULL) {
				if (tpiece2->getType().second == PAWN && tpiece2->getType().first == 0) {
					newCoords2 = convCoordtoPixel({ temp.x + 1, temp.y - 1 }, pRenderTarget->GetSize(), board.boardSize_);
					if (board.findPiece(newCoords2) == NULL) {
						ret.push_back(D2D1::RectF(newCoords2.x, newCoords2.y, newCoords2.x + psize, newCoords2.y + psize));
					}
				}
			}
		}
	}
}
*/

vector<D2D1_RECT_F> moves::getPotMoves(vector<Piece*>& idxPieces, Piece* piece, ID2D1HwndRenderTarget* pRenderTarget, ChessBoard& board) {
	vector<D2D1_RECT_F> ret;
	/*float bsize = board.boardSize_;
	float psize = bsize / 8;
	switch (piece->getType().second) {
		case PAWN:
			GetPawnMoves(piece, pRenderTarget, board);
			break;
		case ROOK:
			break;
		case BISHOP:
			break;
		case KNIGHT:
			break;
		case QUEEN:
			break;
		case KING:
			break;
		default:
			break;
	}
	return ret;*/
	return ret;
}

ULONGLONG moves::testFunc(D2D1_POINT_2F coords, pair<int,int>  piecetype, ULONGLONG white, ULONGLONG black) {
    ULONGLONG rows[8] = { ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8 };
    ULONGLONG col[8] = { COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8 };
    ULONGLONG cur_moves = 0;
    std::pair<int, int> coords_ = { coords.x, coords.y };
    ULONGLONG pos = coords_.first * 8 + coords_.second;
    ULONGLONG enem = piecetype.first ? white : black;
    ULONGLONG ally = piecetype.first ? black : white;
    pos = (ULONGLONG)1 << pos;
    //t = pos;
    if (piecetype.second == PAWN) {//if piece is a pawn
        cur_moves = getMovesPawn(piecetype, white, black, cur_moves, pos);
    }
    else if (piecetype.second == ROOK) {//if its a rook
        cur_moves = GetRookMoves(piecetype, coords_, white, black, cur_moves);
        //cur_moves -= cur_moves&black;
    }
    else if (piecetype.second == BISHOP) {//if its a bishop
        cur_moves = GetBishopMoves(piecetype, coords_, white, black);
    }
    else if (piecetype.second == KNIGHT) {//if its a knight
        cur_moves = GetKnightMoves(piecetype, coords_, white, black, cur_moves, pos);
    }
    else if (piecetype.second == QUEEN) {//if its a queen
        cur_moves = GetBishopMoves(piecetype, coords_, white, black);
        cur_moves = GetRookMoves(piecetype, coords_, white, black, cur_moves);
    }
    else {
        if (coords_.second == 0) {
            cur_moves = cur_moves | ((pos << 8) & (~ally));//below
            cur_moves = cur_moves | ((pos >> 8) & (~ally));//above
            cur_moves = cur_moves | ((pos << 9) & (~ally));//down right
            cur_moves = cur_moves | ((pos >> 7) & (~ally));//up right
            cur_moves = cur_moves | ((pos << 1) & (~ally));//right
        }
        else if (coords_.second == 7) {
            cur_moves = cur_moves | ((pos << 8) & (~ally));//below
            cur_moves = cur_moves | ((pos >> 8) & (~ally));//above
            cur_moves = cur_moves | ((pos << 7) & (~ally));//down left
            cur_moves = cur_moves | ((pos >> 9) & (~ally));//up left
            cur_moves = cur_moves | ((pos >> 1) & (~ally));//left
        }
        else {
            cur_moves = cur_moves | ((pos << 8) & (~ally));//below
            cur_moves = cur_moves | ((pos >> 8) & (~ally));//above
            cur_moves = cur_moves | ((pos << 9) & (~ally));//down right
            cur_moves = cur_moves | ((pos >> 7) & (~ally));//up right
            cur_moves = cur_moves | ((pos << 1) & (~ally));//right
            cur_moves = cur_moves | ((pos << 7) & (~ally));//down left
            cur_moves = cur_moves | ((pos >> 9) & (~ally));//up left
            cur_moves = cur_moves | ((pos >> 1) & (~ally));//left
        }
    }
    return cur_moves;
}


ULONGLONG moves::GetKnightMoves(const std::pair<int, int>& piecetype, const std::pair<int, int>& coords, ULONGLONG white, ULONGLONG black,
    ULONGLONG cur_moves, ULONGLONG pos) {
    ULONGLONG enem = piecetype.first ? white : black;
    ULONGLONG ally = piecetype.first ? black : white;
    if (coords.second + 2 < 8 && coords.second - 2 >= 0) {
        //below right then left
        cur_moves = cur_moves | ((ally & pos << 17) ? 0 : pos << 17);
        cur_moves = cur_moves | ((ally & pos << 15) ? 0 : pos << 15);
        //above left then right
        cur_moves = cur_moves | ((ally & pos >> 17) ? 0 : pos >> 17);
        cur_moves = cur_moves | ((ally & pos >> 15) ? 0 : pos >> 15);
        //right down then up
        cur_moves = cur_moves | ((ally & pos << 10) ? 0 : pos << 10);
        cur_moves = cur_moves | ((ally & pos >> 6) ? 0 : pos >> 6);
        //left down then up
        cur_moves = cur_moves | ((ally & pos << 6) ? 0 : pos << 6);
        cur_moves = cur_moves | ((ally & pos >> 10) ? 0 : pos >> 10);
    }
    else if (coords.second == 0) {
        //below right
        cur_moves = cur_moves | ((ally & pos << 17) ? 0 : pos << 17);
        //above right
        cur_moves = cur_moves | ((ally & pos >> 15) ? 0 : pos >> 15);
        //right down then up
        cur_moves = cur_moves | ((ally & pos << 10) ? 0 : pos << 10);
        cur_moves = cur_moves | ((ally & pos >> 6) ? 0 : pos >> 6);
    }
    else if (coords.second == 7) {
        //below left
        cur_moves = cur_moves | ((ally & pos << 15) ? 0 : pos << 15);
        //above left
        cur_moves = cur_moves | ((ally & pos >> 17) ? 0 : pos >> 17);
        //left down then up
        cur_moves = cur_moves | ((ally & pos << 6) ? 0 : pos << 6);
        cur_moves = cur_moves | ((ally & pos >> 10) ? 0 : pos >> 10);
    }
    else if (coords.second < 2) {
        //below right then left
        cur_moves = cur_moves | ((ally & pos << 17) ? 0 : pos << 17);
        cur_moves = cur_moves | ((ally & pos << 15) ? 0 : pos << 15);
        //above left then right
        cur_moves = cur_moves | ((ally & pos >> 17) ? 0 : pos >> 17);
        cur_moves = cur_moves | ((ally & pos >> 15) ? 0 : pos >> 15);
        //right down then up
        cur_moves = cur_moves | ((ally & pos << 10) ? 0 : pos << 10);
        cur_moves = cur_moves | ((ally & pos >> 6) ? 0 : pos >> 6);
    }
    else if (coords.second > 5) {
        //below right then left
        cur_moves = cur_moves | ((ally & pos << 17) ? 0 : pos << 17);
        cur_moves = cur_moves | ((ally & pos << 15) ? 0 : pos << 15);
        //above left then right
        cur_moves = cur_moves | ((ally & pos >> 17) ? 0 : pos >> 17);
        cur_moves = cur_moves | ((ally & pos >> 15) ? 0 : pos >> 15);
        //left down then up
        cur_moves = cur_moves | ((ally & pos << 6) ? 0 : pos << 6);
        cur_moves = cur_moves | ((ally & pos >> 10) ? 0 : pos >> 10);
    }
    return cur_moves;
}


ULONGLONG moves::GetBishopMoves(const std::pair<int, int>& piecetype, const std::pair<int, int>& coords, ULONGLONG white, ULONGLONG black) {
    int x = coords.first;
    int y = coords.second;
    ULONGLONG enem = piecetype.first ? white : black;
    ULONGLONG ally = piecetype.first ? black : white;
    int tmpx = x - 1;
    int tmpy = y - 1;
    ULONGLONG rows[8] = { ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8 };
    ULONGLONG col[8] = { COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8 };
    ULONGLONG cur_moves = 0;
    while (tmpx >= 0 && tmpy >= 0) {
        if ((rows[tmpx] & col[tmpy]) & enem) {
            cur_moves = cur_moves | (rows[tmpx] & col[tmpy]);
            break;
        }
        else if ((rows[tmpx] & col[tmpy]) & ally) {
            break;
        }
        cur_moves = cur_moves | (rows[tmpx] & col[tmpy]);
        tmpx--;
        tmpy--;
    }
    tmpx = x - 1;
    tmpy = y + 1;
    while (tmpx >= 0 && tmpy < 8) {
        if ((rows[tmpx] & col[tmpy]) & enem) {
            cur_moves = cur_moves | (rows[tmpx] & col[tmpy]);
            break;
        }
        else if ((rows[tmpx] & col[tmpy]) & ally) {
            break;
        }
        cur_moves = cur_moves | (rows[tmpx] & col[tmpy]);
        tmpx--;
        tmpy++;
    }
    tmpx = x + 1;
    tmpy = y + 1;
    while (tmpx < 8 && tmpy < 8) {
        if ((rows[tmpx] & col[tmpy]) & enem) {
            cur_moves = cur_moves | (rows[tmpx] & col[tmpy]);
            break;
        }
        else if ((rows[tmpx] & col[tmpy]) & ally) {
            break;
        }
        cur_moves = cur_moves | (rows[tmpx] & col[tmpy]);
        tmpx++;
        tmpy++;
    }
    tmpx = x + 1;
    tmpy = y - 1;
    while (tmpx < 8 && tmpy >= 0) {
        if ((rows[tmpx] & col[tmpy]) & enem) {
            cur_moves = cur_moves | (rows[tmpx] & col[tmpy]);
            break;
        }
        else if ((rows[tmpx] & col[tmpy]) & ally) {
            break;
        }
        cur_moves = cur_moves | (rows[tmpx] & col[tmpy]);
        tmpx++;
        tmpy--;
    }
    return cur_moves;
}


ULONGLONG moves::GetRookMoves(const std::pair<int, int>& piecetype, const std::pair<int, int>& coords, ULONGLONG white, ULONGLONG black,
    ULONGLONG cur_moves) {
    ULONGLONG rows[8] = { ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8 };
    ULONGLONG col[8] = { COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8 };
    ULONGLONG enem = piecetype.first ? white : black;
    ULONGLONG ally = piecetype.first ? black : white;
    int x = coords.first;//row of the rook
    int y = coords.second;//col of the rook
    bool aval = true;
    //cur_moves = cur_moves | rows[x] | col[y];
    for (int i = y - 1; i >= 0; i--) {
        if ((rows[x] & col[i]) & (enem | ally))
        {
            if ((rows[x] & col[i]) & enem) {
                cur_moves = cur_moves | (rows[x] & col[i]);
            }
            break;
        }
        else {
            cur_moves = cur_moves | (rows[x] & col[i]);
        }
    }
    for (int i = y + 1; i <= 7; i++) {
        if ((rows[x] & col[i]) & (enem | ally))
        {
            if ((rows[x] & col[i]) & enem) {
                cur_moves = cur_moves | (rows[x] & col[i]);
            }
            break;
        }
        else {
            cur_moves = cur_moves | (rows[x] & col[i]);
        }
    }
    for (int i = x + 1; i <= 7; i++) {
        if ((rows[i] & col[y]) & (enem | ally))
        {
            if ((rows[i] & col[y]) & enem) {
                cur_moves = cur_moves | (rows[i] & col[y]);
            }
            break;
        }
        else {
            cur_moves = cur_moves | (rows[i] & col[y]);
        }
    }
    for (int i = x - 1; i >= 0; i--) {
        if ((rows[i] & col[y]) & (enem | ally))
        {
            if ((rows[i] & col[y]) & enem) {
                cur_moves = cur_moves | (rows[i] & col[y]);
            }
            break;
        }
        else {
            cur_moves = cur_moves | (rows[i] & col[y]);
        }
    }
    return cur_moves;
}


ULONGLONG moves::getMovesPawn(const std::pair<int, int>& piecetype, ULONGLONG white, ULONGLONG black, ULONGLONG cur_moves, ULONGLONG pos) {
    if (piecetype.first) {
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
    }
    else {
        cur_moves = GetWhiteMoves(white, black, cur_moves, pos);
    }
    return cur_moves;
}


ULONGLONG moves::GetWhiteMoves(ULONGLONG white, ULONGLONG black, ULONGLONG cur_moves, ULONGLONG pos) {
    if (pos >> 48 < 256 && (!(pos >> 16 & (white | black))) && (!(pos >> 8 & (white | black)))) {
        cur_moves += pos >> 16;
    }
    if (!(pos >> 8 & (white | black))) {
        cur_moves += pos >> 8;
    }
    if (!(pos & COL1) && (pos >> 7 & black)) {
        cur_moves += pos >> 7;
    }
    if (!(pos & COL8) && (pos >> 9 & black)) {
        cur_moves += pos >> 9;
    }
    return cur_moves;
}


ULONGLONG moves::convCoordstoMask(std::pair<int, int> coords) {
    int tmp = coords.first * 8 + coords.second;
    ULONGLONG ret = (ULONGLONG)1 << tmp;
    return ret;
}
std::pair<int, int> moves::convMasktoCoords(ULONGLONG mask) {
    std::pair<int, int> ret;
    ULONGLONG rows[8] = { ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8 };
    ULONGLONG col[8] = { COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8 };
    for (int i = 0; i < 8; i++) {
        if (rows[i] & mask) {
            ret.first = i;
        }
        if (col[i] & mask) {
            ret.second = i;
        }
    }
    return ret;
}



