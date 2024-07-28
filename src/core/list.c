#include <stdlib.h>
#include <errno.h>
#include "logger.h"
#include "list.h"

struct list_node {
    void *data;
    struct list_node *left;
    struct list_node *right;
};

struct list {
    struct list_node *head;
    void (*print_fn)(void *item);
    int (*compare_fn)(void *item1, void *item2);
    int count;
};

struct list* list_new(void)
{
    struct list *double_linked_list = NULL;
    double_linked_list = (struct list*)calloc(1, sizeof(struct list));

    if (!double_linked_list) {
        smbl_log_critical("calloc() failed");
        return double_linked_list;
    }

    double_linked_list->head = NULL;
    double_linked_list->count = 0;

    return double_linked_list;
}

void list_register_compare_callback(struct list *list, int(*compare_callback)(void *item1, void *item2))
{
    list->compare_fn = compare_callback;
}

void list_register_print_callback(struct list *list, void(*print_callback)(void *node))
{
    list->print_fn = print_callback;
}

struct list_node* list_node_create(void *data)
{
    struct list_node *node = NULL;
    node = (struct list_node*)calloc(1, sizeof(struct list_node));

    if (!node) {
        smbl_log_critical("allocation failed.");
        return node;
    }

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void list_node_destroy(struct list_node* node) {
    if (!node)
        return;

    free(node);
    node = NULL;
}

void list_insert(struct list *list, void *data)
{
    if (!list) {
        smbl_log_critical("list is not initialized.");
        return;
    }

    if (!data) {
        smbl_log_critical("data is not a valid pointer.");
        return;
    }

    struct list_node *temp = list_node_create(data);

    if (!list->head) {
        temp->left = NULL;
        temp->right = NULL;
        list->head = temp;
    } else {
        struct list_node *itr = list->head;
        while(itr->right != NULL) {
            itr = itr->right;
        }

        itr->right = temp;
        temp->left = itr;
    }

    list->count++;
}

void list_insert_head(struct list *list, void *data)
{
    struct list_node *temp = list_node_create(data);
    temp->right = list->head;
    
    if (!list->head) {
        list->head->left = temp;
    }

    list->head = temp;
    list->count++;
}

int list_get_items_count(struct list *list)
{
    if (!list)
        return 0;

    return list->count;
}

void list_destroy(struct list* list)
{
    if (!list)
        return;

    struct list_node *temp;
    FOREACH_LIST_ITEM(list, temp) {
        list_node_destroy(temp);
    } FOREACH_LIST_END;

    free(list);
    list = NULL;
}

void list_print_all(struct list* list)
{
    if (!list)
        return;

    if (!list->print_fn) {
        smbl_log_error("No print function registered. call list_register_print_callback() to register callback function.");
        return;
    }
    
    struct list_node *temp;
    FOREACH_LIST_ITEM(list, temp) {
        list->print_fn(temp->data);
    } FOREACH_LIST_END;
}

void get_items_size(void)
{
    smbl_log_info("Size of list_node = %lu.", sizeof(struct list_node));
    smbl_log_info("Size of list = %lu.", sizeof(struct list));
}