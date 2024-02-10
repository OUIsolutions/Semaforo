

string format_mirror_point(const char *stored_point, int mirror_point){
    stringstream  result;
    result << stored_point << "/mirror" << mirror_point << ".json";
    return result.str();
}

string get_random_mirror_path(const char *stored_point){
    srand(getpid() + time(nullptr));
    // Generating random number between 0-10
    int sorted_mirror = rand() % 11;
    return format_mirror_point(stored_point,sorted_mirror);
}


string format_real_point(const char *stored_point){
    stringstream  result;
    result << stored_point << "/real.json";
    return result.str();
}

vector<string> create_all_mirror_points(const char *stored_point){

    vector<string> result;
    result.reserve(TOTAL_MIRRORS);
    for(int i = 0; i <  TOTAL_MIRRORS; i++){
        result.emplace_back(format_mirror_point(stored_point,i));
    }
    return result;

}

int  lock_all_mirrors(DtwLocker *locker, vector<string> &mirrors){
    for(auto &m : mirrors){
        int result =    dtw.locker.lock(locker,m.c_str());
        if(result == DTW_LOCKER_MAX_WAIT){
            return DTW_LOCKER_MAX_WAIT;
        }
    }
    return OK;

}
