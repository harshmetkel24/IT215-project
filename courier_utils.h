#include "start.h"

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

void addCourier(struct Courier current_courier);
void cancelCourier(struct Courier current_courier);
int check_status(struct Courier current_courier);
int find_courrier(char id[], int *status); // return true on SUCCESS else false