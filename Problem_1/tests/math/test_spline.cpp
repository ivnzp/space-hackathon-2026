#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <Space_hackathon/math/interpolation.hpp>
#include <iostream>

TEST(Inter, Inter) {
    const std::vector<double> year = {1910, 1920, 1930, 1940, 1950, 1960, 1970, 1980, 1990, 2000};
    const std::vector<double> population = {
        92228496,
        106021537,
        123202624,
        132164569,
        151325798,
        179323175,
        203211926,
        226545805,
        248709873,
        281421906
        };

    double x = 2010;
    double y = 308745538;

    // кубический сплайн
    const Spline spline(year, population);
    double spline_f = spline.interpolate(x);
}

#include <../cmake-build-debug/alglib_install/src/alglib_project/>

// Определяем тестовый модуль
TEST(ALGLIB_2D_Spline, RBF_Scattered_Interpolation) {
    // 1. Исходная функция: f(x,y) = x² + 2*y²
    auto original_function = [](double x, double y) -> double {
        return x * x + 2.0 * y * y;
    };

    // 2. Создаем обучающий набор данных (разреженная сетка)
    // Точки (x, y) не лежат на прямоугольной сетке
    std::vector<double> xs = {0.0, 1.0, 2.0, 0.0, 1.0, 2.0, 0.0, 1.0, 2.0};
    std::vector<double> ys = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 2.0, 2.0, 2.0};
    std::vector<double> zs;
    for (size_t i = 0; i < xs.size(); ++i) {
        zs.push_back(original_function(xs[i], ys[i]));
    }

    // Конвертируем данные в форматы ALGLIB
    alglib::real_1d_array x_alglib, y_alglib, z_alglib;
    x_alglib.setcontent(xs.size(), xs.data());
    y_alglib.setcontent(ys.size(), ys.data());
    z_alglib.setcontent(zs.size(), zs.data());

    // 3. Настройка и построение RBF-интерполятора
    // Входные данные: координаты x, y и значения z, количество точек
    // Параметры: NLayers = 5 (количество уровней), RBase = 2.0 (базовый радиус)
    alglib::rbfmodel rbf;
    alglib::rbfsetpoints(x_alglib, y_alglib, z_alglib, xs.size());
    alglib::rbfsetalgomultilayer(rbf, 5, 2.0);
    alglib::rbfbuildmodel(rbf);

    // 4. Набор контрольных точек для проверки (не использовались при обучении)
    struct TestPoint {
        double x, y;
    };
    std::vector<TestPoint> test_points = {
        {0.5, 0.5}, {1.5, 1.5}, {0.5, 1.5}, {1.5, 0.5}, {2.0, 1.0}
    };

    // 5. Проверка точности интерполяции
    for (const auto& tp : test_points) {
        double interpolated_value = alglib::rbfcalc2(rbf, tp.x, tp.y);
        double expected_value = original_function(tp.x, tp.y);
        // Проверяем с допуском 1e-3 (относительная погрешность)
        EXPECT_NEAR(interpolated_value, expected_value, 1e-3)
            << "Погрешность интерполяции в точке (" << tp.x << ", " << tp.y << ") превышена.";
    }

    // 6. Дополнительная проверка: производные в точке (1.0, 1.0)
    double x_test = 1.0, y_test = 1.0;
    double z_val, dzx, dzy;
    alglib::rbfcalc2d(rbf, x_test, y_test, z_val, dzx, dzy);

    double expected_z = original_function(x_test, y_test);
    double expected_dzx = 2 * x_test;  // ∂/∂x (x² + 2y²) = 2x
    double expected_dzy = 4 * y_test;  // ∂/∂y (x² + 2y²) = 4y

    EXPECT_NEAR(z_val, expected_z, 1e-3);
    EXPECT_NEAR(dzx, expected_dzx, 1e-3);
    EXPECT_NEAR(dzy, expected_dzy, 1e-3);
}