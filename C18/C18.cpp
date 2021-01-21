#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include<commdlg.h>
#include<CommCtrl.h>
#include<fstream>

const DWORD MaxLength = 0xfffff;
char szClassName[] = "Name";
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASSEX wc;
	MSG msg;
	hInst = hInstance;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);
	hWnd = CreateWindow(szClassName, szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {


	static TCHAR name[256] = _T("C18.txt");
	DWORD result;
	static HANDLE hFile;
	static char text[4447] = " ", buf[MaxLength];
	static unsigned int arr1[1999], arr2[1999];
	int count = 0, arrcount = 0;
	char tempchar;
	switch (uMsg) {
	case WM_CREATE:

		for (int i = 1; i < 1999; i++) {
			text[i] = '\0';
		}

		for (int i = 1999; i >= 1; i = i - 2) {
			arr1[i - 1999] = i;
			_itoa_s(arr1[i - 1999], buf, _countof(buf), 10); //Преобразует целое число в строку. Число, которое требуется преобразовать. Буфер, содержащий результат преобразования. 
		// Основание, используемое для преобразования значения, которое должно находиться в диапазоне 2 - 36.
			strcat_s(text, _countof(text), buf); //Копирует строку. Расположение буфера строки назначения.
			//Расположение буфера строки назначения (Вычисляет количество элементов ). Буфер исходной строки с завершающим нулем.
			strcat_s(text, _countof(text), " ");
		}
		strcat_s(text, _countof(text), "\0");
		hFile = CreateFile(name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);// имя файла, режим доступа, совместный доступ
		 // SD (дескр. защиты), как действовать, атрибуты файла, дескр.шаблона файла
		WriteFile(hFile, text, _countof(text), &result, NULL); // дескриптор файла, буфер данных, число байтов для записи
		// число записанных байтов, асинхронный буфер
		CloseHandle(hFile); //Закрывает дескриптор открытого объекта.

		hFile = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(hFile, text, _countof(text), 0, NULL);
		CloseHandle(hFile);


		for (int i = 0; i < 1999; i++)
		{
			if ('0' <= text[count] and text[count] <= '9')
			{
				do {
					tempchar = text[count];
					arr2[arrcount] = arr2[arrcount] * 10 + atoi(&tempchar);
					count++;
				} while ('0' <= text[count] and text[count] <= '9');
				arrcount++;

			}
			else
				count++;
		}// цикл, отсчитывающий количество чисел
		sprintf(buf, "Первый эелемент = %d, второй = %d, третий = %d", arr2[0], arr2[1], arr2[2]);
		MessageBox(hWnd, buf, "Проверка", MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}
