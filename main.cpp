
#include "imports.hpp"
#include "declaration.hpp"
#include "definition.hpp"

using namespace std;

int main(int argc, char *argv[]){
    cli::Parser parser(argc, argv);

    parser.set_optional<int>("t", "timeout", 60, "max time that current process can be with the ownership");
    parser.set_optional<int>("w", "wait", 60, "max time for waiting the ownershil (after returns an error)");
    parser.set_optional<string>("s", "storage", ".lock.json", "the entity locks json to control what its been locked");
    parser.run_and_exit_if_error();

    //auto will be int
    int timeout = parser.get<int>("t");
    int wait = parser.get<int>("w");
    string storage = parser.get<string>("s");
    cout << "Command: " << timeout << "\n";
    cout << "Command: " << wait << "\n";
    cout << "Command: " << storage << "\n";
}
