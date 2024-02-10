//
// Created by mateusmoutinho on 09/02/24.
//

int resset_storage(const char *storage_file){
    dtw.remove_any(storage_file);
    return OK;
}


int lock_entity(const char *storage_file, const char *entity,int max_wait,int timeout){
    long start = time(nullptr);

    while (true){
        long now = time(nullptr);

        if(start + max_wait < now){
            cout << FILE_ITS_ALREADY_LOCKED << "\n";
            return FILE_ITS_ALREADY_LOCKED_CODE;
        }

        vector<LockedEntity> first_locked_list;

        try{
            first_locked_list = parse_locked_file(storage_file);
        }
        catch (const std::exception& e) {
            // Capturando e tratando a exceção
            cerr  << e.what() << endl;
            return INVALID_STORAGE_FILE;
        }

        if(!its_able_to_lock(first_locked_list,entity)){
            continue;
        }

        //means its able to lock here
        DtwLocker *locker  = dtw.locker.newLocker();
        dtw.locker.lock(locker,storage_file);

        vector<LockedEntity> final_locker;
        try{
            final_locker = parse_locked_file(storage_file);
        }
        catch (const std::exception& e) {
            // Capturando e tratando a exceção
            cerr  << e.what() << endl;
            dtw.locker.free(locker);
            return INVALID_STORAGE_FILE;
        }

        //verify again after the storage has ben locked
        if(!its_able_to_lock(final_locker,entity)){
            dtw.locker.free(locker);
            continue;
        }

        now = time(nullptr);
        long expiration = now + timeout;
        final_locker.emplace_back(entity, expiration);
        save_locked_list(final_locker, storage_file);
    
        return OK;
    }

}


int unlock_entity(const char *storage_file,const char *entity){
    return OK;
}