#pragma once
#include <vector>
#include <array>
#include <stdexcept>

std::vector<double> solveTriagonalSlae(const std::vector<double>& a, const std::vector<double>& b,
    const std::vector<double>& c, const std::vector<double>& d) {
    std::vector<double> p(d.size() - 1);
    std::vector<double> q(d.size() - 1);
    std::vector<double> x(d.size());

    p[0] = -c[0] / b[0];
    q[0] = d[0] / b[0];
    for (int i = 1; i < p.size(); ++i) {
        p[i] = -c[i] / (a[i] * p[i - 1] + b[i]);
        q[i] = (d[i] - a[i] * q[i - 1]) / (a[i] * p[i - 1] + b[i]);
    }
    x.back() = (d.back() - a.back() * q.back()) / (a.back() * p.back() + b.back());
    for (int i = x.size() - 2; i >= 0; --i) {
        x[i] = p[i] * x[i + 1] + q[i];
    }
    return x;
}

class Spline {
private:
    std::vector<std::array<double, 4>> p_;
    std::vector<double> x_;
public:
    Spline(const std::vector<double>& x, const std::vector<double>& f) : x_(x) {
        if (x.size() != f.size() || x.size() < 2) {
            throw std::invalid_argument("Invalid input data");
        }
        const int n = x.size()-1;
        p_.resize(n);

        for (int i = 0; i < n; ++i) {
            p_[i][0] = f[i+1];
        }
        p_.back()[2] = 0;


        std::vector<double> a(n), b(n, 2), c(n), d(n); // b = {2,2,2,2,,,}

        for (int i = 0; i < n - 1; ++i) {
            if (i != 0)
                a[i] = (x[i + 1] - x[i]) / (x[i + 2] - x[i]); // h_i / (h_i + h_{i+1})
            if (i != n - 1) {
                c[i] = (x[i + 2] - x[i + 1]) / (x[i + 2] - x[i]); // h_{i+1} / (h_i + h_{i+1})
            }
            d[i] = ((f[i + 2] - f[i + 1]) / (x[i + 2] - x[i + 1]) - (f[i + 1] - f[i]) / (x[i + 1] - x[i])) /
                       (x[i + 2] - x[i]);
            // u(x_{i+2}, x_{i+1}, x_{i}) = (u(x_{i+1}, x_{i+2}) - u(x_{i}, x_{i+1})) / (x_{i+2} - x_{i})
        }
        const auto res = solveTriagonalSlae(a, b, c, d);

        for (int i = 0; i < n; ++i) {
            p_[i][2] = res[i];
        }

        p_[0][1] = (f[1] - f[0]) / (x[1] - x[0]) + p_[0][2] * (x[1] - x[0]) / 3; // b1 = u(x_0, x_1)  + c_1 * h_1 / 3
        p_[0][3] = p_[0][2] / (x[1] - x[0]); // d1 = c1 / h1

        for (int i = 1; i < n; ++i) {
            p_[i][1] = (f[i + 1] - f[i]) / (x[i + 1] - x[i]) + (p_[i][2] / 3 + p_[i - 1][2] / 6) * (x[i + 1] - x[i]);
            p_[i][3] = (p_[i][2] - p_[i - 1][2]) / (x[i + 1] - x[i]);
        }
    }

    [[nodiscard]] double interpolate(double x) const{
        constexpr auto sqr = [](const auto x) { return x * x; };
        constexpr auto cb = [](const auto x) { return x * x * x; };

        if (x < x_[0]) {
            const double d = x - x_[0];
            return p_[0][0] + p_[0][1] * d + p_[0][2] * sqr(d) / 2 + p_[0][3] * cb(d) / 6;
        }

        if (x > x_.back()){
            const double d = x - x_.back();
            return p_.back()[0] + p_.back()[1] * d + p_.back()[2] * sqr(d) / 2 + p_.back()[3] * cb(d) / 6;
        }

        for (size_t i = 0; i < p_.size(); ++i) {
            if (x >= x_[i] && x <= x_[i + 1]) {
                const double d = x - x_[i + 1];
                return p_[i][0] + p_[i][1] * d + p_[i][2] * sqr(d) / 2 + p_[i][3] * cb(d) / 6;
            }
        }
    }
};