#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <Space_hackathon/third_party_test.hpp>
#include <iostream>
#include <alglib>


TEST(THIRD, PARTY) {
    const Eigen::VectorXd a{};

    const int c = foo(3, 4);
    std::cout << c << std::endl;
}

TEST(ALG, LIB) {
    // --- Исходные данные ---
    // Узлы сплайна (x и y)
    // Пример: строим сплайн для функции y = x^2
    std::vector<double> x_nodes = {0.0, 2.5, 5.0, 7.5, 10.0};
    std::vector<double> y_nodes = {0.0, 6.25, 25.0, 56.25, 100.0};
    int n = x_nodes.size();

    // ALGLIB использует свои типы массивов для совместимости.
    // Мы скопируем данные из std::vector в real_1d_array.
    alglib::real_1d_array x_alglib, y_alglib;
    x_alglib.setcontent(n, x_nodes.data());
    y_alglib.setcontent(n, y_nodes.data());

    // --- Создание сплайна ---
    // Объект для хранения сплайна
    alglib::spline1dinterpolant spline;

    // Построение кубического сплайна
    // Параметры:
    //   x, y - массивы узлов и значений
    //   n    - количество узлов
    //   boundl_type, boundl_val - тип и значение граничного условия слева (2 - вторая производная, 0.0)
    //   boundr_type, boundr_val - тип и значение граничного условия справа
    //   spline - выходной объект сплайна
    alglib::spline1dbuildcubic(x_alglib, y_alglib, n, 2, 0.0, 2, 0.0, spline);

    // --- Использование сплайна ---
    std::cout << "Кубический сплайн для функции y = x*x на [0, 10]\n";
    std::cout << "Узлы сплайна: 0, 2.5, 5, 7.5, 10\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "    x    |   y (сплайн) | y (x^2) | Ошибка\n";
    std::cout << "-----------------------------------------\n";

    // Проверяем точность в нескольких точках
    for (double x = 0.0; x <= 10.0; x += 1.0) {
        // Вычисляем значение сплайна в точке x
        double y_spline = alglib::spline1dcalc(spline, x);
        double y_original = x * x;
        double error = std::abs(y_spline - y_original);

        printf(" %5.1f   |   %8.4f   | %8.4f | %8.6f\n", x, y_spline, y_original, error);
    }

    // --- Дополнительно: производные и интеграл ---
    // Значение сплайна, первой и второй производной в точке x=5
    double v, dv, d2v;
    alglib::spline1ddiff(spline, 5.0, v, dv, d2v);
    std::cout << "\n--- Дополнительные возможности ---\n";
    std::cout << "В точке x=5.0:\n";
    std::cout << "  Значение сплайна:   " << v << " (должно быть 25)\n";
    std::cout << "  Первая производная: " << dv << " (должно быть 10)\n";
    std::cout << "  Вторая производная: " << d2v << " (должно быть 2)\n";

    // Определенный интеграл сплайна от 0 до 10
    double integral = alglib::spline1dintegrate(spline, 10.0);
    std::cout << "\nИнтеграл сплайна от 0 до 10: " << integral << " (должен быть ~333.333)\n";

    return 0;
}