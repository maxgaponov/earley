#pragma once
#include <set>
#include <string>
#include <vector>

struct Rule {
    char from;
    std::string to;
};

struct Configuration {
    Rule rule;
    int dot_position;
};

class Algo {
 public:
    Algo(const std::set<Rule>& grammar, const std::string& word);

    bool in_language();
 private:
    void scan(int index);
    bool predict(int index);
    bool complete(int index);

    std::string _word;
    std::set<Rule> _grammar;
    std::vector<std::set<Configuration>> _configurations;
};
