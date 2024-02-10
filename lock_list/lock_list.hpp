
vector<LockedEntity> parse_locked_file(const char *storage_file);

void save_locked_list(vector<LockedEntity> &listage,const char *storage_file);

long get_entity_position(vector<LockedEntity> &listage,const char *entity);


bool its_able_to_lock(vector<LockedEntity> &listage,const char *entity);


void print_locked_list(vector<LockedEntity> &listage);
