//Преобразовать двумерный массив таким образом, чтобы сначала располагались все элементы в
//столбце, отличающиеся от максимального элемента более чем на 20 %, а потом — все остальные.
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>


// ввод размера массива, выделение памяти и его заполнение (вручную / случайным образом)
int* inputArray(int* rows, int* cols) {
	int i, j, choice;
	int* mat;

	printf("Введите колличество строк: \n");
	scanf_s("%d", rows); 

	printf("Введите колличество столбцов: \n");
	scanf_s("%d", cols);

	
	mat = (int*)malloc((*rows) * (*cols) * sizeof(int));
	if (mat == NULL) {
		puts("error");
		return NULL;
	}

	printf("\n");

	printf("Как вы хотите заполнить массив: \n1 - Вручную\n2 - Случайным образом\n3 - Взять данные из файла\n");
	scanf_s("%d", &choice);

	switch (choice) {
	case 1:
		for (i = 0; i < *rows; i++) {
			for (j = 0; j < *cols; j++) {
				printf("Элемент [%d][%d]: ", i, j);
				scanf_s("%d", &mat[i * (*cols) + j]); 
			}
		}
		break;

	case 2:
		srand(time(NULL));
		printf("Cгенерированная маcсив:\n");
		for (i = 0; i < *rows; i++) {
			for (j = 0; j < *cols; j++) {
				mat[i * (*cols) + j] = rand() % 100;
				printf("%d\t", mat[i * (*cols) + j]);
			}
			printf("\n");
		}
		break;
	}

	return mat;
}


// нахождение максимального элемента в каждом столбце
void findColumnMax(int* mat, int rows, int cols, int max[]) {
	int i, j;
	for (j = 0; j < cols; j++) {
		int current_max = mat[0 * cols + j];
		for (i = 1; i < rows; i++) {
			if (mat[i * cols + j] > current_max) {
				current_max = mat[i * cols + j];
			}
		}
		max[j] = current_max;
	}
}


// построение нового массива: сначала элементы < 80% от максимума, затем остальные
int buildTransformed(int* mat, int rows, int cols, int max[], int* mat2) {
	int i, j, res = 0;

	for (j = 0; j < cols; j++) {
		for (i = 0; i < rows; i++) {
			if (mat[i * cols + j] * 10 < max[j] * 8) {
				mat2[res / cols * cols + res % cols] = mat[i * cols + j];
				res++;
			}
		}
	}

	for (j = 0; j < cols; j++) {
		for (i = 0; i < rows; i++) {
			if (mat[i * cols + j] * 10 >= max[j] * 8) {
				mat2[res / cols * cols + res % cols] = mat[i * cols + j];
				res++;
			}
		}
	}
	return res;
}


// вывод преобразованного массива
void printTransformed(int* mat, int res, int res_c) {
	int i, j;
	int res_r = (res + res_c - 1) / res_c;

	for (i = 0; i < res_r; i++) {
		for (j = 0; j < res_c; j++) {
			int index = i * res_c + j;
			if (index < res)
				printf("%d\t ", mat[index]);
			else
				printf("\t ");
		}
		printf("\n");
	}
}


int main() {
	setlocale(LC_ALL, ".UTF8");
	int rows, cols, i, j, c, k;
	int* mat;    //исходный массив (динамический, одна строка)
	int* mat2;   //преобразованный массив (динамический, одна строка)
	int max[10]; //максимумы столбцов

	printf("*************************************************************************************\n");
	printf("*                                                                                   *\n");
	printf("*    Курсовой проект по дисциплине: Основы программирования и алгоритмизации        *\n");
	printf("*                  Тема: Реализация динамического многомерного массива              *\n");
	printf("*                        Выполнил: Балнов А.А., группа бОТИ-262                     *\n");
	printf("*                                                                                   *\n");
	printf("*************************************************************************************\n");
	printf("\n");
	printf("\n");

	printf("*Программа преобразует двумерный массив таким образом, чтобы сначала располагались все элементы встолбце,\nотличающиеся от максимального элемента более чем на 20%, а потом — все остальные.\n");
	printf("\n");

	printf("*Программа находит максиимальный элемент в какждом столбце и относитьльно его ищет эллементы меньше его на 20 %\nи перестраивает стлбец. Максимальные элементы могут быть выведены по желанию пользователя.  \n");

	do {
		// ввод массива
		mat = inputArray(&rows, &cols);
		if (mat == NULL) {
			return -1;
		}

		// выделение памяти под преобразованный массив
		mat2 = (int*)malloc(rows * cols * sizeof(int));
		if (mat2 == NULL) {
			puts("error");
			return -1;
		}

		// нахождение максимума, построение и вывод нового массива
		findColumnMax(mat, rows, cols, max);

		printf("Вывести максимум столбцов?(1 - Да, 0 - Нет):\n");
		scanf_s("%d", &k);
		if (k == 1) {
			printf("Максимум в столбцах: ");
			for (j = 0; j < cols; j++) {
				printf("%d ", max[j]);
			}
			printf("\n");
		}
		else
		{
			printf("\n");
		}


		{
			int res = buildTransformed(mat, rows, cols, max, mat2);
			int res_c = cols;

			printf("\nПреобразованный массив:\n");
			printTransformed(mat2, res, res_c);
		}

		free(mat);
		free(mat2);

		printf("Желаете начать заново? (1 - Да, 2 - Нет): ");
		scanf_s("%d", &c);
	} while (c == 1);
	return 0;
}

