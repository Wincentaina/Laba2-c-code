#include <stdio.h>

typedef struct {
    char input[256];    // Входные данные для теста
    char expected[256]; // Ожидаемый результат
} TestCase;

typedef struct {
    TestCase* tests;    // Массив тестов
    int test_count;     // Количество тестов
} TestSuite;

typedef struct {
    char solution_code[1024]; // Код решения пользователя
} UserSolution;

typedef struct {
    char actual_output[256];  // Фактический результат выполнения
    int is_passed;            // Успешность прохождения теста (1 - прошел, 0 - не прошел)
} ExecutionResult;

typedef struct {
    UserSolution solution;        // Решение пользователя
    ExecutionResult* results;     // Результаты выполнения тестов
    int total_passed;             // Общее количество пройденных тестов
} Submission;

typedef struct {
    TestSuite suite;              // Набор тестов
    ExecutionResult* results;     // Массив результатов для каждого теста
} TestRun;

typedef struct {
    char description[512];        // Описание задачи
    TestSuite test_suite;         // Набор тестов для задачи
} Task;

typedef struct {
    Task task;                    // Задача, которую нужно проверить
    Submission submission;        // Отправка, содержащая решение
} Checker;

int main() {
    printf("Hello, World!\n");
    return 0;
}
