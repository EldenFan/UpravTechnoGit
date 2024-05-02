import controlP5.*;

final String path = "C:/Users/Денис/source/repos/maze 2/maze 2";

int maxGridSize = 600; // максимальный размер сетки
int minCellSize = 18; // минимальный размер каждой клетки
int maxRows = 32; // максимальное количество строк, учитывая ограничение по размеру
int maxCols = 32; // максимальное количество столбцов, учитывая ограничение по размеру
int cellSize; // размер каждой клетки
int rows = 8; // начальное количество строк
int cols = 8; // начальное количество столбцов

ControlP5 cp5;
Slider slider;
Button grayButton, whiteButton, greenButton, blueButton; // Добавлены кнопки выбора цвета
Button printButton; // Добавлена кнопка для вывода массива
boolean grayFlag = false, whiteFlag = false, greenFlag = false, blueFlag = false; // Флаги для кнопок выбора цвета

int[][] grid; // массив сетки, использующий int
int greenCellX = -1, greenCellY = -1; // координаты текущей зеленой клетки
int blueCellX = -1, blueCellY = -1; // координаты текущей синей клетки

void setup() {
  size(600, 800);
  background(0);

  cellSize = max(min(width/cols, height/rows), minCellSize); // начальный размер клетки

  grid = new int[rows][cols]; // изменено на int

  cp5 = new ControlP5(this);
  slider = cp5.addSlider("slider")
    .setPosition(20, height - 120) // Перемещаем слайдер вверх, чтобы освободить место для кнопок
    .setSize(200, 20)
    .setRange(2, min(maxRows, maxCols)) // минимальное и максимальное количество строк и столбцов
    .setValue(rows)
    .setNumberOfTickMarks(min(maxRows, maxCols))
    .snapToTickMarks(true);

  // Добавляем кнопки выбора цвета
  grayButton = cp5.addButton("setGray")
    .setPosition(20, height - 90)
    .setSize(40, 40)
    .setColorBackground(color(150))
    .setLabel("Obstacle");

  whiteButton = cp5.addButton("setWhite")
    .setPosition(70, height - 90)
    .setSize(40, 40)
    .setColorBackground(color(255))
    .setLabel("Empty");

  greenButton = cp5.addButton("setGreen")
    .setPosition(120, height - 90)
    .setSize(40, 40)
    .setColorBackground(color(0, 255, 0))
    .setLabel("Start");

  blueButton = cp5.addButton("setBlue")
    .setPosition(170, height - 90)
    .setSize(40, 40)
    .setColorBackground(color(0, 0, 255))
    .setLabel("Finish");

  printButton = cp5.addButton("printMap")
    .setPosition(240, height - 90)
    .setSize(80, 40)
    .setLabel("Print Map");

  createGrid();
}

void draw() {
  fill(0);
  rect(0, 0, width, height);

  // Отображаем сетку
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] == -1) {
        fill(150); // серый цвет для заполненных клеток
      } else if (grid[i][j] == 0) {
        fill(255); // белый цвет для пустых клеток
      } else if (grid[i][j] == 1) {
        fill(0, 255, 0); // зелёный цвет для клеток со значением 1
      } else if (grid[i][j] == 2) {
        fill(0, 0, 255); // синий цвет для клеток со значением 2
      }
      rect(j * cellSize, i * cellSize, cellSize, cellSize);
    }
  }

  // Отображаем круг того цвета, флаг которого включен
  noStroke();
  if (grayFlag) {
    fill(150);
    circle(mouseX, mouseY, 10);
  } else if (whiteFlag) {
    fill(255);
    circle(mouseX, mouseY, 10);
  } else if (greenFlag) {
    fill(0, 255, 0);
    circle(mouseX, mouseY, 10);
  } else if (blueFlag) {
    fill(0, 0, 255);
    circle(mouseX, mouseY, 10);
  }
  stroke(0);
}

void createGrid() {
  // Создаем пустую сетку
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      grid[i][j] = 0;
    }
  }
}

void mousePressed() {
  // Изменяем цвет клетки по щелчку мыши
  int j = mouseX / cellSize;
  int i = mouseY / cellSize;

  if (i >= 0 && i < rows && j >= 0 && j < cols) {
    if (grayFlag) {
      grid[i][j] = -1;
      if (greenCellX == j && greenCellY == i) {
        greenCellX = -1;
        greenCellY = -1;
      }
      if (blueCellX == j && blueCellY == i) {
        blueCellX = -1;
        blueCellY = -1;
      }
    } else if (whiteFlag) {
      grid[i][j] = 0;
      if (greenCellX == j && greenCellY == i) {
        greenCellX = -1;
        greenCellY = -1;
      }
      if (blueCellX == j && blueCellY == i) {
        blueCellX = -1;
        blueCellY = -1;
      }
    } else if (greenFlag) {
      if (greenCellX != -1 && greenCellY != -1) {
        grid[greenCellY][greenCellX] = 0; // заменяем старую зеленую клетку на белую
      }
      grid[i][j] = 1;
      greenCellX = j;
      greenCellY = i;
      if (blueCellX == j && blueCellY == i) {
        blueCellX = -1;
        blueCellY = -1;
      }
    } else if (blueFlag) {
      if (blueCellX != -1 && blueCellY != -1) {
        grid[blueCellY][blueCellX] = 0; // заменяем старую синюю клетку на белую
      }
      grid[i][j] = 2;
      blueCellX = j;
      blueCellY = i;
      if (greenCellX == j && greenCellY == i) {
        greenCellX = -1;
        greenCellY = -1;
      }
    }
  }
}

void slider(int theValue) {
  // Изменяем размер сетки по изменению значения слайдера
  rows = theValue;
  cols = theValue;
  resizeGrid();
}

void resizeGrid() {
  // Проверяем, чтобы количество строк и столбцов было больше нуля
  if (rows > 0 && cols > 0) {
    // Изменяем размер сетки
    cellSize = max(min(width/cols, height/rows), minCellSize);
    grid = new int[rows][cols]; // изменено на int
    createGrid();
  }
}

// Функции для кнопок выбора цвета
void setGray() {
  grayFlag = true;
  whiteFlag = false;
  greenFlag = false;
  blueFlag = false;
}

void setWhite() {
  grayFlag = false;
  whiteFlag = true;
  greenFlag = false;
  blueFlag = false;
}

void setGreen() {
  grayFlag = false;
  whiteFlag = false;
  greenFlag = true;
  blueFlag = false;
}

void setBlue() {
  grayFlag = false;
  whiteFlag = false;
  greenFlag = false;
  blueFlag = true;
}

// Функция для кнопки вывода массива
void printMap() {
  // Открываем файл для записи
  PrintWriter writer = createWriter(path + "/data.txt");

  // Записываем размер массива и координаты старта и финиша
  writer.print(rows + " "); // Размер массива
  writer.print(greenCellX + " " + greenCellY + " "); // Координаты старта
  writer.print(blueCellX + " " + blueCellY + " "); // Координаты финиша

  // Записываем координаты препятствий
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] == -1) {
        writer.print(j + " " + i + " "); // Записываем координаты препятствия
      }
    }
  }

  // Закрываем файл
  writer.flush();
  writer.close();

  println("Data saved to data.txt");
}
