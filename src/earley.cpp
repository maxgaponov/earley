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

void Algo::_scan(int index) {
    if (index == 0) {
        return;
    }
    for (const Configuration& conf : _configurations[index - 1]) {
        if (conf.has_symbol_after_dot() && conf.symbol_after_dot() == _word[index - 1]) {
            Configuration next_conf = conf;
            next_conf.dot_position += 1;
            _configurations[index].insert(next_conf);
        }
    }
}

bool operator<(const Rule& lhs, const Rule& rhs) {
    return std::tuple(lhs.from, lhs.to) < std::tuple(rhs.from, rhs.to);
}

bool operator<(const Configuration& lhs, const Configuration& rhs) {
    return std::tuple(lhs.rule, lhs.dot_position) < std::tuple(rhs.rule, rhs.dot_position);
}

bool Configuration::has_symbol_after_dot() const {
    return dot_position < rule.to.length();
}

char Configuration::symbol_after_dot() const {
    return rule.to[dot_position];
}
