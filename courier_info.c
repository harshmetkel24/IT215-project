#include "courier_utils.h"

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
int main()
{
    int choice;

    while (1)
    {
        printf("Enter 1 for adding new courier.\n");
        printf("Enter 2 for cancelling current courier.\n");
        printf("Enter 3 for checking current status of courier.\n");
        struct Courier courier;
        courier.courier_status = 0;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            printf("Welcome again!!\n");
            char sender_name[STR_LEN], receiver_name[STR_LEN], address_receiver[STR_LEN], receiver_no[STR_LEN], courier_mssg[STR_LEN], attatchment_type[STR_LEN];
            printf("Please enter full address of receiver.\n");
            scanf("%s", &address_receiver);
            // getchar();
            printf("Please enter sender name.\n");
            scanf("%s", &sender_name);
            // getchar();
            printf("Please enter receiver name.\n");
            scanf("%s", &receiver_name);
            // getchar();
            printf("Please enter contact number of receiver.\n");
            scanf("%s", &receiver_no);
            //  getchar();
            printf("Please enter message to be attatched with courier.\n");
            scanf("%s", &courier_mssg);
            // getchar();
            printf("Please enter type of attatchment(courier).\n");
            scanf("%s", &attatchment_type);
            // getchar();

            strcpy(courier.attachment_type, attatchment_type);
            strcpy(courier.couier_message, courier_mssg);
            strcpy(courier.receiver_address, address_receiver);
            strcpy(courier.sender_name, sender_name);
            strcpy(courier.receiver_name, receiver_name);
            strcpy(courier.receiver_no, receiver_no);

            addCourier(courier);

            break;
        }
        case 2:
        {
            if (courier.courier_status == 1)
            {
                cancelCourier(courier);
                printf("Courier is cancelled successfully!!!\n");
            }
            else
            {
                printf("You are not able to cancel this courier now!!\n");
            }
            break;
        }

        case 3:
        {
            int status = check_status(courier);
            if (status == 0)
                printf("Courier had not been sent yet!!\n");
            else if (status == 1)
                printf("Courier is in sending process!!\n");
            else if (status == -1)
                printf("Courier has been cancelled by sender!\n");
            else if (status == 2)
                printf("Courier has been received succesfully to the receiver!\n");
            break;
        }
        }

        printf("Want to use any other functionality?\n Enter 1 for yes and 0 for no\n");
        int c;
        scanf("%d", &c);
        if (!c)
            break;
    }
    return 0;
}