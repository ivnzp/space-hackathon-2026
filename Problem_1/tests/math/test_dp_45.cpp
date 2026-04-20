#include <Space_hackathon/math/integration.hpp>
#include <gtest/gtest.h>
#include <Eigen/Dense>

// Тестовая функция: dx/dt = -x
auto f = [](double t, const Eigen::VectorXd& x) -> Eigen::VectorXd {
    Eigen::VectorXd res(1);
    res(0) = -x(0);
    return res;
};

// Аналитическое решение
double exact(double t) {
    return std::exp(-t);
}

TEST(DormanPrince, DenseOutput) {
    // Задаём точки, где нужно выдать решение (включая промежуточные)
    const std::vector<double> ts = {0.2, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0};
    constexpr double t0 = 0.0;
    Eigen::VectorXd y0(1);
    y0(0) = 1.0;   // x(0) = 1

    constexpr double tol = 1e-14;
    constexpr double h0 = 1e-10;  // начальный шаг, можно взять побольше

    std::vector<Eigen::VectorXd> sol = DormanPrince(f, t0, y0, ts, tol, h0);

    // Проверяем, что количество решений совпадает с количеством запрошенных точек
    ASSERT_EQ(sol.size(), ts.size());

    for (size_t i = 0; i < ts.size(); ++i) {
        const double computed = sol[i](0);
        const double expected = exact(ts[i]);
        double rel_error = std::abs(computed - expected) / (std::abs(expected) + 1e-12);
        EXPECT_LT(rel_error, tol * 10) << "at t = " << ts[i];
    }
}