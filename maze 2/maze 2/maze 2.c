#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define BACKGROUND_WHITE (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)
#define CLEAR() printf("\033[H\033[J")
#define GOTOXY(x,y) printf("\033[%d;%dH", (y), (x))


#define MAP_SIZE 32			// Размер карты
#define DEBUG 00			// Режим исправления багов
#define MAP_FROM_FILE 0	// Режим чтения карты из файла
#define MAX_SIZE 32			// Максимальный размер карты (используется только при чтениии карты из файла)
#define RANDOMIZE_MAP 1		// Режим рандомизации карты
#define OBSTACLE_CHANCE 20	// Шанс появления препятсвия

HANDLE consoleHandle; // Дескриптор консоли для управления цветом

// Карта с препятствиями и путями
int Map[MAX_SIZE][MAX_SIZE] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};


// Карта пути от старта до финиша
int MapPath[MAP_SIZE][MAP_SIZE];

// Координаты начала и конца
int StartX = 31, StartY = 31, FinishX = 0, FinishY = 0;


int len(int num) {
	int count = 0;

	// Проверка отрицательного числа
	if (num < 0) {
		num *= -1;
	}

	// Цикл для подсчета цифр
	while (num > 0) {
		num /= 10;
		count++;
	}

	return count;
}

// Функция для вывода карты в консоль
void printMap() {
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			if (Map[x][y] == 1) { // Печать символа "S" для начальной точки
				SetConsoleTextAttribute(consoleHandle, 0);
				SetConsoleTextAttribute(consoleHandle, BACKGROUND_GREEN);
				printf("S ");
				SetConsoleTextAttribute(consoleHandle, 0);
			}
			else if (y == FinishX && x == FinishY) { // Печать символа "F" для конечной точки
				SetConsoleTextAttribute(consoleHandle, 0);
				SetConsoleTextAttribute(consoleHandle, BACKGROUND_GREEN);
				printf("F ");
				SetConsoleTextAttribute(consoleHandle, 0);
			}
			else if (Map[x][y] == 0) { // Печать пустой ячейки
				SetConsoleTextAttribute(consoleHandle, 0);
				SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
				printf("%c%c", 219, 219); // ░
				SetConsoleTextAttribute(consoleHandle, 0);
			}
			else if (Map[x][y] == -1) { // Печать препятствия
				SetConsoleTextAttribute(consoleHandle, 0);
				SetConsoleTextAttribute(consoleHandle, FOREGROUND_WHITE);
				printf("%c%c", 219, 219); // █
				SetConsoleTextAttribute(consoleHandle, 0);
			}
			else { // Печать числа для остальных ячеек
				SetConsoleTextAttribute(consoleHandle, 0);
				SetConsoleTextAttribute(consoleHandle, BACKGROUND_GREEN);
				if (len(Map[x][y]) == 1)printf("%d ", Map[x][y]);
				else printf("%d", Map[x][y]);
				SetConsoleTextAttribute(consoleHandle, 0);
			}
		}
		printf("\n");
	}
	printf("\n");
	SetConsoleTextAttribute(consoleHandle, 0);
	SetConsoleTextAttribute(consoleHandle, FOREGROUND_WHITE);
}

// Функция для вывода карты путей в консоль (без символов "S" и "F")
void printMap_raw() {
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			printf("%d\t", Map[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}

// Функция для вывода карты пути в консоль (без символов "S" и "F")
void printMapPath() {
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			if (MapPath[x][y] == 1) { // Печать символа "S" для начальной точки
				SetConsoleTextAttribute(consoleHandle, 0);
				SetConsoleTextAttribute(consoleHandle, BACKGROUND_GREEN);
				printf("S ");
				SetConsoleTextAttribute(consoleHandle, 0);
			}
			else if (y == FinishX && x == FinishY) { // Печать символа "F" для конечной точки
				SetConsoleTextAttribute(consoleHandle, 0);
				SetConsoleTextAttribute(consoleHandle, BACKGROUND_GREEN);
				printf("F ");
				SetConsoleTextAttribute(consoleHandle, 0);
			}
			else if (MapPath[x][y] == 0) { // Печать пустой ячейки
				SetConsoleTextAttribute(consoleHandle, 0);
				SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
				printf("%c%c", 219, 219); // ░
				SetConsoleTextAttribute(consoleHandle, 0);
			}
			else if (MapPath[x][y] == -1) { // Печать препятствия
				SetConsoleTextAttribute(consoleHandle, 0);
				SetConsoleTextAttribute(consoleHandle, FOREGROUND_WHITE);
				printf("%c%c", 219, 219); // █
				SetConsoleTextAttribute(consoleHandle, 0);
			}
			else { // Печать числа для остальных ячеек
				SetConsoleTextAttribute(consoleHandle, 0);
				SetConsoleTextAttribute(consoleHandle, BACKGROUND_GREEN);
				if (len(Map[x][y]) == 1)printf("%d ", Map[x][y]);
				else printf("%d", Map[x][y]);
				SetConsoleTextAttribute(consoleHandle, 0);
			}
		}
		printf("\n");
	}
	printf("\n");
	SetConsoleTextAttribute(consoleHandle, 0);
	SetConsoleTextAttribute(consoleHandle, FOREGROUND_WHITE);
}

// Функция для вывода карты пути в консоль (с символами "S" и "F")
void printMapPath_raw() {
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			printf("%d\t", MapPath[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}

void fillMap(int Map[MAP_SIZE][MAP_SIZE]) {
	srand(time(NULL)); // Инициализация генератора случайных чисел

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			// Генерация случайного числа от 0 до 99
			int random_number = rand() % 100;
			if (random_number < OBSTACLE_CHANCE) { // 50% вероятность
				Map[i][j] = -1;
			}
			else {
				Map[i][j] = 0;
			}
		}
	}
}


// Главная функция
int main() {
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем дескриптор консоли
	if (consoleHandle == INVALID_HANDLE_VALUE) { // Проверяем, был ли успешным получение дескриптора консоли
		printf("Something went wrong with handle");
	}

	if (MAP_FROM_FILE) {

		FILE* file = fopen("data.txt", "r");

		if (file == NULL) {
			printf("Error opening the file\n");
			return 1;
		}

		int used_space;
		fscanf(file, "%d", &used_space);
		fscanf(file, "%d %d %d %d", &StartX, &StartY, &FinishX, &FinishY);

		for (int i = 0; i < MAX_SIZE; i++) {
			for (int j = 0; j < MAX_SIZE; j++) {
				Map[i][j] = 0;
			}
		}

		int x, y;
		while (fscanf(file, "%d %d", &x, &y) != EOF) {
			if (x >= 0 && x < used_space && y >= 0 && y < used_space) {
				Map[y][x] = -1; // Mark obstacles with -1
			}
		}

		// Close the file
		fclose(file);

		// Mark all unused cells of the array outside of rows and cols as -1
		for (int i = used_space; i < MAX_SIZE; i++) {
			for (int j = 0; j < MAX_SIZE; j++) {
				Map[i][j] = -1; // Mark unused cells as -1
			}
		}
		for (int j = used_space; j < MAX_SIZE; j++) {
			for (int i = 0; i < used_space; i++) {
				Map[i][j] = -1; // Mark unused cells as -1
			}
		}
	}

	if (RANDOMIZE_MAP && !MAP_FROM_FILE) {
		fillMap(Map);
		StartX = rand() % MAP_SIZE;
		StartY = rand() % MAP_SIZE;
		FinishX = rand() % MAP_SIZE;
		FinishY = rand() % MAP_SIZE;
		Map[FinishY][FinishX] = 0;
		/*
		StartX = -1; StartY = -1; FinishX = -1; FinishY = -1;
		while (StartX == -1 && StartY == -1) {
			int randSX = (rand() * (mapSize - 1)) / RAND_MAX, randSY = (rand() * (mapSize - 1)) / RAND_MAX;
			if (Map[randSX][randSY] != -1) {
				StartX = randSX;
				StartY = randSY;
				//Map[StartX][StartY] = 1;
			}
		}
		while (FinishX == -1 && FinishY == -1) {
			int randFX = (rand() * (mapSize - 1)) / RAND_MAX, randFY = (rand() * (mapSize - 1)) / RAND_MAX;
			if (Map[randFX][randFY] != -1 && Map[randFX][randFY] != Map[StartX][StartY]) {
				FinishX = randFX;
				FinishY = randFY;
			}
		}*/

	}
	// Инициализация карты пути
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (Map[i][j] == -1) MapPath[i][j] = -1;
			else MapPath[i][j] = 0;
		}
	}

	//while (DEBUG);
	Map[StartY][StartX] = 1; // Установка начальной точки на карте
	if (DEBUG)printMap_raw(); // Вывод исходной карты в консоль (без пути)
	printMap(); // Вывод исходной карты в консоль (с начальной и конечной точками)

	int path = 1;
	// Выполнение волнового алгоритма до достижения конечной точки
	while (Map[FinishY][FinishX] == 0) {
		for (int x = 0; x < MAP_SIZE; x++) {
			for (int y = 0; y < MAP_SIZE; y++) {
				if (Map[x][y] == path) {
					// Обновление путей для соседних ячеек
					if (x + 1 < MAP_SIZE && y - 1 >= 0 && Map[x + 1][y - 1] == 0) Map[x + 1][y - 1] = path + 1;
					if (x + 1 < MAP_SIZE && y + 1 < MAP_SIZE && Map[x + 1][y + 1] == 0) Map[x + 1][y + 1] = path + 1;
					if (x - 1 >= 0 && y - 1 >= 0 && Map[x - 1][y - 1] == 0) Map[x - 1][y - 1] = path + 1;
					if (x - 1 >= 0 && y + 1 < MAP_SIZE && Map[x - 1][y + 1] == 0) Map[x - 1][y + 1] = path + 1;

					if (y - 1 >= 0 && Map[x][y - 1] == 0) Map[x][y - 1] = path + 1;
					if (y + 1 < MAP_SIZE && Map[x][y + 1] == 0) Map[x][y + 1] = path + 1;
					if (x + 1 < MAP_SIZE && Map[x + 1][y] == 0) Map[x + 1][y] = path + 1;
					if (x - 1 >= 0 && Map[x - 1][y] == 0) Map[x - 1][y] = path + 1;
				}
			}
		}
		path++;
	}

	if (DEBUG)printMap(); // Вывод карты с путем
	if (DEBUG)printMap_raw(); // Вывод карты путей в консоль (без символов "S" и "F")

	int currentX = FinishY, currentY = FinishX;
	int minValue = Map[FinishY][FinishX];
	if (DEBUG)printf("\n%d\t\t%d\t%d\n", minValue, currentX, currentY);
	int minX, minY;

	MapPath[FinishY][FinishX] = minValue;
	MapPath[StartY][StartX] = 1;
	char flag = 0;
	// Построение пути от финиша к старту
	while (MapPath[currentX][currentY] != 2) {
		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				if (currentX + dx >= 0 && currentX + dx < MAP_SIZE && currentY + dy >= 0 && currentY + dy < MAP_SIZE) {
					if (Map[currentX + dx][currentY + dy] < minValue && Map[currentX + dx][currentY + dy] > 0) {
						minValue = Map[currentX + dx][currentY + dy];
						minX = currentX + dx;
						minY = currentY + dy;
						flag = 1;
					}
				}
			}
		}
		if (flag) {
			currentX = minX;
			currentY = minY;
			MapPath[currentX][currentY] = minValue;
			flag = 0;
		}
		else {
			SetConsoleTextAttribute(consoleHandle, 0);
			SetConsoleTextAttribute(consoleHandle, BACKGROUND_RED | FOREGROUND_WHITE);
			printf("\nNo possible paths\n");
			SetConsoleTextAttribute(consoleHandle, 0);
			SetConsoleTextAttribute(consoleHandle, FOREGROUND_WHITE);
			printMap_raw();
			printMapPath_raw();
			return;
		}
	}
	if (DEBUG)printMapPath_raw(); // Вывод карты пути в консоль (без символов "S" и "F")
	printMapPath(); // Вывод карты пути в консоль (с начальной и конечной точками)
	Sleep(10000);
	CLEAR();
	printf("\n");
	for (int i = 0; i < path; i++) {
		Sleep(1000);
		CLEAR();
		SetConsoleTextAttribute(consoleHandle, 0);
		SetConsoleTextAttribute(consoleHandle, FOREGROUND_WHITE);
		for (int x = 0; x < MAP_SIZE; x++) {
			for (int y = 0; y < MAP_SIZE; y++) {
				if (MapPath[x][y] == 1) { // Печать символа "S" для начальной точки
					SetConsoleTextAttribute(consoleHandle, 0);
					SetConsoleTextAttribute(consoleHandle, BACKGROUND_GREEN);
					printf("S ");
					SetConsoleTextAttribute(consoleHandle, 0);
				}
				else if (y == FinishX && x == FinishY) { // Печать символа "F" для конечной точки
					SetConsoleTextAttribute(consoleHandle, 0);
					SetConsoleTextAttribute(consoleHandle, BACKGROUND_GREEN);
					printf("F ");
					SetConsoleTextAttribute(consoleHandle, 0);
				}
				else if (MapPath[x][y] == 0) { // Печать пустой ячейки
					SetConsoleTextAttribute(consoleHandle, 0);
					SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
					printf("%c%c", 219, 219); // ░
					SetConsoleTextAttribute(consoleHandle, 0);
				}
				else if (MapPath[x][y] == -1) { // Печать препятствия
					SetConsoleTextAttribute(consoleHandle, 0);
					SetConsoleTextAttribute(consoleHandle, FOREGROUND_WHITE);
					printf("%c%c", 219, 219); // █
					SetConsoleTextAttribute(consoleHandle, 0);
				}
				else if (MapPath[x][y] <= i) { // Печать пути
					SetConsoleTextAttribute(consoleHandle, 0);
					SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_RED);
					printf("%c%c", 219, 219); // █
					SetConsoleTextAttribute(consoleHandle, 0);
				}
				else { // Печать числа для остальных ячеек
					SetConsoleTextAttribute(consoleHandle, 0);
					SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
					printf("%c%c", 219, 219); // ░
					SetConsoleTextAttribute(consoleHandle, 0);
				}
			}
			printf("\n");
		}

	}
}
