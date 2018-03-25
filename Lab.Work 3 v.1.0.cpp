// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <windows.h>
#include <string.h>

using namespace std;
DWORD N;
HANDLE Hfile;
HANDLE Hres, Hres1, Hres2, Hres3;
HANDLE Hres4;
HANDLE map;
long j(0);

void Thread_0 (HANDLE map) {
	HANDLE hMut = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutexMain");
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutex0");
	while (1) {
		WaitForSingleObject(hMutex, INFINITE);
		HANDLE ma = CreateFileMapping(Hres, 0, PAGE_READONLY, 0, 0, NULL);
		double *t = (double *)MapViewOfFile(ma, FILE_MAP_READ, 0, 0, 0);
		double x = t[0] * t[1];
		WriteFile(Hfile, &x, sizeof(x), &N, NULL);
		ReleaseMutex(hMutex);
	}
}
void Thread_1(HANDLE map) {
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutexMain");
	HANDLE hMut = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutex3");
	while (1) {
		WaitForSingleObject(hMutex, INFINITE);
		HANDLE ma = CreateFileMapping(Hres1, 0, PAGE_READONLY, 0, 0, NULL);
		double *t = (double *)MapViewOfFile(ma, FILE_MAP_READ, 0, 0, 0);
		double x = t[0] - t[1];
		WriteFile(Hfile, &x, sizeof(x), &N, NULL);
		ReleaseMutex(hMut);
	}
}
void Thread_2(HANDLE map) {
	HANDLE hMut = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutexMain");
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutex2");
	while (1) {
		WaitForSingleObject(hMutex, INFINITE);
		HANDLE ma = CreateFileMapping(Hres2, 0, PAGE_READONLY, 0, 0, NULL);
		double *t = (double *)MapViewOfFile(ma, FILE_MAP_READ, 0, 0, 0);
		double x = t[0] + t[1];
		WriteFile(Hfile, &x, sizeof(x), &N, NULL);
		ReleaseMutex(hMutex);
	}
}
void Thread_3(HANDLE map) {
	HANDLE hMut = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutexMain");
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutex3");
	while (1) {
		WaitForSingleObject(hMutex, INFINITE);
		HANDLE ma = CreateFileMapping(Hres3, 0, PAGE_READONLY, 0, 0, NULL);
		double *t = (double *)MapViewOfFile(ma, FILE_MAP_READ, 0, 0, 0);
		double x = sqrt(t[0]);
		WriteFile(Hfile, &x, sizeof(x), &N, NULL);
		ReleaseMutex(hMutex);
	}
}
void Thread_4(HANDLE map) {
	HANDLE hMut = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutexMain");
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutex4");
	while (1) {
		WaitForSingleObject(hMutex, INFINITE);
		HANDLE ma = CreateFileMapping(Hres4, 0, PAGE_READONLY, 0, 0, NULL);
		double *t = (double *)MapViewOfFile(ma, FILE_MAP_READ, 0, 0, 0);
		double x = t[0] / t[1];
		WriteFile(Hfile, &x, sizeof(x), &N, NULL);
		ReleaseMutex(hMutex);
	}
}
//void Thread_5(HANDLE map) {
//	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutex5");
//	WaitForSingleObject(hMutex, INFINITE);
//	HANDLE ma = CreateFileMapping(Hres, 0, PAGE_READONLY, 0, 0, NULL);
//	double *t = (double *)MapViewOfFile(ma, FILE_MAP_READ, 0, 0, 0);
//	double x = t[9] - t[10];
//	WriteFile(Hfile, &x, sizeof(x), &N, NULL);
//}
//void Thread_6(HANDLE map) {
//	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutex6");
//	WaitForSingleObject(hMutex, INFINITE);
//	HANDLE ma = CreateFileMapping(Hres, 0, PAGE_READONLY, 0, 0, NULL);
//	double *t = (double *)MapViewOfFile(ma, FILE_MAP_READ, 0, 0, 0);
//	double x = t[11] * t[12];
//	WriteFile(Hfile, &x, sizeof(x), &N, NULL);
//}
//void Thread_7(HANDLE map) {
//	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutex7");
//	WaitForSingleObject(hMutex, INFINITE);
//	HANDLE ma = CreateFileMapping(Hres, 0, PAGE_READONLY, 0, 0, NULL);
//	double *t = (double *)MapViewOfFile(ma, FILE_MAP_READ, 0, 0, 0);
//	double x = t[13] / t[14];
//	WriteFile(Hfile, &x, sizeof(x), &N, NULL);
//}
//void Thread_8(HANDLE map) {
//	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutex8");
//	WaitForSingleObject(hMutex, INFINITE);
//	HANDLE ma = CreateFileMapping(Hres, 0, PAGE_READONLY, 0, 0, NULL);
//	double *t = (double *)MapViewOfFile(ma, FILE_MAP_READ, 0, 0, 0);
//	double x = t[15] / t[16];
//	WriteFile(Hfile, &x, sizeof(x), &N, NULL);
//}

int main() {
	setlocale(LC_ALL, "Russian");
	HANDLE hThreads[5];
	HANDLE hMutexes[10];
	hMutexes[0] = CreateMutex(NULL, TRUE, L"mutex0");
	hMutexes[1] = CreateMutex(NULL, TRUE, L"mutex1");
	hMutexes[2] = CreateMutex(NULL, TRUE, L"mutex2");
	hMutexes[3] = CreateMutex(NULL, TRUE, L"mutex3");
	hMutexes[4] = CreateMutex(NULL, TRUE, L"mutex4");
	hMutexes[5] = CreateMutex(NULL, TRUE, L"mutexMain");
	hThreads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_0, &map, 0, NULL);
	hThreads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_1, &map, 0, NULL);
	hThreads[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_2, &map, 0, NULL);
	hThreads[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_3, &map, 0, NULL);
	hThreads[4] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_4, &map, 0, NULL);
	/*hThreads[5] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_5, &map, 0, NULL);
	hThreads[6] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_6, &map, 0, NULL);
	hThreads[7] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_7, &map, 0, NULL);
	hThreads[8] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_8, &map, 0, NULL);*/
	double a, b, c, x,y;

	cout << "Вариант 4" << endl << "	Задания:" << endl << "B - потоки одного процесса" << endl;
	cout << "F - мьютексы" << endl << "J - файлы, отображаемые в память" << endl << "K - квадратное уравнение"<< endl;
	cout << " Вид квадратного уравнения : ax^2+bx+c=0"<< endl;
	cout << "Введите a = ";
	cin >> a;
	cout << "Введите b = ";
	cin >> b;
	cout << "Введите c = ";
	cin >> c;
	Hfile = CreateFile(L"Laba3Va.dat", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
	Hres = CreateFile(L"Laba3V1.dat", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	Hres2 = CreateFile(L"Laba3V2.dat", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	Hres3 = CreateFile(L"Laba3V3.dat", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	Hres4 = CreateFile(L"Laba3V4.dat", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	Hres1 = CreateFile(L"Laba3V5.dat", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	map = CreateFileMapping(Hfile, 0, PAGE_READONLY, 0, 0, NULL);
	x = b*b;
	y = 4 * a*c;
	WriteFile(Hfile, &a, sizeof(a), &N, NULL);
	WriteFile(Hfile, &b, sizeof(b), &N, NULL);
	WriteFile(Hfile, &c, sizeof(c), &N, NULL);
	//for (int i = 0; i < 5; i++) {
		double *t = (double *)MapViewOfFile(map, FILE_MAP_READ, 0, 0, 0);
		//if (i == 0) {
			WriteFile(Hres1, &x, sizeof(x), &N, NULL);
			WriteFile(Hres1, &y, sizeof(y), &N, NULL);
			ReleaseMutex(hMutexes[5]);
			WaitForSingleObject(hMutexes[1], INFINITE);

			WriteFile(Hres3, &t[3], sizeof(t[3]), &N, NULL);
			ReleaseMutex(hMutexes[5]);
			WaitForSingleObject(hMutexes[5], INFINITE);

			x = -b;
			WriteFile(Hres2, &x, sizeof(x), &N, NULL);
			WriteFile(Hres2, &t[4], sizeof(t[4]), &N, NULL);
			ReleaseMutex(hMutexes[5]);
			WaitForSingleObject(hMutexes[2], INFINITE);

			x = t[5] - 2 * t[4];
			WriteFile(Hfile, &x, sizeof(x), &N, NULL);
			x = 2;
			WriteFile(Hres, &x, sizeof(x), &N, NULL);
			WriteFile(Hres, &a, sizeof(a), &N, NULL);
			ReleaseMutex(hMutexes[5]);
			WaitForSingleObject(hMutexes[0], INFINITE);

			WriteFile(Hres4, &t[5], sizeof(t[5]), &N, NULL);
			WriteFile(Hres4, &t[7], sizeof(t[7]), &N, NULL);
			ReleaseMutex(hMutexes[5]);
			WaitForSingleObject(hMutexes[4], INFINITE);
			x = t[6] / t[7];
			WriteFile(Hfile, &x, sizeof(x), &N, NULL);
	//	}
	//	if (i == 1) {
	//		WriteFile(Hres3, &t[3], sizeof(t[3]), &N, NULL);
	//		ReleaseMutex(hMutexes[3]);
	//		WaitForSingleObject(hMutexes[5], INFINITE);
	//	}
	//	if (i == 2) {
	//		x = -b;
	//		WriteFile(Hres2, &x, sizeof(x), &N, NULL);
	//		WriteFile(Hres2, &t[4], sizeof(t[4]), &N, NULL);
	//		ReleaseMutex(hMutexes[2]);
	//		WaitForSingleObject(hMutexes[5], INFINITE);
	//	}
	//	if (i == 3) {
	//		x = t[5] - 2 * t[4];
	//		WriteFile(Hfile, &x, sizeof(x), &N, NULL);
	//		x = 2;
	//		WriteFile(Hres, &x, sizeof(x), &N, NULL);
	//		WriteFile(Hres, &a, sizeof(a), &N, NULL);
	//		ReleaseMutex(hMutexes[0]);
	//		WaitForSingleObject(hMutexes[5], INFINITE);
	//	}
	//	if (i == 4) {
	//		WriteFile(Hres4, &t[5], sizeof(t[5]), &N, NULL);
	//		WriteFile(Hres4, &t[7], sizeof(t[7]), &N, NULL);
	//		ReleaseMutex(hMutexes[4]);
	//		WaitForSingleObject(hMutexes[5], INFINITE);
	//		x = t[6] / t[7];
	//		WriteFile(Hfile, &x, sizeof(x), &N, NULL);
	//	}
	//}
		//if (i == 5) {
		//	x = -b;
		//	WriteFile(Hres6, &(x), sizeof(x), &N, NULL);
		//	WriteFile(Hres6, &t[6], sizeof(t[6]), &N, NULL);
		//	ReleaseMutex(hMutexes[1]);
		//	WaitForSingleObject(hThreads[1], INFINITE);
		//}
		//if (i == 6) {
		//	x = 2;
		//	WriteFile(Hres7, &(x), sizeof(x), &N, NULL);
		//	WriteFile(Hres7, &a, sizeof(a), &N, NULL);
		//	ReleaseMutex(hMutexes[0]);
		//	WaitForSingleObject(hThreads[0], INFINITE);
		//}
		//if (i == 7) {
		//	WriteFile(Hres8, &(t[7]), sizeof(t[7]), &N, NULL);
		//	WriteFile(Hres8, &t[9], sizeof(t[9]), &N, NULL);
		//	ReleaseMutex(hMutexes[4]);
		//	WaitForSingleObject(hThreads[4], INFINITE);
		//}
		//if (i == 8) {
		//	WriteFile(Hres9, &(t[8]), sizeof(t[8]), &N, NULL);
		//	WriteFile(Hres9, &t[9], sizeof(t[9]), &N, NULL);
		//	ReleaseMutex(hMutexes[4]);
		//	WaitForSingleObject(hThreads[4], INFINITE);
		//}
	//}
//	map = CreateFileMapping(Hfile, 0, PAGE_READONLY, 0, 0, NULL);
//	double *t = (double *)MapViewOfFile(map, FILE_MAP_READ, 0, 0, 0);
	double re[13] = { t[0],t[1], t[2], t[3], t[4], t[5], t[6], t[7], t[8], t[9], t[10], t[11],t[12]};
	double result[6] = { t[0],t[1],t[2],t[8],t[9],t[3]};
	cout << "\nВведенные данные:" << endl;
	cout << "1) a = " << result[0] << endl;
	cout << "2) b = " << result[1] << endl;
	cout << "3) c = " << result[2] << endl;
	if (result[5]<0) cout << "\nОтвет: Корней нет, Дискриминант отрицательный"<< endl;
	else cout << "\nОтвет: " << "\nx1= " << result[3] << "\nx2= " << result[4] << endl;
	for (int i = 0; i < 5; i++) {
		CloseHandle(hThreads[i]);
	}
	//for (int i = 0; i < 10; i++) {
	//	CloseHandle(hMutexes[i]);
	//}
	CloseHandle(Hfile);
	CloseHandle(Hres);
	CloseHandle(map);
	CloseHandle(Hres1);
	CloseHandle(Hres2);
	CloseHandle(Hres3);
	CloseHandle(Hres4);
	system("pause");
}