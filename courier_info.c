#include "./include/courier_utils.h"

int main()
{
    int choice;

    while (1)
    {
        printf("**********************************************\n");
        printf("Enter 1 for adding new courier.\n");
        printf("Enter 2 for cancelling current courier.\n");
        printf("Enter 3 for checking current status of courier.\n");
        printf("Enter 4 for logging out.\n");
        printf("Enter 5 to see list all Couriers.\n");
        printf("**********************************************\n\n");
        struct Courier courier;

        courier.courier_status = 0;
        printf("Please enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            printf("Welcome again!!\n");
            char courier_id[STR_LEN], sender_name[STR_LEN], sender_no[STR_LEN], receiver_name[STR_LEN], address_receiver[STR_LEN], receiver_no[STR_LEN], courier_mssg[STR_LEN], attatchment_type[STR_LEN];
            getchar();
            printf("Please enter sender name.\n");
            scanf("%[^\n]s", sender_name);
            getchar();
            printf("Please enter contact number of sender.\n");
            scanf("%[^\n]s", sender_no);
            getchar();
            printf("Please enter receiver name.\n");
            scanf("%[^\n]s", receiver_name);
            getchar();
            printf("Please enter contact number of receiver.\n");
            scanf("%[^\n]s", receiver_no);
            getchar();
            printf("Please enter full address of receiver.\n");
            scanf("%[^\n]s", address_receiver);
            getchar();
            printf("Please enter message to be attatched with courier.\n");
            scanf("%[^\n]s", courier_mssg);
            getchar();
            printf("Please enter type of attatchment(courier).\n");
            scanf("%[^\n]s", attatchment_type);
            getchar();
            // copying data into struct
            sprintf(courier_id, "%lld", generate_random_courier_id()); // to convert int into string;
            strcpy(courier.courrier_id, courier_id);
            strcpy(courier.sender_name, sender_name);
            strcpy(courier.sender_no, sender_no);
            strcpy(courier.receiver_name, receiver_name);
            strcpy(courier.receiver_no, receiver_no);
            strcpy(courier.receiver_address, address_receiver);
            strcpy(courier.couier_message, courier_mssg);
            strcpy(courier.attachment_type, attatchment_type);
            courier.courier_status = 0;
            create_thread(courier);
            break;
        }
        case 2:
        {
            char id[STR_LEN], new_status[STR_LEN] = "-1";
            printf("Enter courier id that you want to cancel : ");
            scanf("%s", id);
            cancelCourier(id);
            break;
        }

        case 3:
        {
            printf("Plese enter the courrier ID of your courrier: \n");
            char id[STR_LEN];
            scanf("%s", id);
            int status;
            int flag = find_courrier(id, &status);
            if (flag)
            {
                printf("Current status of Courrier is %d\n", status);
            }
            break;
        }
        case 4:
        {
            printf("You are logged out successfully!\n");
            startExec(); // start the process again from user login/registration
            break;
        }
        case 5:
        {
            char courier_id[STR_LEN];
            getchar();
            printf("Please enter Courrier ID ");
            scanf("%[^\n]s", courier_id);
            printCourierInfo(courier_id);
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