#include <gtest/gtest.h>
#include <earley.h>

TEST(test_rule, compare) {
    Rule r1{'S', "abc"};
    Rule r2{'T', "S"};
    EXPECT_TRUE(r1 < r2);
    EXPECT_FALSE(r2 < r1);
    EXPECT_FALSE(r1 < r1);
}

TEST(test_conf, compare) {
    Configuration c1{Rule{'S', "T"}, 0, 0};
    Configuration c2{Rule{'T', "S"}, 1, 0};
    EXPECT_TRUE(c1 < c2);
    EXPECT_FALSE(c2 < c1);
    EXPECT_FALSE(c1 < c1);
}

TEST(test_conf, manip) {
    Configuration conf{Rule{'S', "T"}, 0, 0};
    EXPECT_TRUE(conf.has_symbol_after_dot());
    EXPECT_EQ(conf.symbol_after_dot(), 'T');
    conf = conf.shift_dot();
    EXPECT_FALSE(conf.has_symbol_after_dot());
    EXPECT_EQ(conf.dot_position, 1);
}