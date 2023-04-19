/**
 * @file permitted.c
 * @brief В этом файле описаны определения функций для определения
 * допустимых и валидных значений
 */
#include "../headers/permitted.h"

int check_null(const void *pointer) { return (pointer == NULL); }

int check_valid_matrix(const int index_functions, const matrix_t *M) {
  int check = -1;
  if (index_functions == MINOR_MATRIX) {
    if (M->rows < 1 || M->columns < 1) {
      check = ERROR_INCORRECT_MATRIX;
    } else if (M->rows != M->columns) {
      check = ERROR_CALCULATION;
    } else {
      check = OK;
    }
  } else {
    check = (M->rows < 1 || M->columns < 1);
  }
  return check;
}

int check_validation(const int count_args, const int index_functions, ...) {
  int status = OK;
  int rows_size[3] = {0, 0, 0};
  int columns_size[3] = {0, 0, 0};
  int status_list[3] = {-1, -1, -1};
  va_list mtx;
  va_start(mtx, index_functions);
  for (int i = 0; i < count_args; i++) {
    if (OK == status) {
      const matrix_t *M = va_arg(mtx, matrix_t *);
      status = check_null(M);
      if (OK == status && M->matrix != NULL) {
        status = check_valid_matrix(index_functions, M);
        if (OK == status) {
          rows_size[i] = M->rows;
          columns_size[i] = M->columns;
          for (int j = 0; j < M->rows; j++) {
            if (M->matrix[j] == NULL) {
              status = ERROR_INCORRECT_MATRIX;
              break;
            }
          }
        }
      } else if (OK == status && M->matrix == NULL) {
        status = ERROR_INCORRECT_MATRIX;
      }
    }
    status_list[i] = status;
  }

  va_end(mtx);

  for (int i = 0; i < count_args; i++) {
    if (ERROR_INCORRECT_MATRIX == status_list[i]) {
      status = ERROR_INCORRECT_MATRIX;
      break;
    }
  }

  if (OK == status &&
      (index_functions == RETVAL_2 || index_functions == RETVAL_3)) {
    const int src_size_rows = rows_size[0];
    const int src_size_columns = columns_size[0];
    for (int i = 1; i < count_args; i++) {
      if (src_size_rows != rows_size[i] ||
          src_size_columns != columns_size[i]) {
        status = ERROR_CALCULATION;
        break;
      }
    }
  }

  if (OK == status && index_functions == MULT_MATRIX) {
    const int src_A_columns = columns_size[0];
    const int src_B_rows = rows_size[1];
    if (src_A_columns != src_B_rows) {
      status = ERROR_CALCULATION;
    }
  }

  if (index_functions == RETVAL_2) {
    status = (OK == status);
  }

  return status;
}