#define DEBUG
using namespace std;


#include "imports.hpp"
DtwNamespace  dtw;
CHashNamespace  chash;
#include "declaration.hpp"
#include "definition.hpp"


int main(int argc, char *argv[]){
    cli::Parser parser(argc, argv);
    dtw = newDtwNamespace();

    chash = newCHashNamespace();
    parser.set_optional<string>(QUIET_SHORT, QUIET_LONG, DEFAULT_QUIET,QUIET_DESCRIPTION);
    parser.set_required<string>(ACTION_SHORT, ACTION_LONG, ACTION_DESCRIPTION);
    parser.set_optional<string>(STORAGE_SHORT, STORAGE_LONG, DEFAULT_STORAGE_FILE, STORAGE_DESCRIPTION);
    parser.set_optional<int>(TIMEOUT_SHORT, TIMEOUT_LONG, DEFAULT_TIME, TIMEOUT_DESCRIPTION);
    parser.set_optional<int>(WAIT_SHORT, WAIT_LONG, DEFAULT_TIME, WAIT_DESCRIPTION);
    parser.set_optional<string>(ENTITY_SHORT,ENTITY_LONG, "",ENTITY_DESCRIPTION);

    parser.run_and_exit_if_error();

    string quiet_string = parser.get<string>(QUIET_SHORT);
    bool quiet = quiet_string == "true" ? true:false;

    string storage = parser.get<string>(STORAGE_SHORT);
    string action = parser.get<string>(ACTION_SHORT);


    const char *storage_c = storage.c_str();

    if(
        action != RESSET_STORAGE &&
        action != UNLOCK_ACTION &&
        action != LOCK_ACTION){
        cout << INVALID_ACTION_MESSAGE << "\n";
        return INVALID_ARGUMENTS;
    }


    if(action == RESSET_STORAGE){
        return resset_storage(quiet,storage_c);
    }


    string entity = parser.get<string>(ENTITY_SHORT);
    if(entity.empty()){
        cout << ENTITY_NOT_PROVIDED;
        return INVALID_ARGUMENTS;
    }


    const char * entity_in_c =entity.c_str();
    if(action == UNLOCK_ACTION){
        return unlock_entity(quiet,storage_c,entity_in_c);
    }


    int timeout = parser.get<int>(TIMEOUT_SHORT);
    int wait = parser.get<int>(WAIT_SHORT);

    return lock_entity(quiet,storage_c,entity_in_c,wait,timeout);
}
