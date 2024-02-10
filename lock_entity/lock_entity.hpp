
class LockedEntity{
public:
    string entity;
    long expiration;
    LockedEntity(const char * entity,long expiration);

    friend ostream& operator<<(ostream& os, const LockedEntity& a);

};

