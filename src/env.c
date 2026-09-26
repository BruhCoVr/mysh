#include <env.h>

extern char **environ;

struct Env env = {
    .user = "",
    .home = "",
    .path = "",
    .pwd = ""
};  


void initialize_env() {
    // Do a full one pass search for environment variables
    int found_user = 0;
    int found_home = 0;
    int found_path = 0;
    int found_pwd = 0;

    for (int i = 0; environ[i] != NULL; i++) {
        if (!found_user && str_eq_limit(environ[i], "USER=", 5)) {
            str_cpy(env.user, environ[i] + 5);
            found_user = 1;
        } else if (!found_home && str_eq_limit(environ[i], "HOME=", 5)) {
            str_cpy(env.home, environ[i] + 5);
            found_home = 1;
        } else if (!found_path && str_eq_limit(environ[i], "PATH=", 5)) {
            str_cpy(env.path, environ[i] + 5);
            found_path = 1;
        } else if (!found_pwd && str_eq_limit(environ[i], "PWD=", 4)) {
            str_cpy(env.pwd, environ[i] + 4);
            found_pwd = 1;
        }
    }
}

char* get_user() {
    return env.user;
}

char* get_home() {
    return env.home;
}

char* get_path() {
    return env.path;
}

char* get_pwd() {
    return env.pwd;
}