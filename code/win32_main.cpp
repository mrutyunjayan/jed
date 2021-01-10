/*
// TODO(Jai): 
        .   Create window, Message loop
.   Direct2D/DirectWrite text rendering
.   Buffer abstraction: gap buffer, etc.
.   Window management system
*/
#include "pch.h"

#include "win32_main.h"

global ID2D1Factory* d2dFactory;
global IDWriteFactory* dWriteFactory;
global ID2D1HwndRenderTarget* renderTarget;

#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d2d1.lib")

LRESULT
win32_JedWindowProc(HWND window,
                    UINT messageType,
                    WPARAM wParam,
                    LPARAM lParam) {
    
    LRESULT result = 0;
    HRESULT hResult = 0;
    
    switch (messageType) {
        
        case WM_DESTROY :{
            PostQuitMessage(0);
        } break;
        case WM_SIZE: {
            
            if (renderTarget) {
                renderTarget->Release();
            }
            
            RECT clientRect;
            GetClientRect(window, &clientRect);
            D2D1_SIZE_U windowSize;
            windowSize.width = (u32)(clientRect.right - clientRect.left);
            windowSize.height = (u32)(clientRect.bottom - clientRect.top);
            hResult = d2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
                                                         D2D1::HwndRenderTargetProperties(window, windowSize),
                                                         &renderTarget);
        } break;
        case WM_PAINT: {
            
            renderTarget->BeginDraw();
            renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Red));
            renderTarget->EndDraw();
            ValidateRect(window, 0);
        } break;
        default: {
            result = DefWindowProcA(window,
                                    messageType,
                                    wParam,
                                    lParam);
        } break;
    }
    
    return result;
}

int 
WinMain(HINSTANCE instance,
        HINSTANCE prevInstance,
        PSTR commandLine,
        int showCommand) {
    
    HRESULT hResult = 0;
    hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED,
                                __uuidof(ID2D1Factory),
                                (void**)&d2dFactory);
    hResult = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                                  __uuidof(IDWriteFactory),
                                  (IUnknown**)&dWriteFactory);
    
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
    WNDCLASSA windowClass = {0};
#pragma clang diagnostic pop
    
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = win32_JedWindowProc;
    windowClass.hInstance = instance;
    windowClass.lpszClassName = "jed";
    // windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	
    if (!RegisterClassA(&windowClass)) {
        //// TODO(Jai): handle error
        return -1;
    }
    
    HWND window = CreateWindowA("jed",
                                "JED",
                                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                0,
                                0,
                                instance,
                                0);
    
    if (!window) {
        // TODO(Jai): handle error
        return -1;
    }
    
    MSG message;
    while (GetMessage(&message,
                      0,
                      0, 0)) {
        
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    
    return 0;
}
