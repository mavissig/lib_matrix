# Руководство по Makefile

Руководство по использованию makefile для проекта [lib_matrix](../README.md)

Author : [Egor Kondratov](https://github.com/mavissig)

---

## Contents

1. [Флаги](#используемые-флаги) \
    1.1. [Флаги для сборки тестов](#флаги-для-сборки-тестов) \
    1.2. [Флаги для проверки на утечки](#флаги-для-проверки-на-утечки)
2. [Описание целей](#описание-целей) \
    2.1. [all](#all) \
    2.2. [matrix.a](#matrixa)\
    2.3. [objective](#objective) \
    2.4. [test](#test) \
    2.5. [leaks](#leaks) \
    2.6. [check и clang](#проверка-и-исправление-стиля-check-и-clang) \
    2.7. [gcov_report](#gcov_report) \
    2.8. [open](#open) \
    2.9. [clean](#clean)

# Используемые флаги

### Флаги компилятора :

```
-Wall -Werror -Wextra -std=c11 -O2 
```

### Флаги для сборки тестов :
- Linux

    ```
    -lcheck -lm -lpthread -lrt -lsubunit
    ```

- Darwin

    ```
    -lcheck -lm 
    ```

### Флаги для проверки на утечки:
- Linux

    ```
    valgrind --tool=memcheck --leak-check=yes --quiet --log-file=./logs/leaks_log.txt ./matrix_test
    ```

- Darwin

    ```
    leaks -q --atExit --  
    ```

# Описание целей

### `all`

Выполняет очистку спомощью цели [clean]() и сборку библиотеки через цель [matrix.a]()

syntax :

```bash
make all
```

---

### `matrix.a`

Выполняет сборку библиотеки в файл *libmatrix.a*

syntax :

```bash
make matrix.a
```
---

### `objective`

Выполняет сборку объектных файлов(.o) из .c файлов расположенных по пути **lib_matrix/src/functions/\*.c**

Полный список компилируемых файлов :
- *matrix.c*
- *memory_management.c*
- *permitted.c*

syntax :

```bash
make objective
```

---

### `test`

Выполняет сборку и запуск тестов

syntax :

```bash
make test
```

---

### `leaks`

Выполняет проверку на утечки памяти.

syntax :

```bash
make leaks
```

---

### Проверка и исправление стиля `check` и `clang`

Выполняет исправление стиля согласно файлу *.clang-format* . Файл *.clang-format* копируется из папки *lib_matrix/materials/linters/.clang-format* и выполняется одна из следующих команд:
- для цели `check` выполняется команда `clang-format -n`
- для цели `clang` выполняется команда `clang-format -i`

После проверки *.clang-format* удаляется из корневой директории.

syntax :

```bash
make check
```
```bash
make clang
```

---

### `gcov_report`

Выполняет расчет покрытия тестами

syntax :

```bash
make gcov_report
```

---

### `open`

Выполняет формирование репорта в браузере. Используется после цели [gcov_report](#gcov_report)

syntax :

```bash
make open
```

---

### `clean`

Выполняет удаление ранее скомпилированых файлов

Полный список удаляемых файлов:

- `*.o` 
- `*.a`
- `*.gc*`
- `*.out`
- `*.dSYM`
- `*.gcov`
- `*.info`
- `./matrix_test`
- `*.txt`
- `test`
- `./gcov_tests`
- `report`
- `./logs/*.txt`

syntax :

```bash
make clean
```


---

