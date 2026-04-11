#pragma once

#include <functional>
#include <Eigen/Dense>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>

// Коэффициенты метода Дормана-Принса (5(4))
constexpr std::array<double, 7> c = {0, 1./5, 3./10, 4./5, 8./9, 1., 1};

constexpr std::array<std::array<double, 6>, 6> A = {{
    {1. / 5, 0, 0, 0, 0, 0},
    {3. / 40, 9. / 40, 0, 0, 0, 0},
    {44. / 45, -56. / 15, 32. / 9, 0, 0, 0},
    {19372. / 6561, -25360. / 2187, 64448. / 6561, -212. / 729, 0, 0},
    {9017. / 3168, -355. / 33, 46732. / 5247, 49. / 176, -5103. / 18656, 0},
    {35. / 384, 0, 500. / 1113, 125. / 192, -2187. / 6784, 11. / 84}
}};

constexpr std::array<double, 7> b5 = {35. / 384, 0, 500. / 1113, 125. / 192, -2187. / 6784, 11. / 84, 0};
constexpr std::array<double, 7> b4 = {5179. / 57600, 0, 7571. / 16695, 393. / 640, -92097. / 339200, 187. / 2100, 1. / 40};

// Коэффициенты плотного вывода
std::array<double, 7> dense_output(double sigma) {
    const double s1 = sigma;
    const double s2 = s1 * s1;
    const double s3 = s2 * s1;
    const double s4 = s3 * s1;

    return {
        (157015080 * s4 - 13107642775 * s3 + 34969693132 * s2 - 32272833064 * s1 + 11282082432) / 11282082432,
        0,
        -100 * s1 * (15701508 * s3 - 914128567 * s2 + 2074956840 * s1 - 1323431896) / 32700410799,
        25 * s1 * (94209048 * s3 - 1518414297 * s2 + 2460397220 * s1 - 889289856) / 5641041216,
        -2187 * s1 * (52338360 * s3 - 451824525 * s2 + 687873124 * s1 - 259006536) / 199316789632,
        11 * s1 * (106151040 * s3 - 661884105 * s2 + 946554244 * s1 - 361440756) / 2467955532,
        s1 * (1 - s1) * (8293050 * s2 - 82437520 * s1 + 44764047) / 29380423,
    };
}

template<typename F, typename T>
std::vector<Eigen::VectorXd> DormanPrince(const F& f, T t0, const Eigen::VectorXd& y0,
                                          const std::vector<T>& ts,
                                          double tol = 1e-12, double h0 = 1e-6) {
    constexpr double alpha = 0.95;
    constexpr double beta  = 1.3;

    std::vector<Eigen::VectorXd> solution;
    solution.reserve(ts.size());

    T t = t0;
    double h = h0;
    Eigen::VectorXd y = y0;
    size_t idx = 0;

    if (idx < ts.size() && std::abs(ts[idx] - t0) < 1e-12) {
        solution.push_back(y0);
        ++idx;
    }

    while (idx < ts.size() && t <= ts.back() + 1e-12) {
        const T t_prev = t;
        const Eigen::VectorXd y_prev = y;

        std::array<Eigen::VectorXd, 7> k;
        k[0] = f(t, y);
        for (int i = 1; i < 7; ++i) {
            Eigen::VectorXd sum = Eigen::VectorXd::Zero(y.size());
            for (int j = 0; j < i; ++j)
                sum += A[i-1][j] * k[j];
            k[i] = f(t + c[i] * h, y + h * sum);
        }

        Eigen::VectorXd y5 = y;
        Eigen::VectorXd y4 = y;
        for (int i = 0; i < 7; ++i) {
            y5 += h * b5[i] * k[i];
            y4 += h * b4[i] * k[i];
        }

        const double epsilon = (y5 - y4).norm();

        if (epsilon <= tol) {
            y = y5;
            t = t + h;

            while (idx < ts.size() && ts[idx] <= t + 1e-12) {
                const double sigma = (ts[idx] - t_prev) / h;
                auto b_dense = dense_output(sigma);

                Eigen::VectorXd y_interp = y_prev;
                for (int i = 0; i < 7; ++i)
                    y_interp += sigma * h * b_dense[i] * k[i];
                // y_interp += sigma * h * b_dense[6] * k7;

                solution.push_back(y_interp);
                ++idx;
            }

            const double factor = alpha * std::pow(tol / epsilon, 1.0 / 5.0);
            h = std::min(beta * h, factor * h);
        } else {
            h = alpha * h * std::pow(tol / epsilon, 1.0 / 5.0);
        }
    }

    return solution;
}