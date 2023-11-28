#pragma comment(lib, "d2d1")

#include "engine.h"

static int MDWNFLAG;


template <class T> void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}
class MainWindow : public BaseWindow<MainWindow>
{
public:
    ID2D1Factory* pFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    ID2D1SolidColorBrush* pBrush;
    ID2D1SolidColorBrush* pBrush2;
    ID2D1SolidColorBrush* pBrush3;
    ID2D1SolidColorBrush* pBrush4;
    ID2D1SolidColorBrush* pBrush5;
    D2D1_ELLIPSE            ellipse;
    D2D1_ELLIPSE            ellipse2;
    D2D1_RECT_F*             BOARD;
    Piece                   Rook;
    ChessBoard boardMain;
    POINT* MCPTRONE;

    void    CalculateLayout();
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    OpenPaint();
    void    Resize();
    void    OnClick();
    void    initwin();

    MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL)
    {
    }

    PCWSTR  ClassName() const { return L"Circle Window Class"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


// Recalculate drawing layout when the size of the window changes.
// Unused -- Remove?

void MainWindow::CalculateLayout()
{
    if (pRenderTarget != NULL)
    {
        /*
        D2D1_SIZE_F size = pRenderTarget->GetSize();
        const float x = size.width / 2;
        const float y = size.height / 2;
        const float radius = min(x, y);
        ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
        */
    }
}


//Creates Resources for Graphics.
//Creates render target, client rectangle, and brushes.
HRESULT MainWindow::CreateGraphicsResources()
{
    HRESULT hr = S_OK;
    if (pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);
        outputnum(rc.right, rc.bottom, { 0,0 }, {0, 0});
        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &pRenderTarget);

        if (SUCCEEDED(hr))
        {
            const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 1.0f);
            hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);
            const D2D1_COLOR_F color2 = D2D1::ColorF((float)242/256, (float)218/256, (float)111/256);
            hr = pRenderTarget->CreateSolidColorBrush(color2, &pBrush2);
            const D2D1_COLOR_F color3 = D2D1::ColorF(0, 0, 1.0f);
            hr = pRenderTarget->CreateSolidColorBrush(color3, &pBrush3);
            const D2D1_COLOR_F black = D2D1::ColorF(D2D1::ColorF::SaddleBrown);
            hr = pRenderTarget->CreateSolidColorBrush(black, &pBrush4);
            const D2D1_COLOR_F white = D2D1::ColorF(D2D1::ColorF::SandyBrown);
            hr = pRenderTarget->CreateSolidColorBrush(white, &pBrush5);
            if (SUCCEEDED(hr))
            {
                CalculateLayout();
            }
        }
    }
    return hr;
}

//Release memory held for the render target and brushes
void MainWindow::DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush);
}

//Initialize the window
//Create Graphics Resources and begin paint
void MainWindow::initwin() {
    //Prepare for window creation
    CreateGraphicsResources();
    OutputDebugStringA("\nCalling init win\n");
    PAINTSTRUCT ps;
    //begin painting the window
    BeginPaint(Window(), &ps);
    //prepare render target for drawing
    pRenderTarget->BeginDraw();
    //set window to cornflower blue
    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CornflowerBlue));
    D2D1_SIZE_F size = pRenderTarget->GetSize();
    //draw the board to the window
    boardMain.initBoard(&pRenderTarget, size);
    //drawing done
    HRESULT hr = pRenderTarget->EndDraw();

    //Failed or something needs redone
    if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
    {
        DiscardGraphicsResources();
    }
    EndPaint(Window(), &ps);
}

//Similar to initwin()
//Not called, replaced by initwin()
//Remove ?
void MainWindow::OpenPaint()
{
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        BeginPaint(m_hwnd, &ps);

        pRenderTarget->BeginDraw();
        OutputDebugStringA("testing if open paint is run\n");
        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
        D2D1_SIZE_F size = pRenderTarget->GetSize();
        
        hr = pRenderTarget->EndDraw();
        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
        {
            DiscardGraphicsResources();
        }
        EndPaint(m_hwnd, &ps);
    }
}

//Create graphics resources
//Then open window and draw on it
void MainWindow::OnPaint()
{
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        BeginPaint(m_hwnd, &ps);
        pRenderTarget->BeginDraw();
        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CornflowerBlue));

        D2D1_SIZE_F size = pRenderTarget->GetSize();

        boardMain.drawBoardPNG(&pRenderTarget);

        hr = pRenderTarget->EndDraw();
        //boardMain.~ChessBoard();

        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
        {
            DiscardGraphicsResources();
        }
        EndPaint(m_hwnd, &ps);
    }
}

//What to do on click
//Check for piece on spot clicked, then select piece by highlighting it.
//Check for possible movements for that piece and display them
void MainWindow::OnClick() {
    //get position of cursor
    GetCursorPos(MCPTRONE);
    ScreenToClient(Window(), MCPTRONE);
    //Check if in the board
    D2D1_POINT_2U t = { (int)MCPTRONE->x, (int)MCPTRONE->y };
    float pos = -boardMain.boardSize_ / 2 + pRenderTarget->GetSize().width / 2;
    float posy = -boardMain.boardSize_ / 2 + pRenderTarget->GetSize().height / 2;
    if (t.x < pos || t.y < posy || t.x >(pos + boardMain.boardSize_) || t.y >(posy + boardMain.boardSize_)) {
        boardMain.is_selected_ = false;
        return;
    }
    //Prepare to highlight piece
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        BeginPaint(m_hwnd, &ps);
        pRenderTarget->BeginDraw();

        //Determine where on board clicked
        D2D1_POINT_2F tmp, tmp2, tmp3;
        int p_s = boardMain.boardSize_ / 8;
        t.x -= pos;
        t.y -= posy;
        t.x -= t.x % p_s;
        t.y -= t.y % p_s;
        t.x += pos;
        t.y += posy;

        D2D1_SIZE_F size = pRenderTarget->GetSize();

        vector<D2D1_RECT_F> possiblemoves;
        vector<Piece*> idxp;
        //Find piece based on where clicked
        Piece* temp  = boardMain.findPiece({ (float)t.x,(float)t.y });
        
        Piece* temp2;
        Piece* temp3;
        moves mlist;
        //if there is a piece where you click
        if (temp != NULL) {
            OutputDebugStringA("piece->size_ = ");
            outputnum(boardMain.boardSize_);
            float bsize = temp->boardSize_;
                //if there is already a selected piece that is not the newly selecting piece, take it
                if (boardMain.is_selected_ && boardMain.selected_ != temp && temp->getType().first != boardMain.selected_->getType().first) {
                    boardMain.removePiece(temp->getCoords());
                    tmp = boardMain.selected_->getCoords();
                    boardMain.movePiece(boardMain.selected_->idx_, temp->getCoords());
                    boardMain.turn_ = !boardMain.turn_;
                    boardMain.is_selected_ = false;
                    boardMain.drawBoardPNG(&pRenderTarget);
                    pRenderTarget->FillRectangle(D2D1::RectF((float)tmp.x, (float)tmp.y, (float)tmp.x + p_s, (float)tmp.y + p_s), pBrush2);
                }
                //if there is not a currently selected piece
                else if (boardMain.is_selected_ == false && temp->getType().first == boardMain.turn_) {
                    if (temp->getType().first == boardMain.turn_) {
                        possiblemoves = mlist.getPotMoves(idxp, temp, pRenderTarget, boardMain);
                        boardMain.selected_ = temp;
                        for (auto i : possiblemoves) {
                            pRenderTarget->FillRectangle(i, pBrush2);
                        }
                        for (auto i : idxp) {
                            i->drawPiece(&pRenderTarget);
                        }
                        pRenderTarget->FillRectangle(D2D1::RectF((float)t.x, (float)t.y, (float)t.x + p_s, (float)t.y + p_s), pBrush);
                        boardMain.selected_->drawPiece(&pRenderTarget);
                        boardMain.is_selected_ = true;
                    }
                    //boardMain.turn_ = !boardMain.turn_;
                }
                //if there is a currently selected piece that is the same as the newly selected piece
                else {
                    boardMain.is_selected_ = false;
                    boardMain.selected_ = NULL;
                    boardMain.drawBoardPNG(&pRenderTarget);
                }
            //if their is already a selected piece that is not the newly selecting piece, take it
            if (boardMain.is_selected_ && boardMain.selected_ != temp && temp->getType().first != boardMain.selected_->getType().first) {
                boardMain.removePiece(temp->getCoords());
                tmp = boardMain.selected_->getCoords();
                boardMain.movePiece(boardMain.selected_->idx_, temp->getCoords());
                ULONGLONG tmppush1 = tmp.x * 8 + tmp.y;
                ULONGLONG tmppush2 = temp->getCoords().x * 8 + temp->getCoords().y;
                if (temp->getType().first == 1) {
                    BLACK = BLACK & !((ULONGLONG)1 << tmppush1);
                    BLACK = BLACK | ((ULONGLONG)1 << tmppush2);
                    WHITE = WHITE & !((ULONGLONG)1 << tmppush2);
                }
                else {
                    WHITE = WHITE & !((ULONGLONG)1 << tmppush1);
                    WHITE = WHITE | ((ULONGLONG)1 << tmppush2);
                    BLACK = BLACK & !((ULONGLONG)1 << tmppush2);
                }
                boardMain.turn_ = !boardMain.turn_;
                boardMain.is_selected_ = false;
                boardMain.drawBoardPNG(&pRenderTarget);
                pRenderTarget->FillRectangle(D2D1::RectF((float)tmp.x, (float)tmp.y, (float)tmp.x + p_s, (float)tmp.y + p_s), pBrush2);
            }
            //if their is not a currently selected piece
            else if (boardMain.is_selected_ == false && temp->getType().first == boardMain.turn_) {
                //if (temp->getType().first == boardMain.turn_) {
                ulong moves_ = mlist.testFunc(temp->getCoords(), temp->getType(),WHITE, BLACK);
                D2D1_POINT_2F coords, pixel;
                for (auto i = 0; i < 64; i++) {
                    coords.x = (int)(i / 8);
                    coords.y = i % 8;
                    pixel = convCoordtoPixel(coords, pRenderTarget->GetSize(), boardMain.boardSize_);
                    if(moves_%2){
                        pRenderTarget->FillRectangle(D2D1::RectF(pixel.x, pixel.y, pixel.x + p_s, pixel.y + p_s), pBrush);
                    }
                    moves_ = moves_ >> 1;
                }
                pRenderTarget->FillRectangle(D2D1::RectF((float)t.x, (float)t.y, (float)t.x + p_s, (float)t.y + p_s), pBrush);
                //boardMain.selected_->drawPiece(&pRenderTarget);
                boardMain.is_selected_ = true;
                //}
                //boardMain.turn_ = !boardMain.turn_;
            }
            //if their is a currently selected piece that is the same as the newly selected piece
            else {
                boardMain.is_selected_ = false;
                boardMain.selected_ = NULL;
                boardMain.drawBoardPNG(&pRenderTarget);
            }
        }
        //if there is a selected piece and their is no piece at the clicked location
        else if (boardMain.is_selected_) {
            tmp = boardMain.selected_->getCoords();
            tmp2 = convPixeltoCoord(tmp, boardMain.getBoardCoords(), boardMain.boardSize_);
            tmp3 = convPixeltoCoord({ (float)t.x, (float)t.y }, boardMain.getBoardCoords(), boardMain.boardSize_);
            temp = boardMain.selected_;
            boardMain.movePiece(boardMain.selected_->idx_, { (float)t.x,(float)t.y });
            boardMain.turn_ = !boardMain.turn_;
            ULONGLONG tmppush1 = tmp3.x * 8 + tmp3.y;
            ULONGLONG tmppush2 = temp->getCoords().x * 8 + temp->getCoords().y;
            if (temp->getType().first == 1) {
                BLACK = BLACK & !((ULONGLONG)1 << tmppush1);
                BLACK = BLACK | ((ULONGLONG)1 << tmppush2);
            }
            else {
                WHITE = WHITE & !((ULONGLONG)1 << tmppush1);
                WHITE = WHITE | ((ULONGLONG)1 << tmppush2);
            }


            
            //en Passant Check
            if (temp->getType().second == PAWN && temp->getType().first == 0 && tmp2.x == 3) {
                temp2 = boardMain.findPiece(convCoordtoPixel({ tmp2.x,tmp2.y + 1 }, pRenderTarget->GetSize(), boardMain.boardSize_));
                temp3 = boardMain.findPiece(convCoordtoPixel({ tmp2.x,tmp2.y - 1 }, pRenderTarget->GetSize(), boardMain.boardSize_));
                if (temp2 != NULL) {
                    if (temp2->getType().second == PAWN && temp2->getType().first) {
                        if ((tmp3.x == tmp2.x - 1) && (tmp3.y == tmp2.y + 1)) {
                            boardMain.removePiece(convCoordtoPixel({ tmp2.x,tmp2.y + 1 }, pRenderTarget->GetSize(), boardMain.boardSize_));
                        }
                    }
                }
                if (temp3 != NULL) {
                    if (temp3->getType().second == PAWN && temp3->getType().first) {
                        if ((tmp3.x == tmp2.x - 1) && (tmp3.y == tmp2.y - 1)) {
                            boardMain.removePiece(convCoordtoPixel({ tmp2.x,tmp2.y - 1 }, pRenderTarget->GetSize(), boardMain.boardSize_));
                        }
                    }
                }
            }
            else if (temp->getType().second == PAWN && temp->getType().first == 1 && tmp2.x == 4) {
                temp2 = boardMain.findPiece(convCoordtoPixel({ tmp2.x,tmp2.y + 1 }, pRenderTarget->GetSize(), boardMain.boardSize_));
                temp3 = boardMain.findPiece(convCoordtoPixel({ tmp2.x,tmp2.y - 1 }, pRenderTarget->GetSize(), boardMain.boardSize_));
                if (temp2 != NULL) {
                    if (temp2->getType().second == PAWN && temp2->getType().first == 0) {
                        if ((tmp3.x == tmp2.x + 1) && (tmp3.y == tmp2.y + 1)) {
                            boardMain.removePiece(convCoordtoPixel({ tmp2.x,tmp2.y + 1 }, pRenderTarget->GetSize(), boardMain.boardSize_));
                        }
                    }
                }
                if (temp3 != NULL) {
                    if (temp3->getType().second == PAWN && temp3->getType().first == 0) {
                        if ((tmp3.x == tmp2.x + 1) && (tmp3.y == tmp2.y - 1)) {
                            boardMain.removePiece(convCoordtoPixel({ tmp2.x,tmp2.y - 1 }, pRenderTarget->GetSize(), boardMain.boardSize_));
                        }
                    }
                }
            }
            boardMain.drawBoardPNG(&pRenderTarget);
            pRenderTarget->FillRectangle(D2D1::RectF((float)tmp.x, (float)tmp.y, (float)tmp.x + p_s, (float)tmp.y + p_s), pBrush2);
            boardMain.is_selected_ = false;
        }
        

        hr = pRenderTarget->EndDraw();

        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
        {
            DiscardGraphicsResources();
        }
        EndPaint(m_hwnd, &ps);
    }
}

//Resize the window
//Unused?
void MainWindow::Resize()
{
    if (pRenderTarget != NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        pRenderTarget->Resize(size);
        CalculateLayout();
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}

//WinMain
//Where the magic happens
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    //Create MainWindow object
    MainWindow win;
    //L MB not down
    MDWNFLAG = 0;
    win.MCPTRONE = new(POINT);

    HRESULT hr = CoInitialize(NULL);
    
    //Create chess window
    if (!win.Create(L"Test Chess", WS_OVERLAPPEDWINDOW))
    {
        return 0;
    }
    //Show window
    ShowWindow(win.Window(), nCmdShow);
    //Create resources
    win.CreateGraphicsResources();
    D2D1_SIZE_F size = win.pRenderTarget->GetSize();

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

//Handle possible messages
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {

    //Create message
    case WM_CREATE:
        //OutputDebugStringA("WM_Create MESSAge \n");
        //Create factory and check if successful
        if (FAILED(D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
        {
            return -1;  // Fail CreateWindowEx.
        }
        //initialize the window
        initwin();
        return 0;

    //Destroy message
    case WM_DESTROY:
        //Release Memory
        DiscardGraphicsResources();
        SafeRelease(&pFactory);
        PostQuitMessage(0);
        return 0;

    //Paint message
    case WM_PAINT:
        OnPaint();
        return 0;

    //Left Mouse Button Up
    case WM_LBUTTONUP:
        MDWNFLAG = 0;
        return 0;

    //Left MB Down
    case WM_LBUTTONDOWN:
        //Click
        MDWNFLAG = 1;
        OnPaint();
        OnClick();
        return 0;

    //Size message
    case WM_SIZE:
        Resize();
        return 0;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}