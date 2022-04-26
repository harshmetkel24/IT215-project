#include "./include/courier_utils.h"

void startExec()
{
    int pid;
    pid = fork();
    if (pid == 0)
    { // child process will compile the file courier_info.c;
        char *prog = "gcc";
        char *arg1 = "start.c";
        char *arg2 = "-o";
        char *arg3 = "start.out";
        execlp(prog, prog, arg1, arg2, arg3, NULL);
    }
    else
    { // parent will wait for child to compile file then it will execute the file;
        int childPid, status;
        childPid = wait(&status);
        char *run = "./start.out";
        execlp(run, run, NULL);
    }
}
long long generate_random_courier_id()
{
    struct timeval te;
    gettimeofday(&te, NULL);                                         // get current time
    long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

void update_status(char id[], char new_status[])
{
    int status;
    if (!find_courrier(id, &status))
    {
        printf("There is no courier with ID %s.\n\n", id);
        return;
    }
    FILE *fin = fopen("./courier_info.csv", "r");
    FILE *fout = fopen("./update_courier.csv", "w+");
    if (fin == NULL)
    {
        printf("Unable to open csv file of courier!!\n");
        return;
    }
    if (fout == NULL)
    {
        perror("Unable to open csv file of update courier!!\n");
        return;
    }
    char buffer[STR_LEN];
    int row = 0, column = 0;
    int flag = false;
    while (fgets(buffer, STR_LEN, fin))
    {
        column = 0;
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
                strcpy(row_string, new_status);
                fprintf(fout, " %s\n", new_status); // imp for getting new line after update;
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
    fclose(fin), fclose(fout);
    int ret = remove("./courier_info.csv");
    if (ret)
    {
        perror("Unable to delete the file\n");
    }
    int value = rename("update_courier.csv", "courier_info.csv");
    if (value)
    {
        perror("Error");
    }
}

void cancelCourier(char id[])
{
    int status;
    int found = find_courrier(id, &status);
    if (found == false)
    {
        printf("There is no Courier with ID %s.\n", id);
        return;
    }
    // if courier is still under process
    if (status == 0)
    {
        char newStatus[STR_LEN] = "2";
        update_status(id, newStatus);
        printf("Courrier with ID %s is cancelled successfully.\n", id);
    }
    // courier sent
    else
    {
        printf("Courier already deliverd!\nCannot be cancelled.\n");
    }
}

int check_status(struct Courier current_courier)
{
    int status;
    find_courrier(current_courier.courrier_id, &status);
    return status;
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
    return false;
}

void printCourierInfo(char id[])
{
    FILE *fp = fopen("./courier_info.csv", "r");
    if (fp == NULL)
    {
        printf("Unable to open csv file of courier!!\n");
        return;
    }
    char buffer[STR_LEN];
    int row = 0, column = 0;
    int flag = false;
    while (fgets(buffer, STR_LEN, fp))
    {
        column = 0;
        ++row;
        if (row == 1)
        {
            printf("Courier ID, Sender, Sender mob, Receiver, Receiver mob, Receiver Address,  Message,  Courrier Status\n\n");
            continue;
        }
        char *row_string = strtok(buffer, ","); // splitting around
        while (row_string)
        {
            ++column;
            printf("%s, ", row_string);
            row_string = strtok(NULL, ",");
        }
    }
    fclose(fp);
}

void *addCourier(void *arg)
{
    struct Courier *courrier = arg;
    FILE *fp = fopen("./courier_info.csv", "a+");
    if (fp == NULL)
    {
        printf("Unable to open csv file of courier!!\n");
        pthread_exit(0); // to terminate only the current thread
    }
    fprintf(fp, "%s, %s, %s, %s, %s, %s, %s, %s, %d\n", courrier->courrier_id, courrier->sender_name, courrier->sender_no, courrier->receiver_name, courrier->receiver_no, courrier->receiver_address, courrier->couier_message, courrier->attachment_type, courrier->courier_status);
    fclose(fp);
    printf("Courier created successfully.\n\n");
    if (fork() == 0)
    {
        printf("Your Courrier id is %s.\n\n", courrier->courrier_id);
        sleep(30);
        int status;
        find_courrier(courrier->courrier_id, &status);
        if (status != 2)
            update_status(courrier->courrier_id, "1"); // update status as sent
        pthread_exit(0);
    }
    else
    {
        printf("\n\n");
        execlp("./courier_info", "./courier_info", NULL);
    }
}

void create_thread(struct Courier courrier)
{
    pthread_t tid;
    pthread_create(&tid, NULL, addCourier, (void *)&courrier);
    pthread_join(tid, NULL);
    pthread_exit(0);
}
