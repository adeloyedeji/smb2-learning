#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "util.h"
#define QUEUE_DEFAULT_SIZE 100
#define QUEUE_IS_EMPTY(queue_ptr) (queue_ptr->front == queue_ptr->rear)
#define FOREACH_QUEUE_ITEM(queue_ptr, data_ptr) {   \
            int _idx = 0;                           \
            for(; _idx < queue_ptr->rear; _idx++){  \
                data_ptr = queue_ptr->data[_idx];      

#define FOREACH_QUEUE_ITEM_END }}

struct queue;

struct queue* queue_new(void);
void queue_destroy(struct queue*);
bool_t queue_enqueue(struct queue*, void*);
void* queue_dequeue(struct queue*);
void* queue_peek(struct queue*);
bool_t queue_is_empty(struct queue*);
int queue_size(struct queue*);
void queue_print_all(struct queue*);
void queue_register_print_callback(struct queue*, void(*print_callback)(void*));
void queue_register_compare_callback(struct queue*, int(compare_callback(void*, void*)));

#endif //_QUEUE_H_