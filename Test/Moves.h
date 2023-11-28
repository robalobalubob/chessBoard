#pragma once
#include "DefaultInclude.h"
#include "ChessBoard.h"
class moves
{
public:
	moves() {};
	moves(int type);
	static void GetPawnMoves(Piece* piece, ID2D1HwndRenderTarget* pRenderTarget, ChessBoard& board);
	//void GetPawnMoves(Piece* piece, ID2D1HwndRenderTarget* pRenderTarget, ChessBoard& board);
	vector<D2D1_RECT_F> getPotMoves(vector<Piece*>& idxPieces, Piece* piece, ID2D1HwndRenderTarget* pRenderTarget, ChessBoard &board);

	//static ULONGLONG GetWhiteMoves(ULONGLONG white, ULONGLONG black, ULONGLONG cur_moves, ULONGLONG pos);

	static ULONGLONG convCoordstoMask(std::pair<int, int> coords);

	static std::pair<int, int> convMasktoCoords(ULONGLONG mask);

	static ULONGLONG GetWhiteMoves(ULONGLONG white, ULONGLONG black, ULONGLONG cur_moves, ULONGLONG pos);

	static ULONGLONG getMovesPawn(const std::pair<int, int>& piecetype, ULONGLONG white, ULONGLONG black, ULONGLONG cur_moves, ULONGLONG pos);

	static ULONGLONG GetRookMoves(const std::pair<int, int>& piecetype, const std::pair<int, int>& coords, ULONGLONG white, ULONGLONG black,ULONGLONG cur_moves);

	static ULONGLONG GetBishopMoves(const std::pair<int, int>& piecetype, const std::pair<int, int>& coords, ULONGLONG white, ULONGLONG black);

	static ULONGLONG GetKnightMoves(const std::pair<int, int>& piecetype, const std::pair<int, int>& coords, ULONGLONG white, ULONGLONG black, ULONGLONG cur_moves, ULONGLONG pos);

	ulong testFunc(D2D1_POINT_2F coords, pair<int, int>  piecetype, ulong white, ulong black);
private:
	typedef std::map<int, std::vector<D2D1_POINT_2F>> moves_list;
	vector<D2D1_RECT_F> potMoves;
};

