
class LockedEntity{
public:
    string entity;
    long expiration;
    LockedEntity(const char * entity,long expiration);

    bool is_parent(const char *entity);

    friend ostream& operator<<(ostream& os, const LockedEntity& a);

};

