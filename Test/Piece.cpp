#include "Piece.h"

//default constructor
//Should be unused
Piece::Piece() {}


//Constructor based on type, coords and value of piece
Piece::Piece(std::pair<int,int> type, D2D1_POINT_2F coords, int val) {
	type_ = type;
	coords_ = coords;
	val_ = val;
}

//Copy constructor
Piece::Piece(Piece& cpy) {
	type_ = cpy.getType();
	coords_ = cpy.getCoords();
	val_ = cpy.getVal();
}

//Return coords_
D2D1_POINT_2F Piece::getCoords() {
	return coords_;
}


//Return type_
std::pair<int, int> Piece::getType() {
	return type_;
}


//Return val_
int Piece::getVal() {
	return val_;
}


//Updates type to newtype
void Piece::updateType(std::pair<int, int> newtype) {
	type_ = newtype;
}

//Updates val_ to newval
void Piece::updateVal(int newval) {
	val_ = newval;
}

//Upadte coords_ to newcoords
void Piece::updateCoords(D2D1_POINT_2F newcoords) {
	coords_ = newcoords;
}

//set the image for the piece
HRESULT Piece::setImage(const char* fname, int length, ID2D1HwndRenderTarget** rendTar, float boardsize) {
	wchar_t* wtext = new wchar_t[length];
	mbstate_t* idkwtd = NULL;
	int check = mbsrtowcs(wtext, &fname, length, idkwtd);
	LPCWSTR ptr = wtext;
	HRESULT hr;
	if (test_ == NULL) {
		OutputDebugStringA("ImagingFactory failed to initialize\n");
		return false;
	}
	if (init_graphics_) {
		hr = test_->CreateDecoderFromFilename(
			ptr,
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder_
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder_->GetFrame(0, &pSource_);
	}
	if (SUCCEEDED(hr))
	{

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = test_->CreateFormatConverter(&pConverter_);

	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter_->Initialize(
			pSource_,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	if (SUCCEEDED(hr))
	{

		// Create a Direct2D bitmap from the WIC bitmap.
		hr = (*rendTar)->CreateBitmapFromWicBitmap(
			pConverter_,
			NULL,
			&pieceBitmap
		);
		boardSize_ = boardsize;
	}
	return hr;
}

//return pieceImage_
IWICBitmap* Piece::getPieceBitmap() {
	return pieceImage_;
}

//initialize the graphics
bool Piece::init_graphics(HRESULT hr) {
	test_ = NULL;
	if (SUCCEEDED(hr)) {
		hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&test_));
	}
	init_graphics_ = SUCCEEDED(hr);
	return init_graphics_;
}


//draw piece to window over board
HRESULT Piece::drawPiece(ID2D1HwndRenderTarget** rendTar) {
	if (pieceBitmap == NULL) {
		OutputDebugStringA("Bitmap failed to initialize\n");
		return 0;
	}
	D2D1_SIZE_F bsize = pieceBitmap->GetSize();
	float scalar = (boardSize_ / 8) / bsize.width;
	scalar = 1;
	//D2D1_POINT_2F centCoords = { coords_.x + bsize.width / 2, coords_.y + bsize.width / 2 };
	//(*rendTar)->SetTransform(D2D1::Matrix3x2F::Scale(D2D1::Size(scalar, scalar), centCoords));
	(*rendTar)->DrawBitmap(pieceBitmap, D2D1::RectF(coords_.x,
													coords_.y,
													coords_.x + (boardSize_ / 8),
													coords_.y + (boardSize_ / 8)
												   )
						   );
	(*rendTar)->SetTransform(D2D1::Matrix3x2F::Identity());
	return HRESULT(1);
}

//Change coords of piece
HRESULT Piece::movePiece(D2D1_POINT_2F newcoords) {
	coords_ = newcoords;
	return 1;
}
