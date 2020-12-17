#include <earley.h>

Algo::Algo(const std::set<Rule>& grammar, const std::string& word)
: _word(word), _grammar(grammar), _configurations(word.length() + 1) {}

bool Algo::in_language() {
    _configurations[0].insert(Configuration{Rule{START_S, std::string{S}}, 0, 0});
    for (int index = 0; index <= _word.length(); ++index) {
        _scan(index);
        int prev_conf_size;
        do {
            prev_conf_size = _configurations[index].size();
            _complete(index);
            _predict(index);
        } while (prev_conf_size != _configurations[index].size());
    }
    return _configurations[_word.length()].count(Configuration{Rule{START_S, std::string{S}}, 1, 0});
}

void Algo::_scan(int index) {
    if (index == 0) {
        return;
    }
    for (const Configuration& conf : _configurations[index - 1]) {
        if (conf.has_symbol_after_dot() && conf.symbol_after_dot() == _word[index - 1]) {
            _configurations[index].insert(conf.shift_dot());
        }
    }
}

void Algo::_complete(int index) {
    for (const Configuration& conf : _configurations[index]) {
        if (conf.has_symbol_after_dot()) {
            continue;
        }
        for (const Configuration& iconf : _configurations[conf.index]) {
            if (iconf.has_symbol_after_dot() && iconf.symbol_after_dot() == conf.rule.from) {
                _configurations[index].insert(iconf.shift_dot());
            }
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

Configuration Configuration::shift_dot() const {
    Configuration conf = *this;
    conf.dot_position += 1;
    return conf;
}