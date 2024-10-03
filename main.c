#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

TestCase create_test_case(char* input, char* expected) {
    TestCase test;
    strcpy(test.input, input);
    strcpy(test.expected, expected);
    return test;
}

TestSuite create_test_suite(TestCase* tests, int test_count) {
    TestSuite suite;
    suite.tests = tests;
    suite.test_count = test_count;
    return suite;
}

ExecutionResult run_test_case(UserSolution solution, TestCase test) {
    ExecutionResult result;
    // Симуляция выполнения решения
    // В реальном проекте этот код будет выполнять решение пользователя
    strcpy(result.actual_output, test.input);  // Симулируем выполнение
    result.is_passed = (strcmp(result.actual_output, test.expected) == 0);
    return result;
}

TestRun run_all_tests(UserSolution solution, TestSuite suite) {
    TestRun run;
    run.suite = suite;
    run.results = malloc(suite.test_count * sizeof(ExecutionResult));

    for (int i = 0; i < suite.test_count; i++) {
        run.results[i] = run_test_case(solution, suite.tests[i]);
    }

    return run;
}

Submission check_solution(UserSolution solution, Task task) {
    Submission submission;
    submission.solution = solution;
    submission.results = malloc(task.test_suite.test_count * sizeof(ExecutionResult));

    int total_passed = 0;

    for (int i = 0; i < task.test_suite.test_count; i++) {
        submission.results[i] = run_test_case(solution, task.test_suite.tests[i]);
        if (submission.results[i].is_passed) {
            total_passed++;
        }
    }

    submission.total_passed = total_passed;
    return submission;
}



int main() {
    // Создание тестов
    TestCase test1 = create_test_case("input1", "expected1");
    TestCase test2 = create_test_case("input2", "expected2");
    TestCase tests[] = {test1, test2};

    // Создание набора тестов
    TestSuite suite = create_test_suite(tests, 2);

    // Создание задачи
    Task task = {"Example Task", suite};

    // Решение пользователя
    UserSolution solution = {"user_solution_code"};

    // Запуск проверки решения
    Submission submission = check_solution(solution, task);

    // Вывод результатов
    printf("Total tests passed: %d out of %d\n", submission.total_passed, suite.test_count);
    for (int i = 0; i < suite.test_count; i++) {
        printf("Test %d: %s\n", i + 1, submission.results[i].is_passed ? "Passed" : "Failed");
    }

    // Освобождение памяти
    free(submission.results);
    return 0;
}
