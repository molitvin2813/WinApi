#include <Windows.h>
#include "Product.h"
#include "WorkPlace.h"
#include "Fabric.h"

#define MAIN_FORM_BTN_RUN  3000
#define MAIN_FORM_BTN_STOP 3001
#define MAIN_FORM_LIST_FIRST_LINE  100
#define MAIN_FORM_LIST_SECOND_LINE 101
#define MAIN_FORM_LABEL_1 500
#define mAIN_FORM_LABEL_2 501
#define ENTER_FORM_BTN_OK 3002
#define ENTER_FORM_BTN_CANCEL 3003
#define ENTER_FORM_EDIT_1 2500
#define ENTER_FORM_EDIT_2 2501
#define ENTER_FORM_EDIT_3 2502
#define MAIN_FORM_CB_1 5555
#define MAIN_FORM_CB_2 5556
static HWND btnRun;
static HWND btnStop;
static HWND chekbox1;
static HWND chekbox2;

static HWND listBoxFirstLine;
static HWND listBoxSecondLine;

static HWND label1;
static HWND label2;

static HWND btnOK;
static HWND btnCancel;

static HWND editBox1;
static HWND editBox2;
static HWND editBox3;

HANDLE hMutex;
HANDLE hThreads = NULL;

HANDLE hMutex2;
HANDLE hThreads2 = NULL;

HWND hWndMain;


LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK EnterWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK StatWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CreateMenuItem(HMENU hMenu, const char* str, UINT uIns,
	UINT uCom, HMENU hSubMenu, BOOL flag, UINT fType);

DWORD WINAPI ThreadProc(LPVOID lpParameter);
DWORD WINAPI ThreadProc2(LPVOID lpParameter);

Fabric fabric = Fabric();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{

	HWND hWnd;
	MSG lpMsg;
	WNDCLASS w;

	w.lpszClassName = "Производственная линия";
	w.hInstance = hInstance;
	w.lpfnWndProc = MainWndProc;
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	w.hIcon = 0;
	w.lpszMenuName = 0;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;

	//Если не удалось зарегистрировать класс окна - выходим
	if (!RegisterClass(&w))
		return 0;

	//Создадим окно в памяти, заполнив аргументы CreateWindow
	hWnd = CreateWindow("Производственная линия",
		"Производственная линия",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		750,
		500,
		(HWND)NULL,
		(HMENU)NULL,
		(HINSTANCE)hInstance,
		(HINSTANCE)NULL);

	//Выводим окно из памяти на экран
	ShowWindow(hWnd, nCmdShow);
	//Обновим содержимое окна
	UpdateWindow(hWnd);

	//Цикл обработки сообщений

	while (GetMessage(&lpMsg, NULL, 0, 0)) { //Получаем сообщение из очереди
		TranslateMessage(&lpMsg); //Преобразует сообщения клавиш в символы
		DispatchMessage(&lpMsg); //Передаёт сообщение соответствующей функции окна
	}
	return(lpMsg.wParam);
}

HINSTANCE hInstance;

BOOL CreateMenuItem(HMENU hMenu,const char* str, UINT uIns,
	UINT uCom, HMENU hSubMenu, BOOL flag, UINT fType)
{
	MENUITEMINFO mii; mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STATE | MIIM_TYPE | MIIM_SUBMENU | MIIM_ID;
	mii.fType = fType; mii.fState = MFS_DEFAULT;
	mii.dwTypeData = (LPSTR)str; mii.cch = sizeof(str);
	mii.wID = uCom;
	mii.hSubMenu = hSubMenu;
	return InsertMenuItem(hMenu, uIns, flag, &mii);
}


DWORD __stdcall ThreadProc(LPVOID lpParameter)
{
	while (true) {
		
		while (fabric.mainLineArray.firstLine.countProductOnLine !=fabric.mainLineArray.firstLine.getN()) {
			if (fabric.mainLineArray.currentProduct == fabric.mainLineArray.totcount)
				break;
			if (fabric.mainLineArray.firstLine.countProductOnLine != fabric.mainLineArray.firstLine.getN()) {
				fabric.mainLineArray.firstLine.addNewProduct(fabric.mainLineArray.arrayOfProduct[fabric.mainLineArray.currentProduct]);

				SendMessage(listBoxFirstLine, LB_ADDSTRING, 0, (LPARAM)fabric.mainLineArray.arrayOfProduct[fabric.mainLineArray.currentProduct].getNameOfProduct().c_str());
				fabric.mainLineArray.currentProduct++;
			}
		}
		if (fabric.mainLineArray.firstLine.countProductOnLine == 0)
			break;
		if (fabric.mainLineArray.secondLine.countProductOnLine != fabric.mainLineArray.secondLine.getN()) {
			CheckDlgButton(hWndMain, MAIN_FORM_CB_1, BST_CHECKED);
			UpdateWindow(hWndMain);
			Sleep(500);
			fabric.mainLineArray.firstWorkPlace.doWork();

			fabric.mainLineArray.firstLine.countProductOnLine--;
			fabric.mainLineArray.secondLine.addNewProduct(fabric.mainLineArray.firstLine.arrayOfProduct[fabric.mainLineArray.firstLine.countProductOnLine]);


			SendMessage(listBoxSecondLine, LB_ADDSTRING, 0, (LPARAM)fabric.mainLineArray.secondLine.arrayOfProduct[fabric.mainLineArray.secondLine.countProductOnLine - 1].getNameOfProduct().c_str());
			SendMessage(listBoxFirstLine, LB_DELETESTRING, (WPARAM)fabric.mainLineArray.firstLine.countProductOnLine, 0);
		}
		UpdateWindow(hWndMain);
		CheckDlgButton(hWndMain, MAIN_FORM_CB_1, BST_UNCHECKED);
		Sleep(500);
		UpdateWindow(hWndMain);
	}
	
	ExitThread(0);
}
DWORD __stdcall ThreadProc2(LPVOID lpParameter)
{
	while (true) {
		if (fabric.mainLineArray.secondLine.countProductOnLine != 0) {
			CheckDlgButton(hWndMain, MAIN_FORM_CB_2, BST_CHECKED);
			UpdateWindow(hWndMain);
			Sleep(1000);
			fabric.mainLineArray.firstWorkPlace.doWork();
			fabric.mainLineArray.secondLine.countProductOnLine--;
			fabric.mainLineArray.countProduct++;
			SendMessage(listBoxSecondLine, LB_DELETESTRING, (WPARAM)fabric.mainLineArray.secondLine.countProductOnLine, 0);
			UpdateWindow(hWndMain);
		}
		if(fabric.mainLineArray.countProduct > 0 && fabric.mainLineArray.countProduct == fabric.mainLineArray.totcount)
			break;
		CheckDlgButton(hWndMain, MAIN_FORM_CB_2, BST_UNCHECKED);
		UpdateWindow(hWndMain);
		Sleep(1000);
	}

	ExitThread(0);
}



LRESULT CALLBACK MainWndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
	static HMENU hMainMenu,hSubMenu, hSubMenu2;
	int i = 0;
	bool f = false;
	hWndMain = hWnd;
	switch (messg)
	{
	case WM_CREATE:
		
		

		hMainMenu = CreateMenu();

		hSubMenu2 = CreateMenu();
		AppendMenuW(hSubMenu2, MFT_STRING, 57,L"Ввести исходные данные");
		AppendMenuW(hSubMenu2, MFT_STRING,58,L"Просмотреть статискику");
		AppendMenuW(hMainMenu, MF_POPUP, (UINT_PTR)hSubMenu2,L"Меню");

		
		SetMenu(hWnd, hMainMenu);
		DrawMenuBar(hWnd);

		btnRun = CreateWindow("button", "Запустить",
			WS_CHILD | WS_VISIBLE |
			BS_DEFPUSHBUTTON, 550, 150, 150, 20, hWnd,
			(HMENU)MAIN_FORM_BTN_RUN, hInstance, NULL);

		btnStop = CreateWindow("button", "Остановить Работу",
			WS_CHILD | WS_VISIBLE |
			BS_DEFPUSHBUTTON, 550, 180, 150, 20, hWnd,
			(HMENU)MAIN_FORM_BTN_STOP, hInstance, NULL);

		label1 = CreateWindow("static", "Первая линия",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			50, 50, 150, 20,
			hWnd, (HMENU)MAIN_FORM_LABEL_1,
			hInstance, NULL);
		
		listBoxFirstLine = CreateWindow("listbox", NULL,
			WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_WANTKEYBOARDINPUT,
			50, 100, 200, 250, hWnd, (HMENU)MAIN_FORM_LIST_FIRST_LINE, hInstance,NULL);

		chekbox1 = CreateWindowEx(NULL,"button","",
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			270,150,25,30,hWnd,(HMENU)MAIN_FORM_CB_1,GetModuleHandle(NULL),NULL);

		label1 = CreateWindow("static", "Вторая линия",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			300, 50, 150, 20,
			hWnd, (HMENU)mAIN_FORM_LABEL_2,
			hInstance, NULL);

		listBoxSecondLine = CreateWindow("listbox", NULL,
			WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_WANTKEYBOARDINPUT,
			300, 100, 200, 250, hWnd, (HMENU)MAIN_FORM_LIST_SECOND_LINE, hInstance, NULL);

		chekbox1 = CreateWindowEx(NULL, "button", "",
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			500, 150, 25, 30, hWnd, (HMENU)MAIN_FORM_CB_2, GetModuleHandle(NULL), NULL);

		hMutex = CreateMutex(NULL, FALSE, NULL);
		hThreads = CreateThread(NULL, 0, &ThreadProc, (LPVOID)hMutex, CREATE_SUSPENDED, NULL);

		hMutex2 = CreateMutex(NULL, FALSE, NULL);
		hThreads2 = CreateThread(NULL, 0, &ThreadProc2, (LPVOID)hMutex, CREATE_SUSPENDED, NULL);

		WNDCLASS wind;
		MSG lpMsg;
		wind.lpszClassName = "ВВОД ДАННЫХ";
		wind.hInstance = hInstance;
		wind.lpfnWndProc = EnterWndProc;
		wind.hCursor = LoadCursor(NULL, IDC_ARROW);
		wind.hIcon = 0;
		wind.lpszMenuName = 0;
		wind.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wind.style = CS_HREDRAW | CS_VREDRAW;
		wind.cbClsExtra = 0;
		wind.cbWndExtra = 0;

		//Если не удалось зарегистрировать класс окна - выходим
		if (!RegisterClass(&wind))
			return 0;

		//DialogBox(hInstance, MAKEINTRESOURCE(DLG_MODAL), hWnd, DlgProc,0);
		hWnd = CreateWindow("ВВОД ДАННЫХ",
			"ВВОД ДАННЫХ",
			WS_OVERLAPPEDWINDOW,
			100,
			100,
			500,
			250,
			(HWND)NULL,
			(HMENU)NULL,
			(HINSTANCE)hInstance,
			(HINSTANCE)NULL);

		WNDCLASS wind2;
		MSG lpMsg2;
		wind2.lpszClassName = "Статистика";
		wind2.hInstance = hInstance;
		wind2.lpfnWndProc = StatWndProc;
		wind2.hCursor = LoadCursor(NULL, IDC_ARROW);
		wind2.hIcon = 0;
		wind2.lpszMenuName = 0;
		wind2.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wind2.style = CS_HREDRAW | CS_VREDRAW;
		wind2.cbClsExtra = 0;
		wind2.cbWndExtra = 0;

		//Если не удалось зарегистрировать класс окна - выходим
		if (!RegisterClass(&wind2))
			return 0;

		//DialogBox(hInstance, MAKEINTRESOURCE(DLG_MODAL), hWnd, DlgProc,0);
		hWnd = CreateWindow("Статистика",
			"Статистика",
			WS_OVERLAPPEDWINDOW,
			100,
			100,
			500,
			250,
			(HWND)NULL,
			(HMENU)NULL,
			(HINSTANCE)hInstance,
			(HINSTANCE)NULL);

		//Цикл обработки сообщений
		return 0;
		break;
	case WM_INITDIALOG:
		hInstance = GetModuleHandle(NULL);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case MAIN_FORM_BTN_RUN:
			ResumeThread(hThreads);
			ResumeThread(hThreads2);
			
			
			return 0;
			break;
		case MAIN_FORM_BTN_STOP:
			SuspendThread(hThreads);
			SuspendThread(hThreads2);
			return 0;
			break;
		case 57:
			ShowWindow(FindWindow("ВВОД ДАННЫХ", NULL), 1);
			while (GetMessage(&lpMsg, NULL, 0, 0)) { //Получаем сообщение из очереди
				TranslateMessage(&lpMsg); //Преобразует сообщения клавиш в символы
				DispatchMessage(&lpMsg); //Передаёт сообщение соответствующей функции окна
			}
			

			return 0;
			break;

		case 58:
			ShowWindow(FindWindow("Статистика", NULL), 1);


			while (GetMessage(&lpMsg2, NULL, 0, 0)) { //Получаем сообщение из очереди
				TranslateMessage(&lpMsg2); //Преобразует сообщения клавиш в символы
				DispatchMessage(&lpMsg2); //Передаёт сообщение соответствующей функции окна
			}


			return 0;
			break;
		}
		break;

		//сообщение выхода - разрушение окна
	case WM_DESTROY:

		PostQuitMessage(0); //Посылаем сообщение выхода с кодом 0 - нормальное завершение
		break;
	case WM_PAINT:

		return 0;
		break;
	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
	}
	return 0;
}

LRESULT CALLBACK StatWndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
	static HWND label1;
	static HWND label2;
	static HWND label3;
	static HWND label4;

	static HWND btnShow;
	string s2 = "";
	char m[50];
	switch (messg)
	{
	case WM_CREATE:
		btnShow = CreateWindow("button", "Обновить статистику",
			WS_CHILD | WS_VISIBLE |
			BS_DEFPUSHBUTTON, 50, 25, 200, 20, hWnd,
			(HMENU)1488, hInstance, NULL);

		label1 = CreateWindow("static", s2.c_str(),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			50, 50, 500, 20,
			hWnd, (HMENU)MAIN_FORM_LABEL_1,
			hInstance, NULL);
		label2 = CreateWindow("static", s2.c_str(),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			50, 75, 500, 20,
			hWnd, (HMENU)MAIN_FORM_LABEL_1,
			hInstance, NULL);
		label3 = CreateWindow("static", s2.c_str(),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			50, 100, 500, 20,
			hWnd, (HMENU)MAIN_FORM_LABEL_1,
			hInstance, NULL);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case 1488:
			_itoa_s(fabric.mainLineArray.firstWorkPlace.timeWork, m, 10);
			s2 = "Время работы первого РМ :";
			s2.append(m);
			SetWindowText(label1, s2.c_str());

			_itoa_s(fabric.mainLineArray.secondWorkPlace.timeWork, m, 10);
			s2 = "Время работы второго РМ :";
			s2.append(m);
			SetWindowText(label2, s2.c_str());

			_itoa_s(fabric.mainLineArray.countProduct, m, 10);
			s2 = "Общее количество обработанных деталей :";
			s2.append(m);
			SetWindowText(label3, s2.c_str());

			
			break;
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		ShowWindow(hWnd, SW_HIDE);
		return 0;
		break;
	case WM_DESTROY: {PostQuitMessage(0); return 0; }

	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
	}
}

LRESULT CALLBACK EnterWndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
	char chBuff[20];
	char chBuff2[20];
	char chBuff3[20];
	
	switch (messg)
	{
	case WM_CREATE:
		btnOK = CreateWindow("button", "Подтвердить",
			WS_CHILD | WS_VISIBLE |
			BS_DEFPUSHBUTTON, 20, 180, 200, 20, hWnd,
			(HMENU)ENTER_FORM_BTN_OK, hInstance, NULL);

		btnCancel = CreateWindow("button", "Отмена",
			WS_CHILD | WS_VISIBLE |
			BS_DEFPUSHBUTTON, 270, 180, 200, 20, hWnd,
			(HMENU)ENTER_FORM_BTN_CANCEL, hInstance, NULL);
		editBox1 = CreateWindow("edit", "Всего товаров",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
			20, 50, 200, 20, hWnd,
			(HMENU)ENTER_FORM_EDIT_1, hInstance, NULL);

		editBox2 = CreateWindow("edit", "На первой",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
			270, 50, 200, 20, hWnd,
			(HMENU)ENTER_FORM_EDIT_2, hInstance, NULL);
		editBox3 = CreateWindow("edit", "На второй",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
			20, 100, 200, 20, hWnd,
			(HMENU)ENTER_FORM_EDIT_3, hInstance, NULL);
		break;
	case WM_CLOSE:

		PostQuitMessage(0);
		ShowWindow(hWnd, SW_HIDE);
		return 0;
		break;
	case WM_DESTROY: {PostQuitMessage(0); return 0; }
	case WM_COMMAND:
		switch (LOWORD(wParam)) 
		{
		case ENTER_FORM_BTN_OK:
			SendMessage(editBox1, EM_GETLINE, 0, (LPARAM)chBuff);
			SendMessage(editBox2, EM_GETLINE, 0, (LPARAM)chBuff2);
			SendMessage(editBox3, EM_GETLINE, 0, (LPARAM)chBuff3);
			fabric = Fabric(atoi(chBuff), atoi(chBuff2), atoi(chBuff3));
			PostQuitMessage(0);
			ShowWindow(hWnd, SW_HIDE);
			break;
		case ENTER_FORM_BTN_CANCEL:
			PostQuitMessage(0);
			ShowWindow(hWnd, SW_HIDE);
			break;
		}
		break;
	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
	}

}

