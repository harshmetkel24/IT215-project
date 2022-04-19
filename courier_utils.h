#include "start.h"

struct Courier
{
    char sender_name[STR_LEN];
    char receiver_name[STR_LEN];
    char receiver_no[STR_LEN];
    char receiver_address[STR_LEN];
    char couier_message[STR_LEN];
    char attachment_type[STR_LEN];
    int courier_status;
};

void addCourier(struct Courier current_courier);
void cancelCourier(struct Courier current_courier);
int check_status(struct Courier current_courier);