#pragma once

#include "DefaultInclude.h"

using std::vector;
using std::string;

class Piece
{
public:
	Piece();
	Piece(std::pair<int,int> type, D2D1_POINT_2F coords, int val);
	Piece(Piece &cpy);
	D2D1_POINT_2F getCoords();
	std::pair<int, int> getType();
	int getVal();
	void updateType(std::pair<int, int> newtype);
	void updateVal(int newval);
	void updateCoords(D2D1_POINT_2F newcoords);
	HRESULT setImage(const char* fname, int length, ID2D1HwndRenderTarget** rendTar, float boardsize);
	IWICBitmap* getPieceBitmap();
	bool init_graphics(HRESULT hr);
	HRESULT drawPiece(ID2D1HwndRenderTarget** rendTar);
	HRESULT movePiece(D2D1_POINT_2F newcoords);
	float boardSize_;
	float pieceSize_;
	int idx_;
private:
	D2D1_POINT_2F coords_;
	D2D1_POINT_2F boardCoords_;
	std::pair<int,int> type_;
	int val_;
	IWICBitmap *pieceImage_;
	bool init_graphics_;
	IWICImagingFactory* test_;
	IWICBitmapDecoder* pDecoder_;
	IWICBitmapFrameDecode* pSource_;
	IWICStream* pStream_;
	IWICFormatConverter* pConverter_;
	IWICBitmapScaler* pScaler_;
	ID2D1Bitmap* pieceBitmap;
};

