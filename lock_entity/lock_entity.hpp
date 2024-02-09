
class LockedEntity{
    string entity;
    long locked_time;
    int timeout;
public:
    LockedEntity(const char * entity,long locked_time,int timeout);


};
