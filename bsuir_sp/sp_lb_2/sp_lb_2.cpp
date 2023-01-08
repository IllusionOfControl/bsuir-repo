#include "framework.h"
#include "sp_lb_2.h"
#include "Thread.h"
#include <string>
#include <io.h>
#include <fcntl.h>

#define MAX_LOADSTRING 100


Thread* threads[3] = {NULL, NULL, NULL};


HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            


DWORD WINAPI InfinityFunc(LPVOID lpParam) {
    while (true) {
        std::cout << "Thread runned by Skorokhod!" << std::endl;
        Sleep(50);
    }
}


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ThreadInfoBoxDispatcher(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    AllocConsole();
    HANDLE stdHandle;
    int hConsole;
    FILE* fp;
    stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    hConsole = _open_osfhandle((long)stdHandle, _O_TEXT);
    fp = _fdopen(hConsole, "w");

    freopen_s(&fp, "CONOUT$", "w", stdout);

    threads[0] = new MainThread();

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SPLB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPLB2));

    MSG msg;


    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPLB2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SPLB2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDM_INFORMATION_MAINTHREAD:
                DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_INFOTHREADBOX), hWnd, ThreadInfoBoxDispatcher, 0);
                break;
            case ID_INFORMATION_THREAD1:
                DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_INFOTHREADBOX), hWnd, ThreadInfoBoxDispatcher, 1);
                break;
            case ID_INFORMATION_THREAD2:
                DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_INFOTHREADBOX), hWnd, ThreadInfoBoxDispatcher, 2);
                break;

            case ID_THREAD1_CREATETHREAD: {
                if (threads[1]) break;
                threads[1] = Thread::CreateRunnableThread(InfinityFunc);
                break;
            }
            case IDM_THREAD1_CREATESUSPENDTHREAD: {
                if (threads[1]) break;
                threads[1] = Thread::CreateSuspendThread(InfinityFunc);
                break;
            }
            case IDM_THREAD1_SUSPENDTHREAD: {
                if (!threads[1]) break;
                threads[1]->SuspendWorkedThread();
                break;
            }
            case ID_THREAD1_RESUMETHREAD: {
                if (!threads[1]) break;
                threads[1]->ResumeWorkThread();
                break;
            }
            case IDM_THREAD1_TERMINATETHREAD: {
                if (!threads[1]) break;
                threads[1]->TerminateWorkThread();
                threads[1] = NULL;
                break;
            }

            case ID_THREAD2_CREATETHREAD: {
                if (threads[2]) break;
                threads[2] = Thread::CreateRunnableThread(InfinityFunc);
                break;
            }
            case IDM_THREAD2_CREATESUSPENDTHREAD: {
                if (threads[2]) break;
                threads[2] = Thread::CreateSuspendThread(InfinityFunc);
                break;
            }
            case IDM_THREAD2_SUSPENDTHREAD: {
                if (!threads[2]) break;
                threads[2]->SuspendWorkedThread();
                break;
            }
            case ID_THREAD2_RESUMETHREAD: {
                if (!threads[2]) break;
                threads[2]->ResumeWorkThread();
                break;
            }
            case ID_THREAD2_TERMINATETHREAD: {
                if (!threads[2]) break;
                threads[2]->TerminateWorkThread();
                threads[2] = NULL;
                break;
            }
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


INT_PTR CALLBACK ThreadInfoBoxDispatcher(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    //UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG: {
        Thread* thread = threads[(int)lParam];

        
        if (thread) {
            SetDlgItemText(hDlg, IDC_THREAD_TIMING, thread->GetFormatedWorkTime().c_str());
            SetDlgItemText(hDlg, IDC_THREAD_ID, std::to_wstring(thread->GetId()).c_str());
            SetDlgItemText(hDlg, IDC_THREAD_STATE, thread->GetTextState().c_str());
            SetDlgItemText(hDlg, IDC_THREAD_PRIORITY, std::to_wstring(thread->GetPriority()).c_str());
            SetDlgItemText(hDlg, IDC_THREAD_DESCRIPTOR, thread->GetTextDescriptor().c_str());
        }
        else {
            SetDlgItemText(hDlg, IDC_THREAD_TIMING, L"0");
            SetDlgItemText(hDlg, IDC_THREAD_ID, L"0");
            SetDlgItemText(hDlg, IDC_THREAD_STATE, L"Terminate");
            SetDlgItemText(hDlg, IDC_THREAD_PRIORITY, L"-1");
            SetDlgItemText(hDlg, IDC_THREAD_DESCRIPTOR, L"-1");
        }
        return (INT_PTR)TRUE;
    }

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}