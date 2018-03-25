// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h> 
#include <iostream> 

int b[7] = { -1,2,3,1 ,2,3,-4 };
int n = 7;
int i = 0;
int main()
{
	setlocale(LC_ALL, "Russian");
	
	_asm {
		lea eax, b                    
		mov ebx, dword ptr[eax]
		mov ecx, dword ptr[n]
	oncemore:
		cmp ebx, 0                     
		jle addition                   
		add eax, 4                     
		mov ebx, dword ptr[eax]        
		loop oncemore                  
		jmp fquit                     
	addition:
		inc i                       
		add eax, 4                    
		mov ebx, dword ptr[eax]       
		loop oncemore                  
	}	
fquit: 
	printf("Задание №8. Посчитать количество отрицательных чисел в массиве.\n");
	printf("Массив: ");
	for (int j=0; j < 7; j++) {
		printf("%d, ", b[j]);
	}
	printf("\nОтвет: Кол-во отрицательных чисел = %d", i);
	getchar();

	return 0;
}

