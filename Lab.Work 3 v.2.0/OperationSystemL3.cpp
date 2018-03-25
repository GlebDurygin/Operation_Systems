// OperationSystemL3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
using namespace std;
unsigned long N;

double SUM(double a, double b, HANDLE mail) {
	HANDLE sem3 = CreateSemaphore(NULL, 0, 1, L"mysem3");
	HANDLE sem2 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, L"mysem2");
	HANDLE mail1 = CreateFile(L"\\\\.\\mailslot\\myslot1", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	double ar[2] = { a,b };
	double c;
	WriteFile(mail1, &ar, sizeof(ar), &N, NULL);
	ReleaseSemaphore(sem2, 1, NULL);
	WaitForSingleObject(sem3, INFINITE);
	ReadFile(mail, &c, sizeof(c) + 1, &N, NULL);
	CloseHandle(sem3);
	CloseHandle(sem2);
	CloseHandle(mail1);
	return c;
}
double DIV(double a, double b, HANDLE mail) {
	HANDLE sem3 = CreateSemaphore(NULL, 0, 1, L"mysem5");
	HANDLE sem2 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, L"mysem4");
	HANDLE mail1 = CreateFile(L"\\\\.\\mailslot\\myslot2", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	double ar[2] = { a,b };
	double c;
	WriteFile(mail1, &ar, sizeof(ar), &N, NULL);
	ReleaseSemaphore(sem2, 1, NULL);
	WaitForSingleObject(sem3, INFINITE);
	ReadFile(mail, &c, sizeof(c) + 1, &N, NULL);
	CloseHandle(sem3);
	CloseHandle(sem2);
	CloseHandle(mail1);
	return c;
}
double MIN(double a, double b, HANDLE mail) {
	HANDLE sem3 = CreateSemaphore(NULL, 0, 1, L"mysem7");
	HANDLE sem2 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, L"mysem6");
	HANDLE mail1 = CreateFile(L"\\\\.\\mailslot\\myslot3", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	double ar[2] = { a,b };
	double c;
	WriteFile(mail1, &ar, sizeof(ar), &N, NULL);
	ReleaseSemaphore(sem2, 1, NULL);
	WaitForSingleObject(sem3, INFINITE);
	ReadFile(mail, &c, sizeof(c) + 1, &N, NULL);
	CloseHandle(sem3);
	CloseHandle(sem2);
	CloseHandle(mail1);
	return c;
}
double SQUAR(double a, HANDLE mail) {
	HANDLE sem3 = CreateSemaphore(NULL, 0, 1, L"mysem9");
	HANDLE sem2 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, L"mysem8");
	HANDLE mail1 = CreateFile(L"\\\\.\\mailslot\\myslot4", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	double c;
	WriteFile(mail1, &a, sizeof(a), &N, NULL);
	ReleaseSemaphore(sem2, 1, NULL);
	WaitForSingleObject(sem3, INFINITE);
	ReadFile(mail, &c, sizeof(c) + 1, &N, NULL);
	CloseHandle(sem3);
	CloseHandle(sem2);
	CloseHandle(mail1);
	return c;
}
int main() {
	setlocale(LC_ALL, "Russian");
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	double a[11]; // переменная для получения ответа
	double b[2];
	double c,d(0);
	int n;
	cout << "Вариант 3: независимые процессы, семафоры, почтовые ячейки, дисперсия." << endl;
	cout << "	Найти выборочную дисперсию для n чисел. (n<=10)"  << endl;
	HANDLE sem = CreateSemaphore(NULL, 0, 1, L"mysem1");
	HANDLE mail = CreateMailslot(L"\\\\.\\mailslot\\myslots", 0, MAILSLOT_WAIT_FOREVER, NULL);
	ZeroMemory(&si, sizeof(STARTUPINFO));
	CreateProcess(L"C:\\Users\\Tatyana\\Desktop\\все\\3 курс\\Операционные системы\\Лаба3\\OperSys\\OperationSystemL3_1\\Debug\\OperationSystemL3_1.exe", L"", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	CreateProcess(L"C:\\Users\\Tatyana\\Desktop\\все\\3 курс\\Операционные системы\\Лаба3\\OperSys\\OperationSystemL3_2\\Debug\\OperationSystemL3_2.exe", L"", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	CreateProcess(L"C:\\Users\\Tatyana\\Desktop\\все\\3 курс\\Операционные системы\\Лаба3\\OperSys\\OperationSystemL3_3\\Debug\\OperationSystemL3_3.exe", L"", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	CreateProcess(L"C:\\Users\\Tatyana\\Desktop\\все\\3 курс\\Операционные системы\\Лаба3\\OperSys\\OperationSystemL3_4\\Debug\\OperationSystemL3_4.exe", L"", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	CreateProcess(L"C:\\Users\\Tatyana\\Desktop\\все\\3 курс\\Операционные системы\\Лаба3\\OperSys\\OperationSystemL3_5\\Debug\\OperationSystemL3_5.exe", L"", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
//   Файл для внесения данных
	WaitForSingleObject(sem, INFINITE);
	ReadFile(mail, &a, sizeof(a)+1, &N, NULL);

	n = a[10]; //кол-во элементов
	for (int i = 0; i < n - 1; i++) {
		if (i==0) c = SUM(a[0], a[1], mail);
		else {
			c = SUM(c, a[i+1], mail);
		}
	}
	c = DIV(c, n, mail);
	for (int i = 0; i < n; i++) {
		d = d + SQUAR(MIN(a[i], c, mail), mail);
	}
	d = DIV(d, 2, mail);
	cout << "Ответ: Выборочная дисперсия равна = " << d << endl;
	CloseHandle(mail);
	CloseHandle(sem);
	system("pause");
	return 0;
}


