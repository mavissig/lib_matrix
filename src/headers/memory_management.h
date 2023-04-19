/**
 * @file memory_management.h
 * @brief В этом файле объявлены функции для работы с памятью
 */
#ifndef SRC_HEADERS_MEMORY_MANAGEMENT_H_
#define SRC_HEADERS_MEMORY_MANAGEMENT_H_

#include <stdlib.h>

#include "matrix_t.h"
#include "permitted.h"
#include "utils.h"

#define IS_NOT_NULL 0
#define IS_NULL 1

/**
 * @brief выделение памяти под матрицу
 *
 * @param rows количество строк
 * @param columns количество столбцов
 *
 * @return (double**) указатель на матрицу
 */
double **allocated_memory(const size_t rows, const size_t column);

#endif  // SRC_HEADERS_MEMORY_MANAGEMENT_H_