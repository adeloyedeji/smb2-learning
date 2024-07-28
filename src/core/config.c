#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "config.h"
#include "logger.h"
#include "util.h"

struct smbl_config {

};

bool_t parse_bool(const char *value, bool_t default_val)
{
    if (!value)
        return default_val;

    return TRUE;
}

struct smbl_config* config_open(const char* config_path)
{
    struct smbl_config* config = NULL;
    struct stat st_buff;
    int fd;

    fd = open(config_path, O_RDONLY | O_CLOEXEC);
    if (fd < 0) {
        smbl_log_critical("Cannot open config file %s.", config_path);
        return config;
    }

    if (fstat(fd, &st_buff) < 0) {
        smbl_log_critical("Configuration failure loading %s.", config_path);
        close(fd);
        return config;
    }



    return config;
}