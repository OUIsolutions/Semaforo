
vector<LockedEntity> parse_locked_file(const char *storage_file);

void save_locked_list(vector<LockedEntity> &listage,const char *storage_file);

bool its_able_to_lock(vector<LockedEntity> &listage,const char *entity);


void print_locked_list(vector<LockedEntity> listage);
