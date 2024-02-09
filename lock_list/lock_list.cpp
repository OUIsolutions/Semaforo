

vector<LockedEntity> parse_locked_file(string &locked_file){

    vector<LockedEntity> result;

    int entity  = dtw.entity_type(locked_file.c_str());

    if(entity == DTW_NOT_FOUND){
        return result;
    }
    

    return  result;
}