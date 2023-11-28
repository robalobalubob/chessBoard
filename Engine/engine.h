#pragma once

#include "../Test/ChessBoard.h"
#include "../Test/Moves.h"


template <class DERIVED_TYPE> 
class BaseWindow
{
public:
    
    //Window procedure definition
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        DERIVED_TYPE *pThis = NULL;

        if (uMsg == WM_NCCREATE)
        {
            CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
            pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

            pThis->m_hwnd = hwnd;
        }
        else
        {
            pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        }
        if (pThis)
        {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }
        else
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    //Default constructor
    BaseWindow() : m_hwnd(NULL) { }

    //Create default window
    BOOL Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = 0,
        int nHeight = 0,
        HWND hWndParent = 0,
        HMENU hMenu = 0
        )
    {
        WNDCLASS wc = {0};

        wc.lpfnWndProc   = DERIVED_TYPE::WindowProc;
        wc.hInstance     = GetModuleHandle(NULL);
        wc.lpszClassName = ClassName();

        RegisterClass(&wc);

        m_hwnd = CreateWindowEx(
            dwExStyle, ClassName(), lpWindowName, WS_OVERLAPPEDWINDOW, x, y,
            nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this);

        return (m_hwnd ? TRUE : FALSE);
    }

    //Get m_hwnd
    HWND Window() const { 
        //resize window based on dpi to default size
        if (m_hwnd) {

            float dpi = GetDpiForWindow(m_hwnd);
            outputnum(dpi, 0, { 0,0 }, { 0,0 });

            int nWidth = static_cast<int>(ceil(1520.f * dpi / 96.f));
            int nHeight = static_cast<int>(ceil(770.f * dpi / 96.f));

            DWORD dwStyle = GetWindowLongPtr(m_hwnd, GWL_STYLE);
            DWORD dwExStyle = GetWindowLongPtr(m_hwnd, GWL_EXSTYLE);
            HMENU menu = GetMenu(m_hwnd);

            RECT rc = { 0, 0 , nWidth, nHeight };

            AdjustWindowRectEx(&rc, dwStyle, menu ? TRUE : FALSE, dwExStyle);
            SetWindowPos(
                m_hwnd,
                NULL,
                NULL,
                NULL,
                rc.right - rc.left,
                rc.bottom - rc.top,
                SWP_NOMOVE
            );
        }
        return m_hwnd; }

protected:

    virtual PCWSTR  ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

    HWND m_hwnd;
};
