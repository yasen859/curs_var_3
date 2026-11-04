//Преобразовать двумерный массив таким образом, чтобы сначала располагались все элементы в
//столбце, отличающиеся от максимального элемента более чем на 20 %, а потом — все остальные.
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>


int main() {
	setlocale(LC_ALL, ".UTF8");
	int rows, cols, i, j, c;
	int mat[10][10]; //исх массив
	int mat2[10][10];//преобразованный массив
	int res = 0;// сколько элементов уже положили в result
	int result[100]; //массив для хранения результатов преобразования

	printf("*************************************************************************************\n");
	printf("*                                                                                   *\n");
	printf("*    Курсовой проект по дисциплине: Основы программирования и алгоритмизации        *\n");
	printf("*                  Тема: Реализация динамического многомерного массива              *\n");
	printf("*                        Выполнил: Балнов А.А., группа бОТИ-262                     *\n");
	printf("*                                                                                   *\n");
	printf("*************************************************************************************\n");
	printf("\n");
	printf("\n");

	printf("*Программа преобразует двумерный массив таким образом, чтобы сначала располагались все элементы встолбце, отличающиеся от максимального элемента более чем на 20 %, а потом — все остальные.\n");
	printf("\n");

	printf("Введите колличество строк (макс 10): \n");
	scanf_s("%d", &rows);
	printf("Введите колличество столбцов (макс 10): \n");
	scanf_s("%d", &cols);

	printf("\n");


	printf("Как вы хотите заполнить массив: \n1 - Вручную\n2 - Случайным образом\n");
	scanf_s("%d", &c);

	srand(time(NULL));

	if (c == 1) {
		for (i = 0; i < rows; i++) {
			for (j = 0; j < cols; j++) {
				printf("Элемент [%d][%d]: ", i, j);
				scanf_s("%d", &mat[i][j]);
			}

		}
	}
	else {
		printf("Cгенерированная маcсив:\n");
		for (i = 0; i < rows; i++) {
			for (j = 0; j < cols; j++) {
				mat[i][j] = rand() % 100;
				printf("%d\t", mat[i][j]);
			}
			printf("\n");
		}
	}
	//нахождение максимума в столбцах
	int max[10];
	for (j = 0; j < cols; j++) {
		int current_max = -1;
		for (i = 0; i < rows; i++) {
			if (mat[i][j] > current_max) {
				current_max = mat[i][j];
			}
		}
		max[j] = current_max;
	}


	//нахождение элементов  оличаются от макс столбца более чем на 20%
	// элемнт < макс * 0.8
	for (j = 0; j < cols; j++) {
		for (i = 0; i < rows; i++) {
			if (mat[i][j] * 10 < max[j] * 8) {
				result[res] = mat[i][j];
				res++;

			}
		}

	}


	//нахлждение остальных элементов
	for (j = 0; j < cols; j++) {
		for (i = 0; i < rows; i++) {
			if (mat[i][j] * 10 >= max[j] * 8) {
				result[res] = mat[i][j];
				res++;
			}
		}

	}
	int res_c = cols;
	int res_r = (res + res_c - 1) / res_c;


	for (i = 0; i < res; i++) {
		int a = i / res_c;
		int b = i % res_c;
		mat2[a][b] = result[i];
	}

	printf("\nПреобразованный массив:\n");
	for (i = 0; i < res_r; i++) {
		for (j = 0; j < res_c; j++) {
			int index = i * res_c + j;
			printf("%d\t ", mat2[i][j]);
		}
		printf("\n");
	}


	return 0;
}