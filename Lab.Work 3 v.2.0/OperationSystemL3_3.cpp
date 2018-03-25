// OperationSystemL3_3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
using namespace std;

int main() {
	unsigned long N; // Сколько записано
	setlocale(LC_ALL, "Russian");
	double n1;
	double x[2];
	HANDLE sem1 = CreateSemaphore(NULL, 0, 1, L"mysem4");
	HANDLE mail1 = CreateMailslot(L"\\\\.\\mailslot\\myslot2", 0, MAILSLOT_WAIT_FOREVER, NULL);
	while (1) {
		WaitForSingleObject(sem1, INFINITE);
		ReadFile(mail1, &x, sizeof(x) + 1, &N, NULL);
		n1 = x[0] / x[1];
		HANDLE sem3 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, L"mysem5");
		HANDLE mail = CreateFile(L"\\\\.\\mailslot\\myslots", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		WriteFile(mail, &n1, sizeof(n1), &N, NULL);
		ReleaseSemaphore(sem3, 1, NULL);
	}
	return 0;
}