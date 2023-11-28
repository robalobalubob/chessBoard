#pragma once

#include "Piece.h"

class ChessBoard
{
public:
	ChessBoard();
	~ChessBoard();
	D2D1_POINT_2F getBoardCoords() { return boardCoords_; }
	HRESULT movePiece(int idx, D2D1_POINT_2F new_coords);
	HRESULT addPiece(Piece newpiece);
	HRESULT removePiece(D2D1_POINT_2F coordsOfPiece);
	HRESULT setBoardPNG(const char* fname, int length, ID2D1HwndRenderTarget** rendTar);
	HRESULT drawBoardPNG(ID2D1HwndRenderTarget** rendTar);
	HRESULT initBoard(ID2D1HwndRenderTarget** rendTar, D2D1_SIZE_F size);
	vector<Piece*> getPieces();
	Piece* findPiece(D2D1_POINT_2F coordsOfPiece);
	float boardSize_;
	bool is_selected_;
	Piece* selected_;
	bool turn_;
private:
	vector<Piece*> curPieces_;
	int valWhite_;
	int valBlack_;
	IWICBitmap* boardImage_;
	D2D1_POINT_2F boardCoords_;
	bool init_graphics_;
	bool init_board_;
	IWICImagingFactory* test_;
	IWICBitmapDecoder* pDecoder_;
	IWICBitmapFrameDecode* pSource_;
	IWICStream* pStream_;
	IWICFormatConverter* pConverter_;
	IWICBitmapScaler* pScaler_;
	ID2D1Bitmap* pieceBitmap;
};


