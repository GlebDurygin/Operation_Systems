// OperationSystemL3_1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
using namespace std;

int main() {
	unsigned long N; // ������� ��������
	setlocale(LC_ALL, "Russian");
	double x[11], AverSelec(0);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	double n1 = 11;
	while (n1 > 10){
		cout << "������� n = ";
		cin >> n1;
		if (n1 > 10) cout << "n>10, ���������� ��� ���." << endl;
	}
	x[10] = n1;
	for (int i = 0; i < n1; i++) {
		cout << "������� x" << i + 1 << " = ";
		cin >> x[i];
	}
	
	HANDLE sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, L"mysem1");
	HANDLE mail = CreateFile(L"\\\\.\\mailslot\\myslots", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(mail, &x, sizeof(x), &N, NULL);
	ReleaseSemaphore(sem, 1, NULL);
	return 0;
}

