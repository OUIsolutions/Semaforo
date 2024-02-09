

int resset_storage(const char *storage_file);

int lock_entity(const char *storage_file, const char *entity,int max_wait,int timeout);

int unlock_entity(const char *storage_file,const char *entity);
