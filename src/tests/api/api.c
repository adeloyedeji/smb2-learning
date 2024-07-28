#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "smbl.h"

struct user {
    char fname[50];
    char lname[50];
    int age;
};

struct user* user_create(char *fname, char* lname, int age)
{
    struct user* user = NULL;
    user = (struct user*)calloc(1, sizeof(struct user));

    if (!user) {
        smbl_log_critical("allocation failed.");
        return user;
    }

    strncpy(user->fname, fname, (strlen(fname) + 1));
    strncpy(user->lname, lname, (strlen(lname) + 1));
    user->age = age;

    return user;
}

void user_destroy(struct user* user)
{
    free(user);
    user = NULL;
}

void print_user_data(struct user *user)
{
    smbl_log_info("\nName:\t%s %s\nAge:\t%d.", user->fname, user->lname, user->age);
}

void print_user_callback(void *data)
{
    struct user *user = (struct user*)data;
    print_user_data(user);
}

void test_list(struct user* users_arr[5])
{
    struct list* user_db = NULL;
    user_db = list_new();
    list_register_print_callback(user_db, print_user_callback);

    list_insert(user_db, (void*)users_arr[0]);
    list_insert(user_db, (void*)users_arr[1]);
    list_insert(user_db, (void*)users_arr[2]);
    list_insert_head(user_db, (void*)users_arr[3]);
    list_insert_head(user_db, (void*)users_arr[4]);

    smbl_log_info("Our list database now has %d items.", list_get_items_count(user_db));
    smbl_log_info("User Database - List");
    list_print_all(user_db);

    list_destroy(user_db);
}

void test_queue(struct user* users_arr[5])
{
    struct queue* user_queue_db = NULL;
    user_queue_db =  queue_new();
    queue_register_print_callback(user_queue_db, print_user_callback);  

    queue_enqueue(user_queue_db, (void*)users_arr[0]);
    queue_enqueue(user_queue_db, (void*)users_arr[1]);
    queue_enqueue(user_queue_db, (void*)users_arr[2]);
    queue_enqueue(user_queue_db, (void*)users_arr[3]);
    queue_enqueue(user_queue_db, (void*)users_arr[4]);

    smbl_log_info("Our queue database now has %d items.", queue_size(user_queue_db));
    smbl_log_info("User Database - Queue");
    queue_print_all(user_queue_db);
    smbl_log_info("Peeking at queue ...");
    void* peek_data = queue_peek(user_queue_db);
    print_user_callback(peek_data); 

    queue_destroy(user_queue_db);
}

int main(void)
{  
    struct user *john = user_create("John", "Doe", 40);
    struct user *clark = user_create("Clark", "Kent", 30);
    struct user *barry = user_create("Barry", "Allen", 27);
    struct user *bruce = user_create("Bruce", "Wayne", 32);
    struct user *hal = user_create("Hal", "Jordan", 28);
    struct user* users[5] = {john, clark, barry, bruce, hal};

    test_list(users);
    test_queue(users);
    
    user_destroy(john);
    user_destroy(clark);
    user_destroy(barry);
    user_destroy(bruce);
    user_destroy(hal);

    return EXIT_SUCCESS;
}