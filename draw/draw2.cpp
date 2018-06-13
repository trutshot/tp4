// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <time.h>
#include <cstdio>

#define MAX_LOADSTRING 100
#define ID_BUTTON1				200
#define ID_BUTTON2				201
#define ID_BUTTON3				202
#define ID_BUTTON4				203
#define ID_BUTTON5				204
#define ID_BUTTON6				205
#define ID_BUTTON7				206
#define ID_BUTTON8				207   
#define ID_BUTTON9				208
#define ID_BUTTON10				209
#define ID_BUTTON11				210
#define ID_BUTTON12				211
#define ID_BUTTON13				212


const WORD ID_TIMER=1;
const WORD ID_TIMER1=2;
const WORD ID_TIMER2=3;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

int polozenie=500;
int wn_windy;

int gdzie_winda=0;
int gdzie_pasazer;
int dokad;

int predkosc=10;

int px; //1000
int py; //320

bool czy_cz;
// buttons
HWND hwndButton;
// sent data
RECT drawArea1 = { 595,105, 805, 610 }; // winda
RECT drawArea2 = {100, 100, 10000, 50000};

RECT drawArea3 = {811,100, 1159,359}; //pietro 2
RECT drawArea4 = {210,100, 580,239}; //pietro 3
RECT drawArea5 = {210,250, 580,479}; //pietro 1
RECT drawArea6 = {811,370, 1159,599}; //pietro 0

RECT drawArea10 = {100, 0, 1000, 100};
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);

void rysuj_pietra(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	Graphics graphics(hdc);

	Pen pen(Color(255, 0, 0, 255));
	graphics.DrawRectangle(&pen,590,100,220,520);
	graphics.DrawRectangle(&pen,600,500,200,100);
	
	graphics.DrawLine(&pen,810,600,1200,600);
	
	graphics.DrawLine(&pen,590,480,200,480);
	
	graphics.DrawLine(&pen,810,360,1200,360);
	
	graphics.DrawLine(&pen,590,240,200,240);
	
	WCHAR string1[] = L"00kg";
	 PointF origin(650.0f, 30.0f);
	 Font myFont(L"Arial", 16);
	 SolidBrush blackBrush(Color(255, 0, 0, 0));
	 graphics.DrawString(string1,4,&myFont,origin,&blackBrush);
}
void masa(HDC hdc,int ile)
{
	Graphics graphics(hdc);

   WCHAR string[] = L"70kg";
   WCHAR string1[] = L"00kg";

   Font myFont(L"Arial", 16);
   PointF origin(650.0f, 30.0f);
   SolidBrush blackBrush(Color(255, 0, 0, 0));
	if(ile==1)
   graphics.DrawString(string,4,&myFont,origin,&blackBrush);
   if(ile==0)
   graphics.DrawString(string1,4,&myFont,origin,&blackBrush);	
}
void rysuj_pasazera(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255,150, 50, 255));
	graphics.DrawRectangle(&pen,px,py,20,20);
}
void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	graphics.DrawRectangle(&pen,600,polozenie,200,100);

}
void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	if (drawArea==NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	EndPaint(hWnd, &ps);
}
void repaintWindow_p(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea,bool czy_cz)
{
	if(czy_cz==false)
	{
	InvalidateRect(hWnd, drawArea,false);
	hdc = BeginPaint(hWnd, &ps);
	rysuj_pasazera(hdc);
	EndPaint(hWnd, &ps);
	}
	if(czy_cz==true)
	{
		InvalidateRect(hWnd, drawArea, true);
	}
}
void repaintWindow_txt(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea,int ile)
{

	InvalidateRect(hWnd, drawArea,true);
	hdc = BeginPaint(hWnd, &ps);
	masa(hdc,ile);
	EndPaint(hWnd, &ps);
	
}
// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;


	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle (of exe) in our global variable

	// main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	// create button and store the handle    
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Na 3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		150, 430,                                  // the left and top co-ordinates
		50, 20,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need                                                   
	                  // extra bits you dont really need
	    hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Na 0"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		 150, 470,                               // the left and top co-ordinates
		50, 20,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);              

		hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Na 1 "),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		150, 210,                                   // the left and top co-ordinates
		50, 20,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON3,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);              
		
		hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Na 2 "),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		150, 450,                                  // the left and top co-ordinates
		50, 20,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON4,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);     
		
		hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Na 2 "),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		150, 190,                                  // the left and top co-ordinates
		50, 20,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON5,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);    
		
		hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Na 0 "),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		150, 230,                                  // the left and top co-ordinates
		50, 20,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON6,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);  
		
		hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Na 3 "),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1200, 310,                                  // the left and top co-ordinates
		50, 20,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON7,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);  
		
		hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Na 1 "),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1200, 330,                                  // the left and top co-ordinates
		50, 20,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON8,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);  
	  	   
	  	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Na 0 "),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1200, 350,                                  // the left and top co-ordinates
		50, 20,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON9,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);  
		
		hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Na 3 "),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1200, 550,                                  // the left and top co-ordinates
		50, 20,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON10,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);  
		
		hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Na 2 "),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1200, 570,                                  // the left and top co-ordinates
		50, 20,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON11,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);  
			
		hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Na 1 "),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1200, 590,                                  // the left and top co-ordinates
		50, 20,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON12,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);  

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// MENU & BUTTON messages
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON1:
			px=400;
			py=440;
			repaintWindow_p(hWnd, hdc, ps, &drawArea5,false);
			gdzie_pasazer=1;
			dokad=3;
			SetTimer(hWnd, ID_TIMER,predkosc, NULL );
			break;
		case ID_BUTTON2:
			px=400;
			py=440;
			repaintWindow_p(hWnd, hdc, ps, &drawArea5,false);
			gdzie_pasazer=1;
			dokad=0;
			SetTimer(hWnd, ID_TIMER,predkosc, NULL );
			break;
		case ID_BUTTON3:
			px=400;
			py=200;
			repaintWindow_p(hWnd, hdc, ps, &drawArea4,false);
			gdzie_pasazer=3;
			dokad=1;
			SetTimer(hWnd, ID_TIMER,predkosc, NULL );
			break;
		case ID_BUTTON4:
			px=400;
			py=440;
			repaintWindow_p(hWnd, hdc, ps, &drawArea5,false);
			gdzie_pasazer=1;
			dokad=2;
			SetTimer(hWnd, ID_TIMER,predkosc, NULL );
			break;
		case ID_BUTTON5:
			px=400;
			py=200;
			repaintWindow_p(hWnd, hdc, ps, &drawArea4,false);
			gdzie_pasazer=3;
			dokad=2;
			SetTimer(hWnd, ID_TIMER,predkosc, NULL );
			break;
		case ID_BUTTON6:
			px=400;
			py=200;
			repaintWindow_p(hWnd, hdc, ps, &drawArea4,false);
			gdzie_pasazer=3;
			dokad=0;
			SetTimer(hWnd, ID_TIMER,predkosc, NULL );
			break;
		case ID_BUTTON7:
			px=1000;
			py=320;
			repaintWindow_p(hWnd, hdc, ps, &drawArea3,false);
			gdzie_pasazer=2;
			dokad=3;
			SetTimer(hWnd, ID_TIMER,predkosc, NULL );
			break;
		case ID_BUTTON8:
			px=1000;
			py=320;
			repaintWindow_p(hWnd, hdc, ps, &drawArea3,false);
			gdzie_pasazer=2;
			dokad=1;
			SetTimer(hWnd, ID_TIMER,predkosc, NULL );
			break;
		case ID_BUTTON9:
			px=1000;
			py=320;
			repaintWindow_p(hWnd, hdc, ps, &drawArea3,false);
			gdzie_pasazer=2;
			dokad=0;
			SetTimer(hWnd, ID_TIMER,predkosc, NULL );
			break;
		case ID_BUTTON10:
			px=1000;
			py=560;
			repaintWindow_p(hWnd, hdc, ps, &drawArea6,false);
			gdzie_pasazer=0;
			dokad=3;
			SetTimer(hWnd, ID_TIMER,predkosc, NULL );
			break;
		case ID_BUTTON11:
			px=1000;
			py=560;
			repaintWindow_p(hWnd, hdc, ps, &drawArea6,false);
			gdzie_pasazer=0;
			dokad=2;
			SetTimer(hWnd, ID_TIMER,predkosc, NULL );
			break;
		case ID_BUTTON12:
			px=1000;
			py=560;
			repaintWindow_p(hWnd, hdc, ps, &drawArea6,false);
			gdzie_pasazer=0;
			dokad=1;
			SetTimer(hWnd, ID_TIMER,predkosc, NULL );
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		rysuj_pietra(hWnd, hdc, ps, &drawArea2);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_TIMER:
		switch (wParam)
		{
		case ID_TIMER:
			repaintWindow(hWnd, hdc, ps, &drawArea1);
			if(gdzie_pasazer-gdzie_winda>0)
			polozenie--;
			if(gdzie_pasazer-gdzie_winda<0)
			polozenie++;
			if(polozenie==500-120*gdzie_pasazer)
			{
				repaintWindow_txt(hWnd, hdc, ps, &drawArea10,1);
				if(gdzie_pasazer==2)
				{
				repaintWindow_p(hWnd, hdc, ps, &drawArea3,true);
				}
				if(gdzie_pasazer==3)
				{
				repaintWindow_p(hWnd, hdc, ps, &drawArea4,true);
				}
				if(gdzie_pasazer==1)
				{
				repaintWindow_p(hWnd, hdc, ps, &drawArea5,true);
				}
				if(gdzie_pasazer==0)
				{
				repaintWindow_p(hWnd, hdc, ps, &drawArea6,true);
				}
			py=550-120*gdzie_pasazer;
			px=700;
			repaintWindow_p(hWnd, hdc, ps, &drawArea1,false);
			KillTimer( hWnd, ID_TIMER );
			gdzie_winda=gdzie_pasazer;
			SetTimer(hWnd, ID_TIMER2,50, NULL );
			SetTimer(hWnd, ID_TIMER1,predkosc, NULL );
			}
			break;
		case ID_TIMER1:
			repaintWindow(hWnd, hdc, ps, &drawArea1);
			repaintWindow_p(hWnd, hdc, ps, &drawArea1,false);
			if(dokad-gdzie_winda>0)
			{
			polozenie--;
			py--;
			}
			if(dokad-gdzie_winda<0)
			{
			polozenie++;
			py++;
			}
			if(polozenie==500-120*dokad)
			{
			repaintWindow_txt(hWnd, hdc, ps, &drawArea10,0);		
			KillTimer( hWnd, ID_TIMER1 );
			gdzie_winda=dokad;
			RECT drawArea7 = {610,530-120*gdzie_winda, 790,590-120*gdzie_winda};
			repaintWindow_p(hWnd, hdc, ps, &drawArea7,true);
			}
			break;
		break;
		}
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
