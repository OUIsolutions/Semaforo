

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
