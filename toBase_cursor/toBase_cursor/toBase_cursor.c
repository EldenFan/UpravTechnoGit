#include <stdio.h>

#define print printf
#define scanf scanf_s

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

/*
Как работают макросы clear() и gotoxy()?
Макрос clear():

\033 - это код ASCII для символа "ESC".
H - это код управления курсором, который перемещает курсор в верхний левый угол экрана.
[J - это код управления курсором, который очищает экран от всех символов.
Макрос gotoxy(x, y):

\033 - это код ASCII для символа "ESC".
[%d;%dH - это код управления курсором, который перемещает курсор в заданную позицию (x, y) на экране.
%d - это спецификатор форматирования, который заменяется на значение x.
; - это разделитель между координатами x и y.
H - это код управления курсором, который перемещает курсор в заданную строку.
*/

void toBase(int num, int base) {
	printf("Number %d in decimal\nto %d base\n", num, base);

	int cnt = 0;
	int cntNum = num;
StartCycle:
	cntNum /= base;
	cnt++;
	if (cntNum > 0)goto StartCycle;
	int x = cnt * 3;

StartCycle2:
	gotoxy(x - 2, 3);
	printf("%d", num % base);
	num /= base;
	x -= 3;
	if (num > 0)goto StartCycle2;

	gotoxy(0, 4);
	return;

}

int main(void) {

	int _num, _base;

mainCycle:
	scanf("%d %d", &_num, &_base);
	clear();
	if ((_base > 1 && _base <= 50) && (_num >= 0 && _num <= 1000000))toBase(_num, _base);
	else print("Wrong enter...\n Number must be 0 or above, and 1'000'000 or below\n Base must be 2 or above, and 50 or below\n");


	goto mainCycle;


}
