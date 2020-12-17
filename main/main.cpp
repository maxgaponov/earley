#include <iostream>
#include <earley.h>

std::set<Rule> read_grammar(std::istream& in) {
    std::set<Rule> grammar;
    char from;
    std::string to;
    while (in >> from >> to) {
        grammar.insert(Rule{from, to});
    }
    return grammar;
}

void run(std::istream& in, std::ostream& out) {
    std::string word;
    in >> word;
    std::set<Rule> grammar = read_grammar(in);
    out << (Algo(grammar, word).in_language() ? "In language" : "Not in language") << std::endl;
}

int main() {
    run(std::cin, std::cout);
	return 0;
}
