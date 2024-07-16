#include <stdlib.h>
#include "queue.h"
#include "logger.h"

struct queue {
    int front;
    int rear;
    size_t count;
    void *data[QUEUE_DEFAULT_SIZE];
    void (*print_fn)(void *data);
    int (*compare_fn)(void *key1, void *key2);
};

struct queue* queue_new(void)
{
    struct queue* queue = NULL;
    queue = (struct queue*)calloc(1, sizeof(struct queue));

    if (!queue) {
        smbl_log_critical("calloc() failed.");
        return queue;
    }

    queue->count = 0;
    queue->front = queue->rear = 0;

    return queue;
}

void queue_destroy(struct queue* queue)
{
    if (queue == NULL)
        return;

    free(queue);
    queue = NULL;
}

bool_t queue_is_full(struct queue* queue)
{
    if (!queue)
        return FALSE;
    
    if (queue->rear == QUEUE_DEFAULT_SIZE)
        return TRUE;
    
    return FALSE;
}

bool_t queue_enqueue(struct queue* queue, void* new_data)
{
    if (!queue || !new_data) {
        smbl_log_error("invalid options.");
        return FALSE;
    }

    if (queue->rear == QUEUE_DEFAULT_SIZE) {
        smbl_log_critical("queue is full, dropping enqueue request.");
        return FALSE;
    }

    queue->data[queue->rear] = new_data;
    queue->rear++;
    queue->count++;
    return TRUE;
}

void* queue_dequeue(struct queue* queue)
{
    void *queue_data = NULL;
    if (!queue) {
        smbl_log_error("invalid queue object.");
        return queue_data;
    }

    if (queue_is_empty(queue)) {
        smbl_log_info("queue is empty.");
        return queue_data;
    }

    queue_data = queue->data[queue->front];
    for(int i = 0; i < queue->rear - 1; i++) {
        queue->data[i] = queue->data[i + 1];
    }

    queue->rear--;
    
    return queue_data;
}

void* queue_peek(struct queue* queue)
{
    void* queue_data = NULL;
    if (!queue) {
        smbl_log_error("invalid queue object.");
        return queue_data;
    }

    if (queue_is_empty(queue)) {
        smbl_log_info("queue is empty.");
        return queue_data;
    }

    queue_data = queue->data[queue->front];

    return queue_data;
}

bool_t queue_is_empty(struct queue* queue)
{
    return queue->front == queue->rear ? TRUE : FALSE;
}

int queue_size(struct queue* queue)
{
    return queue->rear;
}

void queue_print_all(struct queue* queue)
{
    if (!queue) {
        smbl_log_error("queue is not initialized.");
        return;
    }

    if (queue_is_empty(queue)) {
        smbl_log_info("queue is empty.");
        return;
    }

    if (!queue->print_fn) {
        smbl_log_error("queue has no print callback.");
        return;
    }

    void* data = NULL;
    FOREACH_QUEUE_ITEM(queue, data) {
        queue->print_fn(data);
    } FOREACH_QUEUE_ITEM_END;

}

void queue_register_print_callback(struct queue* queue, void(*print_callback)(void*))
{
    if (!queue || !print_callback) {
        smbl_log_error("invalid options.");
        return;
    }

    queue->print_fn = print_callback;
}

void queue_register_compare_callback(struct queue* queue, int(compare_callback(void*, void*)))
{
    if (!queue || !compare_callback) {
        smbl_log_error("invalid options.");
        return;
    }

    queue->compare_fn = compare_callback;
}
