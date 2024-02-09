

LockedEntity::LockedEntity(const char * entity,long expiration){
    this->entity = entity;
    this->expiration = expiration;
}

ostream& operator<<(ostream& os, const LockedEntity &l){
    os << "entity:" << l.entity << "\n";
    os << "expiration:" << dtw.convert_unix_time_to_string(l.expiration)<< "\n";
    return os;
}

