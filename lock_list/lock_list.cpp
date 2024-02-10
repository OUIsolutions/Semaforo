

vector<LockedEntity> parse_locked_file(const char *storage_file){

    vector<LockedEntity> result;

    int entity  = dtw.entity_type(storage_file);
    string error;
    if(entity == DTW_NOT_FOUND){
        return result;
    }

    if(entity == DTW_FOLDER_TYPE){
        error = LOCK_FILE_ITS_A_FOLDER;
        throw runtime_error(error);
    }

    char *content =  dtw.load_string_file_content(storage_file);
    if(!content){
        error = UNEXPECTED_ERROR;
        throw runtime_error(error);
    }

    CHashArray *parsed = chash.load_from_json_strimg(content);
    free(content);
    chash.validator.ensure_Array(parsed);
    CHash_catch(parsed){

        char *error_message = chash.get_error_menssage(parsed);
        auto error =  runtime_error(error_message);
        CHash_free(parsed);
        throw error;
    }

    long size = chash.get_size(parsed);
    long now = time(nullptr);
    for(int i = 0; i < size; i++){
        CHashObject * current = chash.array.getObject(parsed,i);
        char *current_entity = chash.object.getString(current,ENTITY_KEY);
        long expiration = (long)chash.object.getNumber(current,EXPIRATION_KEY);

        CHash_catch(current){
            char *error_message = chash.get_error_menssage(parsed);
            auto error =  runtime_error(error_message);
            CHash_free(parsed);
            throw error;
        }

        if(now < expiration){
            result.emplace_back(current_entity, expiration);
        }

    }
    chash.free(parsed);
    return result;


}
bool its_able_to_lock(vector<LockedEntity> &listage,const char *entity){

    for(auto& current_entity : listage) {
        if(current_entity.is_parent(entity)){
            return  false;
        }
    }
    return true;
}

void save_locked_list(vector<LockedEntity> &listage,const char *storage_file){
    CHashArray *result = newCHashArrayEmpty();

    for(auto& entity : listage) {
        CHashArray_append(result, newCHashObject(
            ENTITY_KEY,chash.newString(entity.entity.c_str()),
            EXPIRATION_KEY,chash.newNumber(entity.expiration)
        ));
    }

#ifdef DEBUG
    chash.dump_to_json_file(result,storage_file);
#else
    cJSON *parsed_cjson = chash.dump_to_cJSON(result);
    char *unidented = cJSON_PrintUnformatted(parsed_cjson);
    dtw.write_string_file_content(storage_file,unidented);
    cJSON_Delete(parsed_cjson);
    free(unidented);
#endif


    chash.free(result);


}
void print_locked_list(vector<LockedEntity> &listage){
    for(auto& entity : listage) {
        cout << entity;
        cout << "--------------------------------\n";
    }
}
