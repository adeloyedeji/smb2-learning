#ifndef _CONFIG_H_
#define _CONFIG_H_

enum config_line_category {
    CONFIG_LINE_CATEGORY_SECTION,
    CONFIG_LINE_CATEGORY_LINE,
    CONFIG_LINE_CATEGORY_END
};

struct config_line {
    char *config_name;
    char *config_value;
    enum config_line_category config_category;
};

struct smbl_config;

struct smbl_config* config_open(const char* config_path);
void config_close(struct smbl_config* confg);
struct config_line* config_read_line(struct smbl_config *config);

#endif //_CONFIG_H_