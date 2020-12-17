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

TEST(test_earley, bbs) {
    std::set<Rule> grammar = {
            Rule{'S', ""},
            Rule{'S', "(S)S"}
    };
    EXPECT_TRUE(Algo(grammar, "").in_language());
    EXPECT_TRUE(Algo(grammar, "()").in_language());
    EXPECT_TRUE(Algo(grammar, "(())()").in_language());
    EXPECT_TRUE(Algo(grammar, "(()())((()))").in_language());
    EXPECT_FALSE(Algo(grammar, ")(").in_language());
    EXPECT_FALSE(Algo(grammar, "()(()").in_language());
}

TEST(test_earley, anbn) {
    std::set<Rule> grammar = {
            Rule{'S', ""},
            Rule{'S', "aSb"}
    };
    EXPECT_TRUE(Algo(grammar, "").in_language());
    EXPECT_TRUE(Algo(grammar, "ab").in_language());
    EXPECT_TRUE(Algo(grammar, "aabb").in_language());
    EXPECT_TRUE(Algo(grammar, "aaaaabbbbb").in_language());
    EXPECT_FALSE(Algo(grammar, "b").in_language());
    EXPECT_FALSE(Algo(grammar, "aaaaabbbb").in_language());
    EXPECT_FALSE(Algo(grammar, "aaa").in_language());
}

TEST(test_earley, scan) {
    std::set<Rule> grammar = {
            Rule{'S', ""},
            Rule{'S', "aSb"}
    };
    std::string word = "aabb";
    Algo algo(grammar, word);
    algo._complete(0);
    algo._predict(0);
    algo._scan(1);
    EXPECT_EQ(algo._configurations[1].size(), 1);
}

TEST(test_earley, predict) {
    std::set<Rule> grammar = {
            Rule{'S', ""},
            Rule{'S', "aSb"}
    };
    std::string word = "aabb";
    Algo algo(grammar, word);
    algo._predict(0);
    EXPECT_EQ(algo._configurations[0].size(), 3);
}

TEST(test_earley, complete) {
    std::set<Rule> grammar = {
            Rule{'S', ""},
            Rule{'S', "aSb"}
    };
    std::string word = "aabb";
    Algo algo(grammar, word);
    algo._complete(0);
    algo._predict(0);
    algo._scan(1);
    algo._complete(1);
    EXPECT_EQ(algo._configurations[1].size(), 1);
}