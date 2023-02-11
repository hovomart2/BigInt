#include <BigInt/BigInt.h>
#include <gtest/gtest.h>

#include <vector>

using namespace ACA;
using namespace std;

TEST(BigInt, Increment) {
    const vector<pair<BigInt, BigInt>> ExpectedActualList = {
        { BigInt("1"), BigInt("2") },
        { BigInt("4841353513135319"), BigInt("4841353513135320") },
        { BigInt("9"), BigInt("10") },
        { BigInt("99999"), BigInt("100000") }
    };

    for (auto [num, num_plus_one] : ExpectedActualList) {
        EXPECT_EQ(++num, num_plus_one);
    }
}

TEST(BigInt, Decrement) {
    const vector<pair<BigInt, BigInt>> ExpectedActualList = {
        { BigInt("1"), BigInt("0") },
        { BigInt("10"), BigInt("9") },
        { BigInt("646546464646484618465486"), BigInt("646546464646484618465485") },
        { BigInt("13513100000"), BigInt("13513099999") }
    };

    for (auto [num, num_minus_one] : ExpectedActualList) {
        EXPECT_EQ(--num, num_minus_one);
    }
}

TEST(BigInt, Sum) {
    const vector<tuple<BigInt, BigInt, BigInt>> ExpectedActualList = {
        { BigInt("1"), BigInt("0"), BigInt("1") },
        { BigInt("1689"), BigInt("1745"), BigInt("3434") },
        { BigInt("1987"), BigInt("348"), BigInt("2335") },
        { BigInt("17835493352534"), BigInt("1432564762"), BigInt("17836925917296") },
        { BigInt("999"), BigInt("333"), BigInt("1332") },
        { BigInt("99889"), BigInt("111"), BigInt("100000") },
        { BigInt("76"), BigInt("178545"), BigInt("178621") }

    };
    

    for (auto [num1, num2, answer] : ExpectedActualList) {
        EXPECT_EQ(num1 + num2, answer);
    }
}

TEST(BigInt, Difference) {
    const vector<tuple<BigInt, BigInt, BigInt>> ExpectedActualList = {
        { BigInt("1"), BigInt("0"), BigInt("1") },
        { BigInt("3434"), BigInt("1689"), BigInt("1745") },
        { BigInt("2335"), BigInt("1987"), BigInt("348") },
        { BigInt("17836925917296"), BigInt("17835493352534"), BigInt("1432564762") },
        { BigInt("1332"), BigInt("999"), BigInt("333") },
        { BigInt("555"), BigInt("555"), BigInt("0") },
        { BigInt("11111111"), BigInt("22"), BigInt("11111089") }


    };

    for (auto [num1, num2, answer] : ExpectedActualList) {
        EXPECT_EQ(num1 - num2, answer);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

