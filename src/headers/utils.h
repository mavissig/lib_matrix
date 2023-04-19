/**
 * @file utils.h
 * @brief В этом файле объявлены утилитарные структуры и функции
 */
#ifndef SRC_HEADERS_UTILS_H_
#define SRC_HEADERS_UTILS_H_

#define FALSE 0
#define TRUE 1
#define NULL ((void*)0)

#define ONE_MATRIX 10
#define MINOR_MATRIX 11
#define TRANSP_MATRIX 12
#define MULT_MATRIX 21
#define RETVAL_2 22
#define RETVAL_3 23

typedef unsigned long int size_t;

/**
 * @brief статус выполнения для функции сравнения(eq_matrix)
 *
 * @param FAILURE (int 0) Ошибка или матрицы не равны;
 * @param SUCCESS (int 1) Матрицы равны;
 */
typedef enum { FAILURE, SUCCESS } eq_matrix_status;

/**
 * @brief статус выполнения всех функций, кроме сравнения(eq_matrix)
 *
 * @param OK (int 0) Выполнено без ошибок
 * @param ERROR_INCORRECT_MATRIX (int 1) Ошибка, некорректная матрица
 * @param ERROR_CALCULATION (int 2) Ошибка вычисления
 */
typedef enum { OK, ERROR_INCORRECT_MATRIX, ERROR_CALCULATION } matrix_status;

#endif  // SRC_HEADERS_UTILS_H_