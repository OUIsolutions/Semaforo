

string format_mirror_point(const char *stored_point, int mirror_point);

string get_random_mirror_path(const char *stored_point);

string format_real_point(const char *stored_point);

vector<string> create_all_mirror_points(const char *stored_point);

void  lock_all_mirrors(DtwLocker *locker, vector<string> &mirrors);