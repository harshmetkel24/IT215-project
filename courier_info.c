#include "courier_utils.h"

int ct = 0;

void update_status(char id[], char new_status[])
{
    FILE *fin = fopen("./courier_info.csv", "r");
    FILE *fout = fopen("./update_courier.csv", "w+");
    if (fin == NULL)
    {
        printf("Unable to open csv file of courier!!\n");
        return;
    }
    if (fout == NULL)
    {
        printf("Unable to open csv file of update courier!!\n");
        return;
    }
    char buffer[STR_LEN];
    int row = 0, column = 0;
    int flag = false;
    while (fgets(buffer, STR_LEN, fin))
    {
        column = 0;
        char *row_string = strtok(buffer, ","); // splitting around ","
        while (row_string)
        {
            ++column;
            if (column == 1)
            {
                if (!strcmp(row_string, id))
                {
                    flag = true;
                }
            }
            if (flag && column == 9)
            {
                row_string = new_status;
                fprintf(fout, " %s\n", row_string); // imp for getting new line after update;
            }
            else if (column == 9)
            {
                fprintf(fout, "%s", row_string);
            }

            if (column != 9)
                fprintf(fout, "%s,", row_string);
            row_string = strtok(NULL, ",");
        }
    }
    int ret = remove("./courier_info.csv");
    if (ret == 0)
    {
        printf("File deleted successfully");
    }
    else
    {
        perror("Unable to delete the file");
    }
    int value = rename("update_courier.csv", "courier_info.csv");
    if (!value)
    {
        printf("%s", "File name changed successfully");
    }
    else
    {
        perror("Error");
    }
    fclose(fin), fclose(fout);
}
void cancelCourier(struct Courier current_courier)
{
    current_courier.courier_status = -1; // courier is cancelled
}
int check_status(struct Courier current_courier)
{
    return current_courier.courier_status;
}

int find_courrier(char id[], int *status)
{
    FILE *fp = fopen("./courier_info.csv", "r");
    if (fp == NULL)
    {
        printf("Unable to open csv file of courier!!\n");
        return false;
    }
    char buffer[STR_LEN];
    int row = 0, column = 0;
    int flag = false;
    while (fgets(buffer, STR_LEN, fp))
    {
        column = 0;
        ++row;
        if (row == 1)
            continue;                           // avoid printing the names of column
        char *row_string = strtok(buffer, ","); // splitting around
        while (row_string)
        {
            ++column;
            if (column == 1)
            {
                if (!strcmp(row_string, id))
                {
                    flag = true;
                }
            }
            if (flag && column == 9)
            {
                *status = atoi(row_string);
                fclose(fp);
                return true;
            }
            row_string = strtok(NULL, ",");
        }
    }
    fclose(fp);
    printf("No courrier with courrier ID %s found!\n", id);
    return false;
}

void handleCancel(int sig)
{
    printf("Thread with tid %u received SIGINT signal.\n", (unsigned int)pthread_self());
    if (cancel == true)
    {
        printf("Courrier sending on thread %u is cancelled.\n", (unsigned int)pthread_self());
        pthread_exit(0);
    }
}

void *addCourier(void *arg)
{
    struct Courier *courrier = arg;
    printf("Current thread id is %u.\n", (unsigned int)pthread_self());
    signal(SIGINT, handleCancel);
    FILE *fp = fopen("./courier_info.csv", "a+");
    if (fp == NULL)
    {
        printf("Unable to open csv file of courier!!\n");
        pthread_exit(0); // to terminate only the current thread
    }
    fprintf(fp, "%s, %s, %s, %s, %s, %s, %s, %s, %d\n", courrier->courrier_id, courrier->sender_name, courrier->sender_no, courrier->receiver_name, courrier->receiver_no, courrier->receiver_address, courrier->couier_message, courrier->attachment_type, courrier->courier_status);
    fclose(fp);
    sleep(10); // sleep the process for 60 secs
    // after completion of delay we can't cancel
    /**
     * @note even amount of delay we need can be taken from user while sending courier
     */
    if (cancel == false)
        update_status(courrier->courrier_id, "-1"); // update status to sent
    else
        update_status(courrier->courrier_id, "1"); // update status to cancelled
    printf("New data for courier is  added successfully!!\n");
    printf("thread with tid %u exited\n", (unsigned int)pthread_self());
    pthread_exit(0);
}

void create_thread(struct Courier courrier)
{
    pthread_t tid;
    pthread_create(&tid, NULL, addCourier, (void *)&courrier);
    pthread_join(tid, NULL);
    pthread_exit(0);
    // we can send whether couurier is cancelled or not
    // 1 for cancelling courrier
    // 0 for successfull addition of courrier
}

int main()
{
    int choice;

    while (1)
    {
        // add go to dashboard code
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
            // to convert int into string;
            sprintf(courier_id, "%d", ct);
            ct++;
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
            update_status(id, new_status);
            if (courier.courier_status == 0)
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
        }

        printf("Want to use any other functionality?\n Enter 1 for yes and 0 for no\n");
        int c;
        scanf("%d", &c);
        if (!c)
            break;
    }
    return 0;
}