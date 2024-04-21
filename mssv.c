#include "mssv.h"

int main(int argc, char** argv)
{
    pthread_t children[4];

    sol = readSol(argv[0]);
    row = (int*)calloc(9, sizeof(int));
    col = (int*)calloc(9, sizeof(int));
    sub = (int*)calloc(9, sizeof(int));
    delay_time = argv[1];

    sem_t* parent_blocker;
    sem_init(parent_blocker,0, -4);

    for(int ii=0; ii<4; ii++)
    {
        if(!pthread_create(&children[ii], NULL, mssv_child_main, ii*3))
        {
            printf("failed to create child thread %d\n", ii+1);
            return 1;
        }
    }

    sem_wait(parent_blocker);

    for(int ii=0; ii<4; ii++)
    {
        if(!pthread_join(children[ii], NULL))
        {
            printf("failed to terminate thread %d\n", ii+1);
            return 1;
        }
    }

    int fault_count = 0;
    char* print_str = "";
    char* temp = ""; 
    for(int ii=0; ii<9; ii++)
    {
        if(!ii%3)
        {
            if(ii)
            {
                strncpy(temp, print_str, strlen(print_str)-3);
                strcpy(print_str, temp);
                switch(fault_count)
                {
                    case 0:
                        strcat(print_str, " valid");
                    break;
                    case 1:
                        strcat(print_str, " is invalid");
                    break;
                    default:
                        strcat(print_str, " are invalid");
                    break;
                }
                strcat(print_str, "\n");
            }
            fault_count = 0;
            sprintf(temp, "Thread ID-%d:", ii+1);
            strcat(print_str, temp);
        }
        if(!row[ii])
        {
            sprintf(temp, " row %d, ", ii+1);
            strcat(print_str, temp);
            fault_count++;
        }
        if(!sub[ii])
        {
            sprintf(temp, " sub-grid %d, ", ii+1);
            strcat(print_str, temp);
            fault_count++;
        }
    }
    strncpy(temp, print_str, strlen(print_str)-3);
    strcpy(print_str, temp);
    switch(fault_count)
    {
        case 0:
            strcat(print_str, " valid");
        break;
        case 1:
            strcat(print_str, " is invalid");
        break;
        default:
            strcat(print_str, " are invalid");
        break;
    }
    strcat(print_str, "\n");

    fault_count = 0;
    strcat(print_str, "Thread ID-4:");
    for(int ii=0; ii<9; ii++)
    {
        if(!col[ii])
        {
            sprintf(temp, "column %d, ", ii+1);
            strcat(print_str, temp);
            fault_count++;
        }
    }
    switch(fault_count)
    {
        case 0:
            strcat(print_str, " valid");
        break;
        case 1:
            strcat(print_str, " is invalid");
        break;
        default:
            strcat(print_str, " are invalid");
        break;
    }
    sprintf(temp, "There are in total %d valid rows, columns, and sub-grids, and ", counter);
    strcat(print_str, temp);
    if(counter == 27)
    {
        strcat(print_str, "thus the solution is valid\n");
    }else{
        strcat(print_str, " and the solution is invalid\n");
    }

    printf(print_str);

    freeSol(sol);
    free(row);
    free(col);
    free(counter);
    sem_destroy(parent_blocker);

    return 0;
}