using namespace std;


#include "imports.hpp"
DtwNamespace  dtw;

#include "declaration.hpp"
#include "definition.hpp"


int main(int argc, char *argv[]){
    cli::Parser parser(argc, argv);
    dtw = newDtwNamespace();

    parser.set_required<string>(ACTION_SHORT, ACTION_LONG, ACTION_DESCRIPTION);
    parser.set_optional<string>(STORAGE_SHORT, STORAGE_LONG, DEFAULT_STORAGE_FILE, STORAGE_DESCRIPTION);


    string storage = parser.get<string>(STORAGE_SHORT);
    const char *storage_c = storage.c_str();
    string action = parser.get<string>(ACTION_SHORT);
    if(
             action != RESSET_STORAGE &&
             action != UNLOCK_ACTION &&
             action != LOCK_ACTION
            ){
        cout << INVALID_ACTION_MESSAGE << "\n";
        return INVALID_ACTION;
    }


    if(action == RESSET_STORAGE){
        return resset_storage(storage_c);
    }
    parser.set_required<string>(ENTITY_SHORT,ENTITY_LONG, ENTITY_DESCRIPTION);
    string entity = parser.get<string>(ENTITY_SHORT);
    const char * entity_in_c =entity.c_str();

    if(action == UNLOCK_ACTION){
        return unlock_entity(storage_c,entity_in_c);
    }

    //action is lock here

    parser.set_optional<int>(TIMEOUT_SHORT, TIMEOUT_LONG, DEFAULT_TIME, TIMEOUT_DESCRIPTION);
    parser.set_optional<int>(WAIT_SHORT, WAIT_LONG, DEFAULT_TIME, WAIT_DESCRIPTION);
    //auto will be int
    int timeout = parser.get<int>(TIMEOUT_SHORT);
    int wait = parser.get<int>(WAIT_SHORT);


}
