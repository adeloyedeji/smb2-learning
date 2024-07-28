#ifndef _LISTS_H_
#define _LISTS_H_

struct list;
struct list_node;

#define FOREACH_LIST_ITEM(list_ptr, node_ptr) {         \
            struct list_node *_temp = NULL;             \
            node_ptr = list_ptr->head;                  \
            for(; node_ptr != NULL; node_ptr = _temp){  \
                _temp = node_ptr->right;

#define FOREACH_LIST_END }}

struct list* list_new(void);
void list_register_compare_callback(struct list *list, int(*compare_callback)(void *item1, void *item2));
void list_register_print_callback(struct list *list, void(*print_callback)(void *node));
struct list_node* list_node_create(void *data);
void list_insert(struct list *list, void *data);
void list_insert_head(struct list *list, void *data);
int list_get_items_count(struct list *list);
void list_destroy(struct list* list);
void list_print_all(struct list* list);
void get_items_size(void);

#endif //_LISTS_H_