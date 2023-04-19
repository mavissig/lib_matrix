/**
 * @file matrix.h
 * @author mavissig (tg: @senior_stepik)
 * @brief В этом файле объявлены основные функции библиотеки matrix
 * @version 0.1
 * @date 2023-03-23
 * @copyright Copyright (c) 2023
 */
#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include "headers/matrix_t.h"
#include "headers/memory_management.h"
#include "headers/permitted.h"
#include "headers/utils.h"

/**
 * @brief функция для создания матрицы с заданными параметрами
 *
 * @param [in]rows строки
 * @param [in]columns столбцы
 * @param [out]result структура матрицы
 *
 * @return (int) статус выполнения функции
 *
 * @retval 0 - OK
 * @retval 1 - Ошибка, некорректная матрица
 * @retval 2 - Ошибка вычисления
 */
int create_matrix(int rows, int columns, matrix_t *result);

/**
 * @brief функция для удаления матрицы
 * @param A - матрица которую нужно удалить из структуры
 */
void remove_matrix(matrix_t *A);

/**
 * @brief сравнивает матрицы
 *
 * @param A первая матрица
 * @param B вторая матрица
 * @return int
 * @retval SUCCESS - если матрицы равны
 * @retval FAILURE - если матрицы не равны или ошибка
 */
int eq_matrix(matrix_t *A, matrix_t *B);

/**
 * @brief сложение матриц
 *
 * @param A первая матрица
 * @param B вторая матрица
 * @param result матрица после сложения
 * @return int
 * @retval 0 - OK
 * @retval 1 - Ошибка, некорректная матрица
 * @retval 2 - Ошибка вычисления
 */
int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief вычетание матриц
 *
 * @param A первая матрица
 * @param B вторая матрица
 * @param result матрица после вычетания
 * @return int
 * @retval 0 - OK
 * @retval 1 - Ошибка, некорректная матрица
 * @retval 2 - Ошибка вычисления
 */
int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief умножение матрицы на число
 *
 * @param A матрица которую будем умножать
 * @param number число на которое умножаем
 * @param result матрица после умножения
 * @return int
 * @retval 0 - OK
 * @retval 1 - Ошибка, некорректная матрица
 * @retval 2 - Ошибка вычисления
 */
int mult_number(matrix_t *A, double number, matrix_t *result);

/**
 * @brief умножение матрицы A на матрицу B
 *
 * @param A матрица которую будем умножать
 * @param B матрица на которую будем умножать
 * @param result матрица после умножения
 * @return int
 * @retval 0 - OK
 * @retval 1 - Ошибка, некорректная матрица
 * @retval 2 - Ошибка вычисления
 */
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief транспонирование матрицы А
 *
 * @param A матрица которую будем транспонировать
 * @param result матрица после транспонирования
 * @return int
 * @retval 0 - OK
 * @retval 1 - Ошибка, некорректная матрица
 * @retval 2 - Ошибка вычисления
 */
int transpose(matrix_t *A, matrix_t *result);

/**
 * @brief нахождение детерминанта матрицы A
 *
 * @param A матрица детерминант которой считаем
 * @param result (double)детерминант матрицы A
 * @return int
 * @retval 0 - OK
 * @retval 1 - Ошибка, некорректная матрица
 * @retval 2 - Ошибка вычисления
 */
int determinant(matrix_t *A, double *result);

/**
 * @brief нахождение минора матрицы и матрицы алгебраических дополнений
 *
 * @param A исходная матрица
 * @param result ма трица после вычислений
 * @return int
 * @retval 0 - OK
 * @retval 1 - Ошибка, некорректная матрица
 * @retval 2 - Ошибка вычисления
 */
int calc_complements(matrix_t *A, matrix_t *result);

/**
 * @brief нахождение обратной матрицы
 *
 * @param A
 * @param result
 * @return
 */
int inverse_matrix(matrix_t *A, matrix_t *result);

#endif  // SRC_MATRIX_H_