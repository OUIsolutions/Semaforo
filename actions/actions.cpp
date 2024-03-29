//
// Created by mateusmoutinho on 09/02/24.
//

int resset_storage(bool quiet,const char *storage_file){
    dtw.remove_any(storage_file);
    return OK;
}


int lock_entity(bool quiet,const char *storage_file, const char *entity,int max_wait,int timeout){
    long start = time(nullptr);
    bool first = true;
    while (true){
        long now = time(nullptr);

        if(start + max_wait <= now && !first){
            if(!quiet){
                cout << FILE_ITS_ALREADY_LOCKED << "\n";
            }

            return FILE_ITS_ALREADY_LOCKED_CODE;
        }

        first = false;


        //means its able to lock here
        DtwLocker *locker  = dtw.locker.newLocker();
        locker->max_wait = max_wait;
        locker->total_checks = TOTAL_CHECKS;
        locker->fail_delay =MAX_DELAY;
        if(dtw.locker.lock(locker,storage_file) == DTW_LOCKER_WAIT_ERROR){
            if(!quiet){
                cout << FILE_ITS_ALREADY_LOCKED << "\n";

            }
            dtw.locker.free(locker);
            return FILE_ITS_ALREADY_LOCKED_CODE;
        };


        vector<LockedEntity> locked_list;
        try{
            locked_list = parse_locked_file(storage_file);
        }
        catch (const std::exception& e) {
            // Capturando e tratando a exceção
            if(!quiet){
                cerr  << e.what() << endl;
            }
            dtw.locker.free(locker);
            return INVALID_STORAGE_FILE;
        }

        //verify again after the storage has ben locked
        if(!its_able_to_lock(locked_list, entity)){
            dtw.locker.free(locker);
            continue;
        }

        now = time(nullptr);
        long expiration = now + timeout;
        locked_list.emplace_back(entity, expiration);
        save_locked_list(locked_list, storage_file);
        dtw.locker.free(locker);

        return OK;
    }

}


int unlock_entity(bool quiet,const char *storage_file,const char *entity){

    //means its able to lock here
    DtwLocker *locker  = dtw.locker.newLocker();
    locker->total_checks = TOTAL_CHECKS;
    dtw.locker.lock(locker,storage_file);

    vector<LockedEntity> final_locker;
    try{
        final_locker = parse_locked_file(storage_file);
    }
    catch (const std::exception& e) {
        // Capturando e tratando a exceção
        if(!quiet){
            cerr  << e.what() << endl;

        }
        dtw.locker.free(locker);
        return INVALID_STORAGE_FILE;
    }

    long position = get_entity_position(final_locker,entity);
    if(position == NOT_FOUND){
        dtw.locker.free(locker);
        return  OK;
    }
    //remove the element at position index
    final_locker.erase(final_locker.begin() + position);

    save_locked_list(final_locker, storage_file);
    dtw.locker.free(locker);
    return OK;

}