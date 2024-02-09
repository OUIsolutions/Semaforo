

LockedEntity::LockedEntity(const char * entity,long locked_time,int timeout){
    this->entity = entity;
    this->locked_time = locked_time;
    this->timeout = timeout;
}

ostream& operator<<(ostream& os, const LockedEntity &l){
    os << "entity " << l.entity << "\n";
    os << "locked-time " << l.locked_time << "\n";
    os << "time" << l.timeout << "\n";
    return os;
}
