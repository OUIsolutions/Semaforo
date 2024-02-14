

int resset_storage(bool quiet,const char *storage_file);

int lock_entity(bool quiet,const char *storage_file, const char *entity,int max_wait,int timeout);

int unlock_entity(bool quiet,const char *storage_file,const char *entity);
