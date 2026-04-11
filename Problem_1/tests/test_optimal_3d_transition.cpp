#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <Space_hackathon/optimal_3d_transition.hpp>


TEST(OPt_3D_trans, OPt_3D_trans) {
    auto table = getCharacteristicVelocityTable();
    double V_ch = table[0][0][0];
}