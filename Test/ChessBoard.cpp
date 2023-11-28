#include "ChessBoard.h"

ChessBoard::ChessBoard() {
	valWhite_ = NULL;
	valBlack_ = NULL;
	boardImage_ = NULL;
	boardCoords_ = { 0,0 };
	init_graphics_ = NULL;
	init_board_ = NULL;
	test_ = NULL;
	pDecoder_ = NULL;
	pSource_ = NULL;
	pStream_ = NULL;
	pConverter_ = NULL;
	pScaler_ = NULL;
	pieceBitmap = NULL;
	boardSize_ = 0;
	selected_ = NULL;
	is_selected_ = FALSE;
	turn_ = 0;
}

//Future delete for chessboard
//Unimplemented
ChessBoard::~ChessBoard() {

}

//Add a piece
//Unused -- Delete?
HRESULT ChessBoard::addPiece(Piece newpiece) {
	return 0;
}

//Remove Piece from board and piece vector based on coords of piece
HRESULT ChessBoard::removePiece(D2D1_POINT_2F coordsOfPiece) {
	//locate piece to be removed
	Piece* temp = findPiece(coordsOfPiece);
	//Ensure piece exists
	if (temp != NULL) {
		//Find piece in curPieces_
		auto it = std::find(curPieces_.begin(), curPieces_.end(), temp);
		//Adjust index for each piece
		for (auto it2 = it; it2 != curPieces_.end(); it2++) {
			(*it2)->idx_--;
		}
		//Delete the piece
		curPieces_.erase(it);
	}
	return 0;
}

//Set the PNG used for the board
HRESULT ChessBoard::setBoardPNG(const char* fname, int length, ID2D1HwndRenderTarget** rendTar) {
	wchar_t* wtext = new wchar_t[length];
	mbstate_t* idkwtd = NULL;
	int check = mbsrtowcs(wtext, &fname, length, idkwtd);
	LPCWSTR ptr = wtext;
	HRESULT* hr = new HRESULT;
	*hr = NULL;
	if (test_ == NULL) {
		OutputDebugStringA("ImagingFactory failed to initialize\n");
		return 0;
	}
	if (init_graphics_) {
		*hr = test_->CreateDecoderFromFilename(
			ptr,
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder_
		);
	}
	if (SUCCEEDED(*hr))
	{
		// Create the initial frame.
		*hr = pDecoder_->GetFrame(0, &pSource_);
	}
	if (SUCCEEDED(*hr))
	{

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		*hr = test_->CreateFormatConverter(&pConverter_);

	}
	if (SUCCEEDED(*hr))
	{
		*hr = pConverter_->Initialize(
			pSource_,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}
	if (SUCCEEDED(*hr))
	{

		// Create a Direct2D bitmap from the WIC bitmap.
		*hr = (*rendTar)->CreateBitmapFromWicBitmap(
			pConverter_,
			NULL,
			&pieceBitmap
		);
		boardSize_ = pieceBitmap->GetSize().width * .75;
	}
	return *hr;
}

//Draw the board PNG to window
HRESULT ChessBoard::drawBoardPNG(ID2D1HwndRenderTarget** rendTar) {
	if (pieceBitmap == NULL) {
		OutputDebugStringA("Bitmap failed to initialize\n");
		return 0;
	}
	D2D1_SIZE_F bsize = (*rendTar)->GetSize();
	float offset = boardSize_ / -2;
	boardCoords_ = { offset + bsize.width/2, offset + bsize.height / 2 };
	(*rendTar)->Clear(D2D1::ColorF(D2D1::ColorF::CornflowerBlue));
	(*rendTar)->DrawBitmap(pieceBitmap, D2D1::RectF(boardCoords_.x,
														boardCoords_.y,
														boardCoords_.x + boardSize_,
														boardCoords_.y + boardSize_
													));

	(*rendTar)->SetTransform(D2D1::Matrix3x2F::Identity());

	for (int i = 0; i < curPieces_.size(); i++) {

		curPieces_[i]->drawPiece(rendTar);
	}
	return HRESULT(1);
}

//Move piece on board
HRESULT ChessBoard::movePiece(int idx, D2D1_POINT_2F new_coords) {
	curPieces_[idx]->updateCoords(new_coords);
	return 1;
}

//initialize the board and pieces
HRESULT ChessBoard::initBoard(ID2D1HwndRenderTarget** rendTar, D2D1_SIZE_F size) {
	test_ = NULL;
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&test_));
	init_graphics_ = SUCCEEDED(hr);
	this->setBoardPNG("srcIMG/board.png", 17, rendTar);
	D2D1_SIZE_F nsize = (*rendTar)->GetSize();
	curPieces_.resize(32);
	for (int i = 0; i < 32; i++) {
		curPieces_[i] = new Piece(basePieceLayout[i], convCoordtoPixel(basePieceBoardCoords[i], nsize, boardSize_), getValTop(basePieceLayout[i].second));
		curPieces_[i]->init_graphics(1);
		curPieces_[i]->setImage(piecePNGNames[i], piecePNGLength[i], rendTar, boardSize_);
		curPieces_[i]->idx_ = i;
	}
	turn_ = false;
	WHITE = 0xFFFF000000000000;
	BLACK = 0x000000000000FFFF;

	this->drawBoardPNG(rendTar);
	return 1;
}

//Returns curPieces_ vector
vector<Piece*> ChessBoard::getPieces() {
	return curPieces_;
}

//Locates piece based on coords and returns that piece
//Otherwise NULL
Piece* ChessBoard::findPiece(D2D1_POINT_2F coordsOfPiece) {
	for (unsigned i = 0; i < curPieces_.size(); i++) {
		if (curPieces_[i]->getCoords().x == coordsOfPiece.x && curPieces_[i]->getCoords().y == coordsOfPiece.y) {
			return curPieces_[i];
		}
	}
	return NULL;
}
