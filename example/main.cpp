#include "clrpp/clrpp.hpp"
#include <vector>
#include <string>

int main() {
    clrpp();

    std::vector<std::string> vec;
    vec.emplace_back("test_package");

    clrpp_print_vector(vec);
}
