#include "start.h"
#include <pthread.h>

struct Courier
{
    char courrier_id[STR_LEN];
    char sender_name[STR_LEN];
    char sender_no[STR_LEN];
    char receiver_name[STR_LEN];
    char receiver_no[STR_LEN];
    char receiver_address[STR_LEN];
    char couier_message[STR_LEN];
    char attachment_type[STR_LEN];
    int courier_status;
    /***********************
     * 0 -> courrier transfer under process
     * 1 -> courrier received successfully
     * -1 -> courrier cancelled by sender
     * ********************/
};

void startExec();
long long generate_random_courier_id();
void update_status(char id[], char new_status[]);
void create_thread(struct Courier current_courier);
void *addCourier(void *arg);
void cancelCourier(char id[]);
void printCourierInfo(char id[]);
int check_status(struct Courier current_courier);
int find_courrier(char id[], int *status); // return true on SUCCESS else false