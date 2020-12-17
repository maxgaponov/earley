#include <earley.h>

Algo::Algo(const std::set<Rule> &grammar, const std::string &word)
: _word(word), _grammar(grammar), _configurations(word.length() + 1) {}

bool Algo::in_language() {
    _configurations[0].insert(Configuration{Rule{START_S, std::string{S}}, 0});
    for (int index = 0; index <= _word.length(); ++index) {
        _scan(index);
        while (_complete(index) || _predict(index)) {}
    }
    return _configurations[_word.length()].count(Configuration{Rule{START_S, std::string{S}}, 1});
}

bool operator<(const Rule& lhs, const Rule& rhs) {
    return std::tuple(lhs.from, lhs.to) < std::tuple(rhs.from, rhs.to);
}

bool operator<(const Configuration& lhs, const Configuration& rhs) {
    return std::tuple(lhs.rule, lhs.dot_position) < std::tuple(rhs.rule, rhs.dot_position);
}
