/**
 * @file permitted.h
 * @brief В этом файле объявлены функции для определения допустимых
 * и валидных значений
 */
#ifndef SRC_HEADERS_PERMITED_H_
#define SRC_HEADERS_PERMITED_H_

#include <math.h>
#include <stdarg.h>

#include "matrix_t.h"
#include "utils.h"

/**
 * @brief проверка указателя на NULL
 *
 * @param pointer проверяемый указатель
 *
 * @return int
 *
 * @retval 0 - pointer is NOT NULL
 * @retval 1 - pointer is NULL
 */
int check_null(const void *val);

/**
 * @brief проверка валидных параметров матрицы(строки, столбцы и проверка на
 * NULL)
 *
 * @param A проверяемая матрица
 * @return int
 * @retval 0 - NOT NULL и параметры > 0
 * @retval 1 - NULL или не валидные параметры
 */
int check_valid_matrix(const int index_functions, const matrix_t *M);

/**
 * @brief проверка матриц на валидность
 *
 * @attention параметр index_functions идентифицирует функцию по
 * передаваемому индексу:
 * @attention 22(RETVAL_2) - две матрицы, инвертированы возвращаемые значения(2
 * значения)
 * @attention 23(RETVAL_3) - вде матрицы с тремя возвращаемыми статусами
 *
 * @param count_args количество матриц подаваемых для проверки
 * @param index_functions индекс для идентификации проверяемых матриц
 * @param ... спиок проверяемых матриц
 * @return int
 */
int check_validation(const int count_args, const int index_functions, ...);

#endif  // SRC_HEADERS_PERMITED_H_