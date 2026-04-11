#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <Space_hackathon/third_party_test.hpp>
#include <iostream>


TEST(DormanPrince, DenseOutput) {
    const Eigen::VectorXd a{};

    const int c = foo(3, 4);
    std::cout << c << std::endl;
}