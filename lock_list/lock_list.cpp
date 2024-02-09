

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

    return result;






    return  result;
}