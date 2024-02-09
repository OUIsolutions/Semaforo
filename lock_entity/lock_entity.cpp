

LockedEntity::LockedEntity(const char * entity,long locked_time,int timeout){
    this->entity = entity;
    this->locked_time = locked_time;
    this->timeout = timeout;
}
