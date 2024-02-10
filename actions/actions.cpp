//
// Created by mateusmoutinho on 09/02/24.
//

int resset_storage(const char *storage_file){
    dtw.remove_any(storage_file);
    return OK;
}


int lock_entity(const char *storage_point, const char *entity, int max_wait, int timeout){
    long start = time(nullptr);
    bool first = true;
    string real_stored_file = format_real_point(storage_point);
    const char *real_stored_file_c =  real_stored_file.c_str();
    vector<string> mirrors = create_all_mirror_points(storage_point);


    while (true){
        long now = time(nullptr);

        if(start + max_wait <= now && !first){
            cout << FILE_ITS_ALREADY_LOCKED << "\n";
            return FILE_ITS_ALREADY_LOCKED_CODE;
        }

        first = false;
        DtwLocker *locker  = dtw.locker.newLocker();
        //means its able to lock here
        locker->total_checks = TOTAL_CHECKS;
        vector<LockedEntity> test_locked_list;
        string random_mirror = get_random_mirror_path(storage_point);
        dtw.locker.lock(locker,random_mirror.c_str());

        try{
           test_locked_list = parse_locked_file(random_mirror.c_str());
        }

        catch (const std::exception& e) {
            // Capturando e tratando a exceção
            cerr  << e.what() << endl;
            dtw.locker.free(locker);
            return INVALID_STORAGE_FILE;
        }

        if (!its_able_to_lock(test_locked_list, entity)) {
            dtw.locker.free(locker);
            continue;
        }
        dtw.locker.lock(locker, real_stored_file_c);

        vector<LockedEntity> locked_list;
        try{
            locked_list = parse_locked_file(real_stored_file_c);
        }
        catch (const std::exception& e) {
            // Capturando e tratando a exceção
            cerr  << e.what() << endl;
            dtw.locker.free(locker);
            return INVALID_STORAGE_FILE;
        }



        //verify again after the storage has ben locked
        if(!its_able_to_lock(locked_list, entity)){
            dtw.locker.free(locker);
            continue;
        }

        lock_all_mirrors(locker,mirrors);
        now = time(nullptr);
        long expiration = now + timeout;
        locked_list.emplace_back(entity, expiration);
        save_locked_list(locked_list, real_stored_file_c);

        save_mirrors(locked_list,mirrors);
        dtw.locker.free(locker);

        return OK;
    }

}


int unlock_entity(const char *storage_point,const char *entity){

    string real_stored_file = format_real_point(storage_point);
    const char *real_stored_file_c =  real_stored_file.c_str();
    vector<string> mirrors = create_all_mirror_points(storage_point);


    //means its able to lock here
    DtwLocker *locker  = dtw.locker.newLocker();
    locker->total_checks = TOTAL_CHECKS;
    dtw.locker.lock(locker,real_stored_file_c);

    vector<LockedEntity> final_locker;

    try{
        final_locker = parse_locked_file(real_stored_file_c);
    }

    catch (const std::exception& e) {
        // Capturando e tratando a exceção
        cerr  << e.what() << endl;
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
    lock_all_mirrors(locker,mirrors);

    save_locked_list(final_locker, real_stored_file_c);
    save_mirrors(final_locker,mirrors);
    dtw.locker.free(locker);
    return OK;

}