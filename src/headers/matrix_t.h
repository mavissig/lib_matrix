/**
 * @file matrix_t.h
 * @brief В этом файле объявлена основная структура матрицы
 */
#ifndef SRC_MATRIX_T_H_
#define SRC_MATRIX_T_H_

/**
 * @brief структура матрицы
 *
 * @param (double**)matrix матрица
 * @param (int)rows строки
 * @param (int)columns столбцы
 */
typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

#endif  // SRC_MATRIX_T_H_