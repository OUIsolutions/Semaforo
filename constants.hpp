const char * TIMEOUT_SHORT = "t";
const char *TIMEOUT_DESCRIPTION = "max time that current process can be with the ownership";

const char *ACTION_SHORT = "a";
const char *ACTION_LONG = "action";
const char *ACTION_DESCRIPTION = "the action you will execute";

const char *ENTITY_SHORT = "e";
const char *ENTITY_LONG = "entity";
const char *ENTITY_DESCRIPTION = "the entity you are targeting";

const char * TIMEOUT_LONG = "timeout";
const int DEFAULT_TIME =60;



const char * WAIT_SHORT = "w";
const char * WAIT_LONG ="wait";
const char  *WAIT_DESCRIPTION = "max time for waiting the ownershil (after returns an error)";

const char * STORAGE_SHORT = "s";
const char * STORAGE_LONG = "storage";
const char  *STORAGE_DESCRIPTION = "the entity locks json to control what its been locked";

const char * DEFAULT_STORAGE_FILE = ".lock.json";


const char *LOCK_ACTION = "lock";
const char *UNLOCK_ACTION = "unlock";
const char *RESSET_STORAGE  = "resset";

const char *INVALID_ACTION_MESSAGE = "invalid action";


//cccodes

const int OK = 0;
const int LOCKED_BY_OTHER_PROCESS  =1;
const int INVALID_ARGUMENTS = 2;

const int STORAGE_FILE_UNFORMATED =  3;
const char *ENTITY_NOT_PROVIDED = "entity not provided\n";
const char * LOCK_FILE_ITS_A_FOLDER  = "lock file it a folder";
const char *UNEXPECTED_ERROR = "unexpected error";