#pragma once
#include <set>
#include <string>
#include <vector>
#include <tuple>
#include <gtest/gtest.h>

struct Rule {
    char from;
    std::string to;
};

bool operator<(const Rule& lhs, const Rule& rhs);

struct Configuration {
    Rule rule;
    int dot_position;
    int index;

    bool has_symbol_after_dot() const;
    char symbol_after_dot() const;
    Configuration shift_dot() const;
};

bool operator<(const Configuration& lhs, const Configuration& rhs);

class Algo {
 public:
    Algo(const std::set<Rule>& grammar, const std::string& word);

    bool in_language();
 private:
    void _scan(int index);
    void _predict(int index);
    void _complete(int index);

    std::string _word;
    std::set<Rule> _grammar;
    std::vector<std::set<Configuration>> _configurations;

    const char START_S = '\0';
    const char S = 'S';

    FRIEND_TEST(test_earley, scan);
    FRIEND_TEST(test_earley, predict);
    FRIEND_TEST(test_earley, complete);
};
