/**
 * @file matrix.c
 * @brief В этом файле описаны определения основных функций библиотеки
 * matrix
 */
#include "../matrix.h"

/**
 * @brief нахождение минора матрицы A
 *
 * @param A
 * @param row
 * @param col
 * @param minor
 * @return int
 * @retval 0 - OK
 * @retval 1 - Ошибка, некорректная матрица
 * @retval 2 - Ошибка вычисления
 */
static int get_minor(matrix_t *A, const int rows, const int columns,
                         matrix_t *result);

int create_matrix(int rows, int columns, matrix_t *result) {
  int status = ERROR_CALCULATION;
  if (0 < rows && 0 < columns) {
    if (NULL != result) {
      const size_t copyRows = rows, copyColumns = columns;
      result->matrix = allocated_memory(copyRows, copyColumns);
      result->columns = columns;
      result->rows = rows;
      status = check_null(result->matrix);
    } else {
      status = ERROR_INCORRECT_MATRIX;
    }
  } else {
    status = ERROR_INCORRECT_MATRIX;
  }
  return status;
}

void remove_matrix(matrix_t *A) {
  if (NULL != A && NULL != A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (NULL != A->matrix[i]) {
        free(A->matrix[i]);
        A->matrix[i] = NULL;
      }
    }
    free(A->matrix);
    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
  }
}

int eq_matrix(matrix_t *A, matrix_t *B) {
  int status = check_validation(2, RETVAL_2, A, B);
  if (SUCCESS == status) {
    for (int i = 0; i < A->rows && SUCCESS == status; i++) {
      for (int j = 0; j < A->columns; j++) {
        if ((fabs(A->matrix[i][j] - B->matrix[i][j])) > 1e-7) {
          status = FAILURE;
          break;
        }
      }
    }
  }
  return status;
}

int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = check_validation(2, RETVAL_3, A, B);
  if (OK == status && NULL != result) {
    status = create_matrix(A->rows, A->columns, result);
    if (OK == status) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  } else if (NULL == result) {
    status = ERROR_INCORRECT_MATRIX;
  }
  return status;
}

int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = check_validation(2, RETVAL_3, A, B);
  if (OK == status && NULL != result) {
    status = create_matrix(A->rows, A->columns, result);
    if (OK == status) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  } else if (NULL == result) {
    status = ERROR_INCORRECT_MATRIX;
  }
  return status;
}

int mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = check_validation(1, ONE_MATRIX, A);
  if (OK == status && NULL != result) {
    status = create_matrix(A->rows, A->columns, result);
    if (OK == status) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  } else if (OK == status && NULL == result) {
    status = ERROR_INCORRECT_MATRIX;
  }
  return status;
}

int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = check_validation(2, MULT_MATRIX, A, B);
  if (OK == status && NULL != result) {
    status = create_matrix(A->rows, B->columns, result);
    if (OK == status) {
      for (int result_i = 0; result_i < A->rows; result_i++) {
        for (int result_j = 0; result_j < B->columns; result_j++) {
          for (int k = 0; k < B->rows; k++) {
            result->matrix[result_i][result_j] +=
                A->matrix[result_i][k] * B->matrix[k][result_j];
          }
        }
      }
    }
  } else if (OK == status && NULL == result) {
    status = ERROR_INCORRECT_MATRIX;
  }
  return status;
}

int transpose(matrix_t *A, matrix_t *result) {
  int status = check_validation(1, TRANSP_MATRIX, A);
  if (OK == status && NULL != result) {
    status = create_matrix(A->columns, A->rows, result);
    if (OK == status) {
      for (int i = 0; i < A->columns; i++) {
        for (int j = 0; j < A->rows; j++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    }
  } else if (OK == status && NULL == result) {
    status = ERROR_INCORRECT_MATRIX;
  }
  return status;
}

int calc_complements(matrix_t *A, matrix_t *result) {
  int status = check_validation(1, MINOR_MATRIX, A);
  if (OK == status && NULL != result) {
    status = create_matrix(A->rows, A->columns, result);
    if (OK == status) {
      if (1 != A->rows) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            matrix_t minor = {.matrix = NULL, .rows = 0, .columns = 0};
            double det = 0;
            status = create_matrix(A->rows - 1, A->columns - 1, &minor);
            if (OK == status) {
              status = get_minor(A, i, j, &minor);
            } else {
              break;
            }
            if (OK == status) {
              status = determinant(&minor, &determinant);
              if (OK == status) {
                result->matrix[i][j] = det * pow(-1, i + j);
              } else {
                remove_matrix(&minor);
                break;
              }
            }
            remove_matrix(&minor);
          }
        }
      } else {
        result->matrix[0][0] = 1.0;
      }
    }
  } else if (OK == status && NULL == result) {
    status = ERROR_INCORRECT_MATRIX;
  }
  return status;
}

static int get_minor(matrix_t *A, const int rows, const int columns,
                         matrix_t *result) {
  int status = check_validation(1, MINOR_MATRIX, A);
  if (OK == status && NULL != result) {
    result->rows = A->rows - 1;
    result->columns = A->columns - 1;
    int minor_i = 0;
    for (int i = 0; i < A->rows; i++) {
      int minor_j = 0;
      if (rows != i) {
        for (int j = 0; j < A->columns; j++) {
          if (columns != j) {
            result->matrix[minor_i][minor_j++] = A->matrix[i][j];
          }
        }
        minor_i++;
      }
    }
  }
  return status;
}

int determinant(matrix_t *A, double *result) {
  int status = check_validation(1, MINOR_MATRIX, A);
  if (OK == status && NULL != result) {
    if (2 < A->rows) {
      matrix_t minor = {.matrix = NULL, .rows = 0, .columns = 0};
      create_matrix(A->rows - 1, A->columns - 1, &minor);
      *result = 0;
      for (int i = 0; i < A->columns; i++) {
        double det = 0;
        get_minor(A, 0, i, &minor);
        determinant(&minor, &det);
        *result += A->matrix[0][i] * pow(-1, i) * det;
      }
      remove_matrix(&minor);
    } else if (2 == A->rows) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else if (1 == A->rows) {
      *result = A->matrix[0][0];
    }
  } else if (OK == status && NULL == result) {
    status = ERROR_INCORRECT_MATRIX;
  }
  return status;
}

int inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = check_validation(1, MINOR_MATRIX, A);
  if (OK == status && NULL != result) {
    matrix_t adjoint = {.matrix = NULL, .rows = 0, .columns = 0};
    double det = 0.0;
    status = calc_complements(A, &adjoint);
    if (OK == status) {
      status = determinant(A, &det);
      if (OK == status) {
        if (0 != det) {
          matrix_t buf_matrix = {.matrix = NULL, .rows = 0, .columns = 0};
          const double inv_determinant = 1.0 / det;
          mult_number(&adjoint, inv_determinant, &buf_matrix);
          transpose(&buf_matrix, result);
          remove_matrix(&buf_matrix);
        } else {
          status = ERROR_CALCULATION;
        }
      }
    }
    remove_matrix(&adjoint);
  } else if (OK == status && NULL == result) {
    status = ERROR_INCORRECT_MATRIX;
  }
  return status;
}