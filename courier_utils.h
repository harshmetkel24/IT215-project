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

void addCourier(struct Courier current_courier)
{
    //  printf("*\n");
    current_courier.courier_status = 1; // courier is in sending status
    FILE *fp = fopen("./courier_info.csv", "a+");
    if (fp == NULL)
    {
        printf("Unable to open csv file of courier!!\n");
        return;
    }
    fprintf(fp, "%s, %s, %s, %s, %s, %s\n", current_courier.sender_name, current_courier.receiver_name, current_courier.receiver_no, current_courier.receiver_address, current_courier.couier_message, current_courier.attachment_type);
    printf("New data for courier is  added successfully!!\n");
    fclose(fp);
}
void cancelCourier(struct Courier current_courier)
{
    current_courier.courier_status = -1; // courier is cancelled
}
int check_status(struct Courier current_courier)
{
    return current_courier.courier_status;
}