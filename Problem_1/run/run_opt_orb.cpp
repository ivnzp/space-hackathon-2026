#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <Space_hackathon/optimal_3d_transition.hpp>
#include <Space_hackathon/math/interpolation.hpp>
#include <iostream>


TEST(OPT, ORB) {
    const auto table = getCharacteristicVelocityTable();

    const Spline spline(year, population);
    double spline_f = spline.interpolate(x);
    double V_ch = table[apocenter_index][pericenter_index][inclination_index];
}