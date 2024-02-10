//
// Created by mateusmoutinho on 09/02/24.
//

int resset_storage(const char *storage_file){
    dtw.remove_any(storage_file);
    return OK;
}


int lock_entity(const char *storage_file, const char *entity,int max_wait,int timeout){

    vector<LockedEntity> locked_list;

    try{
        locked_list = parse_locked_file(storage_file);
    }
    catch (const std::exception& e) {
        // Capturando e tratando a exceção
        std::cerr  << e.what() << std::endl;
        return INVALID_STORAGE_FILE;
    }

    long now = time(nullptr);
    locked_list.push_back(LockedEntity(entity,now + timeout));
    save_locked_list(locked_list,storage_file);



    return OK;
}


int unlock_entity(const char *storage_file,const char *entity){
    return OK;
}