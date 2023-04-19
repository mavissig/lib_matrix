/**
 * @file memory_management.h
 * @brief В этом файле описаны определения функций для работы с памятью
 */
#include "../headers/memory_management.h"

double **allocated_memory(const size_t rows, const size_t columns) {
  double **buf = (double **)calloc(rows, sizeof(double *));
  if (NULL != buf) {
    for (size_t i = 0; i < rows; i++) {
      buf[i] = (double *)calloc(columns, sizeof(double));
    }
  }
  return buf;
}
