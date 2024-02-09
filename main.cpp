
#include "imports.hpp"
#include "declaration.hpp"
#include "definition.hpp"

using namespace std;

int main(int argc, char *argv[]){
    cli::Parser parser(argc, argv);

    parser.set_optional<int>("n", "number", 8, "Integers in all forms, e.g., unsigned int, long long, ..., are possible. Hexadecimal and Ocatl numbers parsed as well");

    //auto will be int
    auto number = parser.get<int>("n");
    cout << "Command: " << number << "\n";
}
