

LockedEntity::LockedEntity(const char * entity,long expiration){
    this->entity = entity;
    this->expiration = expiration;
}

bool  LockedEntity::is_parent(const char *entity){
    if(this->entity == entity){
        return true;
    }
    CTextStack * self_stack = newCTextStack_string(this->entity.c_str());
    if(CTextStack_starts_with(self_stack,entity)){
        CTextStack_free(self_stack);
        return  true;
    }
    CTextStack_free(self_stack);

    CTextStack * entity_stack = newCTextStack_string(entity);
    if(CTextStack_starts_with(entity_stack,this->entity.c_str())){
        CTextStack_free(entity_stack);
        return true;
    }

    CTextStack_free(entity_stack);
    return false;
}

ostream& operator<<(ostream& os, const LockedEntity &l){
    os << "entity:" << l.entity << "\n";
    os << "expiration:" << dtw.convert_unix_time_to_string(l.expiration)<< "\n";
    return os;
}

