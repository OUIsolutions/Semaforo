using namespace std;


#include "imports.hpp"
DtwNamespace  dtw;

#include "declaration.hpp"
#include "definition.hpp"


int main(int argc, char *argv[]){
    cli::Parser parser(argc, argv);
    dtw = newDtwNamespace();

    parser.set_optional<int>(TIMEOUT_SHORT, TIMEOUT_LONG, DEFAULT_TIME, TIMEOUT_DESCRIPTION);
    parser.set_optional<int>(WAIT_SHORT, WAIT_LONG, DEFAULT_TIME, WAIT_DESCRIPTION);
    parser.set_optional<string>(STORAGE_SHORT, STORAGE_LONG, DEFAULT_STORAGE_FILE, STORAGE_DESCRIPTION);
    parser.run_and_exit_if_error();

    //auto will be int
    int timeout = parser.get<int>(TIMEOUT_SHORT);
    int wait = parser.get<int>(WAIT_SHORT);
    string storage = parser.get<string>(STORAGE_SHORT);


    //verify if its available to lock

    //lock the .json

    //verify again
    //lock file




}
