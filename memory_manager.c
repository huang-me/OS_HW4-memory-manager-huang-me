#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define write 1
#define read 0

struct node
{
    int pfi;
    int reference;
    struct node* next;
    struct node* pre;
};

void deleteNode(struct node* head_ref, struct node* del)
{
    /* base case */
    if (head_ref == NULL || del == NULL)
        return;

    /* If node to be deleted is head node */
    if (head_ref == del)
        head_ref = del->next;

    /* Change next only if node to be deleted is NOT the last node */
    if (del->next != NULL)
        del->next->pre = del->pre;
    else
        del->pre->next = NULL;

    /* Change prev only if node to be deleted is NOT the first node */
    if (del->pre != NULL)
        del->pre->next = del->next;

    return;
}

void fifo(void)
{
    int page_num,frame_num;
    char file_read[50];
    char *token;

    // get the number of virtual page
    if(fgets(file_read,sizeof(file_read),stdin) == NULL)
    {
        printf("error while getting number of virtual page\n");
        return;
    }
    token = strtok(file_read,":");
    token = strtok(NULL,"\n");
    page_num = atoi(token);

    // get the number of physical frame
    if(fgets(file_read,sizeof(file_read),stdin) == NULL)
    {
        printf("error while reading file\n");
        return;
    }
    token = strtok(file_read,":");
    token = strtok(NULL,"\n");
    frame_num = atoi(token);

    // create the structure to do the memory manage
    int disk[page_num], frame[frame_num];
    // initialize the array
    for(int i=0; i<page_num; i++)
        disk[i] = -1;
    for(int i=0; i<frame_num; i++)
        frame[i] = -1;

    // ---trace---
    if(fgets(file_read,sizeof(file_read),stdin));

    int id;
    int miss_time=0, hit_time=0;
    int frame_ptr=0, exist, where;
    // while do the memory menage in FIFO
    while(fgets(file_read,sizeof(file_read),stdin))
    {
        token = strtok(file_read," ");
        token = strtok(NULL," ");
        id = atoi(token);
        // test if the frame i want is in the array
        for(int i=0; i<frame_num; i++)
        {
            if(id == frame[i])
            {
                exist = 1;
                where = i;
            }
        }
        // already in array
        if(exist)
        {
            hit_time++;
            printf("Hit, %d=>%d\n",id,where);
        }
        // not in the array
        else
        {
            miss_time++;
            int old_id=frame[frame_ptr];
            frame[frame_ptr] = id;

            int disk_id=-1, disk_old=-1;
            // if there's page in the frame
            if(old_id != -1)
            {
                // put the old page into disk
                for(int i=0; i<page_num; i++)
                {
                    if(disk[i] == -1)
                    {
                        disk[i] = old_id;
                        disk_old = i;
                        break;
                    }
                }
            }
            // find where the page insert were before
            for(int i=0; i<page_num; i++)
            {
                if(disk[i] == id)
                {
                    disk_id = i;
                    disk[disk_id] = -1;
                    break;
                }
            }
            // print the result
            printf("Miss, %d, %d>>%d, %d<<%d\n",frame_ptr,old_id,disk_old,id,disk_id);
            frame_ptr++;
            frame_ptr %= frame_num;
        }
        exist = 0;
    }
    // calculate page fault rate
    float page_fault;
    page_fault = miss_time;
    page_fault /= hit_time + miss_time;
    printf("Page Fault Rate: %.3f\n",page_fault);
}

void esca(void)
{
    int page_num,frame_num;
    char file_read[50];
    char *token;

    // get the number of virtual page
    if(fgets(file_read,sizeof(file_read),stdin) == NULL)
    {
        printf("error while getting number of virtual page\n");
        return;
    }
    token = strtok(file_read,":");
    token = strtok(NULL,"\n");
    page_num = atoi(token);

    // get the number of physical frame
    if(fgets(file_read,sizeof(file_read),stdin) == NULL)
    {
        printf("error while reading file\n");
        return;
    }
    token = strtok(file_read,":");
    token = strtok(NULL,"\n");
    frame_num = atoi(token);

    // create the structure to do the memory manage
    int disk[page_num], frame[frame_num][2];
    // initialize the array
    for(int i=0; i<page_num; i++)
        disk[i] = -1;
    for(int i=0; i<frame_num; i++)
    {
        frame[i][0] = -1;
        frame[i][1] = 0;
    }

    // ---trace---
    if(fgets(file_read,sizeof(file_read),stdin));
    // define

    int ptr=-1, hit_time=0, miss_time=0;
    int point=-1;

    // memory manager in ESCA
    while(fgets(file_read,sizeof(file_read),stdin))
    {
        // get the id of the next page
        char *line;
        int act;
        line = strtok(file_read," ");
        if(!strcmp(line,"Write"))
            act = write;
        else
            act = read;
        line = strtok(NULL,"\n");
        int id, exist=0;
        id = atoi(line);
        for(int i=0; i<frame_num; i++)
        {
            if(frame[i][0] == id)
            {
                exist = 1;
                hit_time++;
                if(frame[i][1] == 11);
                else if(act == write)
                    frame[i][1] = 11;
                else if(frame[i][1] == 1 && act == read)
                    frame[i][1] = 11;
                else
                    frame[i][1] = 10;
                printf("Hit, %d=>%d\n",id,i);
                break;
            }
        }
        // frame not in page
        if(!exist)
        {
            miss_time++;
            int old_id=-1, done=0, have_space=-1;
            int old_disk=-1, id_disk=-1;

            for(int i=0; i<frame_num; i++)
            {
                if(frame[i][0] == -1)
                {
                    have_space = i;
                    break;
                }
            }
            if(have_space != -1)
            {
                frame[have_space][0] = id;
                if(act == write)
                    frame[have_space][1] = 11;
                else
                    frame[have_space][1] = 10;
            }
            else
            {
                // find 00
                for(int i=1; i<=frame_num; i++)
                {
                    point=(ptr+i)%frame_num;
                    if( frame[point][1] == 0 )
                    {
                        old_id = frame[point][0];
                        frame[point][0] = id;
                        if(act == write)
                            frame[point][1] = 11;
                        else
                            frame[point][1] = 10;
                        ptr = point;
                        done = 1;
                        break;
                    }
                }
                if(!done)
                {
                    // find 01
                    for(int i=1; i<=frame_num; i++)
                    {
                        point=(ptr+i)%frame_num;
                        if( frame[point][1] == 1 )
                        {
                            old_id = frame[point][0];
                            frame[point][0] = id;
                            if(act == write)
                                frame[point][1] = 11;
                            else
                                frame[point][1] = 10;
                            ptr = point;
                            done = 1;
                            break;
                        }
                        else
                        {
                            if(frame[point][1] == 10)
                                frame[point][1] = 0;
                            else
                                frame[point][1] = 1;
                        }

                    }
                }
                if(!done)
                {
                    // find 00
                    for(int i=1; i<=frame_num; i++)
                    {
                        point=(ptr+i)%frame_num;
                        if( frame[point][1] == 0 )
                        {
                            old_id = frame[point][0];
                            frame[point][0] = id;
                            if(act == write)
                                frame[point][1] = 11;
                            else
                                frame[point][1] = 10;
                            ptr = point;
                            done = 1;
                            break;
                        }
                    }
                }
                if(!done)
                {
                    // find 01
                    for(int i=1; i<=frame_num; i++)
                    {
                        point=(ptr+i)%frame_num;
                        if( frame[i][1] == 1 )
                        {
                            old_id = frame[point][0];
                            frame[point][0] = id;
                            if(act == write)
                                frame[point][1] = 11;
                            else
                                frame[point][1] = 10;
                            ptr = point;
                            break;
                        }
                    }
                }


                // put the old frame into disk
                if(old_id != -1)
                {
                    for(int i=0; i<page_num; i++)
                    {
                        if(disk[i] == -1)
                        {
                            disk[i] = old_id;
                            old_disk = i;
                            break;
                        }
                    }
                }
            }
            for(int i=0; i<page_num; i++)
            {
                if(disk[i] == id)
                {
                    id_disk = i;
                    disk[i] = -1;
                }
            }

            if(have_space != -1)
                printf("Miss, %d, %d>>%d, %d<<%d\n",have_space,old_id,old_disk,id,id_disk);
            else
                printf("Miss, %d, %d>>%d, %d<<%d\n",point,old_id,old_disk,id,id_disk);

        }
    }
    float page_fault=miss_time;
    page_fault /= (miss_time+hit_time);
    printf("Page Fault Rate: %.3f\n",page_fault);
    return;
}

void slru(void)
{
    int page_num,frame_num;
    char file_read[50];
    char *token;
    int miss_time=0, hit_time=0;

    // get the number of virtual page
    if(fgets(file_read,sizeof(file_read),stdin) == NULL)
    {
        printf("error while getting number of virtual page\n");
        return;
    }
    token = strtok(file_read,":");
    token = strtok(NULL,"\n");
    page_num = atoi(token);

    // get the number of physical frame
    if(fgets(file_read,sizeof(file_read),stdin) == NULL)
    {
        printf("error while reading file\n");
        return;
    }
    token = strtok(file_read,":");
    token = strtok(NULL,"\n");
    frame_num = atoi(token);
    int frame[frame_num][2], disk[page_num];
    for(int i=0; i<frame_num; i++)
    {
        frame[i][0] = -1;
        frame[i][1] = 0;
    }
    for(int i=0; i<page_num; i++)
    {
        disk[i] = -1;
    }

    // ---Trace---
    if(fgets(file_read,sizeof(file_read),stdin) == NULL)
    {
        printf("error reading trace\n");
        return;
    }

    // intiger to memorize how many frame are there in active list & inactive list
    int frame_in_active=0, frame_in_inactive=0;
    // slot of active & inactive list
    int inactive_num=ceil((float)frame_num/2), active_num=floor((float)frame_num/2);
    // linked list of active & inactive
    struct node *active_head = (struct node*)malloc(sizeof(struct node*)),
                 *active_tail = active_head,
                  *inactive_head = (struct node*)malloc(sizeof(struct node*)),
                   *inactive_tail = (struct node*)malloc(sizeof(struct node*)),
                    *remove = (struct node*)malloc(sizeof(struct node*)),
                     *temp = (struct node*)malloc(sizeof(struct node*));

    // pointer point to array
    int ptr=0;

    //read the index
    while(fgets(file_read,sizeof(file_read),stdin))
    {
        // get the id of frame
        char *index;
        index = strtok(file_read," ");
        index = strtok(NULL,"\n");
        int id = atoi(index);
        // printf("=%d\n",id);
        int exist=0, list, space=frame_num;
        // find whether the frame is in list
        for(int i=0; i<frame_num; i++)
        {
            // printf("frame[%d] = %d;%d\n",i,frame[i][0],frame[i][1]);                  // test
            if(frame[i][0] == id)
            {
                exist = 1;
                list = frame[i][1];
                ptr = i;
                printf("Hit, %d=>%d\n",id,ptr);
            }
        }

        int old_id=-1, old_disk=-1, id_disk=-1;
        if(exist) // frame already in list
        {
            hit_time++;
            if(list)   // in active list
            {
                temp = (struct node*)malloc(sizeof(struct node*));
                temp = active_head;
                while(temp)
                {
                    if(temp->pfi == ptr)
                        break;
                    temp = temp->next;
                }
                temp->reference = 1;
                if(temp->next && temp->pre)      //delete from active list
                {
                    temp->pre->next = temp->next;
                    temp->next->pre = temp->pre;
                    temp->next = active_head;
                    active_head->pre = temp;
                    temp->pre = NULL;
                    active_head = temp;
                }
                else if(temp->next);
                else if(temp->pre)
                {
                    temp->pre->next = NULL;
                    active_tail = active_tail->pre;
                    temp->next = active_head;
                    active_head->pre = temp;
                    temp->pre = NULL;
                    active_head = temp;
                }
                else
                {
                    temp->reference = 1;
                }
            }
            else  // in inactive list
            {
                temp = (struct node*)malloc(sizeof(struct node*));
                temp = inactive_head;
                while(temp)
                {
                    if(temp->pfi == ptr)
                        break;
                    temp = temp->next;
                }
                if(temp->reference)  // reference bit 1
                {
                    if(temp->next && temp->pre)      //delete from inactive list
                    {
                        temp->pre->next = temp->next;
                        temp->next->pre = temp->pre;
                    }
                    else if(temp->next)
                    {
                        temp->next->pre = NULL;
                        inactive_head = inactive_head->next;
                    }
                    else if(temp->pre)
                    {
                        temp->pre->next = NULL;
                        inactive_tail = inactive_tail->pre;
                    }

                    if(frame_in_active == 0)        // add to active list
                    {
                        temp->next = NULL;
                        temp->pre = NULL;
                        temp->reference = 0;
                        active_head = temp;
                        active_tail = temp;
                        frame[ptr][1] = 1;
                    }
                    else if(frame_in_active == active_num)
                    {
                        while(active_tail->reference)
                        {
                            remove = active_tail;
                            active_tail = active_tail->pre;
                            active_tail->next = NULL;

                            remove->reference = 0;
                            remove->next = active_head;
                            active_head->pre = remove;
                            active_head = remove;
                            active_head->pre = NULL;
                        }

                        remove = active_tail;
                        active_tail = active_tail->pre;
                        active_tail->next = NULL;

                        remove->next = inactive_head;
                        inactive_head->pre = remove;
                        remove->pre = NULL;
                        inactive_head = remove;

                        frame[remove->pfi][1] = 0;
                        frame_in_active--;
                        frame_in_inactive++;
                        temp->reference = 0;
                        temp->next = active_head;
                        active_head->pre = temp;
                        temp->pre = NULL;
                        active_head = temp;
                        frame[ptr][1] = 1;
                    }
                    else
                    {
                        temp->reference = 0;
                        temp->next = active_head;
                        active_head->pre = temp;
                        temp->pre = NULL;
                        active_head = temp;
                        frame[ptr][1] = 1;
                    }

                    frame_in_active++;
                    frame_in_inactive--;
                }
                else    // reference bit 0
                {
                    if(temp->next && temp->pre)      //delete from inactive list
                    {
                        temp->pre->next = temp->next;
                        temp->next->pre = temp->pre;
                        temp->reference = 1;
                        temp->next = inactive_head;
                        temp->pre = NULL;
                        inactive_head->pre = temp;
                        inactive_head = temp;
                    }
                    else if(temp->next)
                        temp->reference = 1;
                    else if(temp->pre)
                    {
                        temp->pre->next = NULL;
                        inactive_tail = inactive_tail->pre;
                        temp->reference = 1;
                        temp->next = inactive_head;
                        temp->pre = NULL;
                        inactive_head->pre = temp;
                        inactive_head = temp;
                    }
                }
            }
        }
        else // not in list
        {
            miss_time++;
            if(frame_in_inactive == 0)   // first frame in inactive list
            {
                space = 0;
                temp = inactive_head;
                temp->next = NULL;
                temp->pre = NULL;
                temp->pfi = space;
                temp->reference = 1;
                inactive_tail = temp;
                frame[space][0] = id;
                frame[space][1] = 0;  // in inactive
                frame_in_inactive++;
            }
            else if(frame_in_inactive == inactive_num)
            {
                temp = (struct node*)malloc(sizeof(struct node*));
                temp = inactive_tail;
                while(temp->reference == 1)
                {
                    temp->reference = 0;
                    inactive_tail = inactive_tail->pre;
                    inactive_tail->next = NULL;

                    temp->next = inactive_head;
                    inactive_head->pre = temp;
                    inactive_head = temp;
                    inactive_head->pre = NULL;
                    temp = inactive_tail;
                }
                old_id = frame[temp->pfi][0];
                frame[temp->pfi][0] = -1;
                frame[temp->pfi][1] = 0;
                space = temp->pfi;

                if(temp->next && temp->pre)      //delete from inactive list
                {
                    temp->pre->next = temp->next;
                    temp->next->pre = temp->pre;
                }
                else if(temp->next)
                {
                    temp->next->pre = NULL;
                    inactive_head = inactive_head->next;
                }
                else if(temp->pre)
                {
                    temp->pre->next = NULL;
                    inactive_tail = inactive_tail->pre;
                }

                frame_in_inactive--;

                for(int i=0; i<frame_num; i++)
                {
                    if(frame[i][0] == -1)
                    {
                        space = i;
                        break;
                    }
                }

                temp = (struct node*)malloc(sizeof(struct node*));
                temp->pre = NULL;
                temp->next = inactive_head;
                inactive_head->pre = temp;
                temp->reference = 1;
                temp->pfi = space;
                inactive_head = temp;
                frame[space][0] = id;
                frame[space][1] = 0;  // in inactive
                frame_in_inactive++;
            }
            else
            {
                for(int i=0; i<frame_num; i++)
                {
                    if(frame[i][0] == -1)
                    {
                        space = i;
                        break;
                    }
                }

                temp = (struct node*)malloc(sizeof(struct node*));
                temp->pre = NULL;
                temp->next = inactive_head;
                inactive_head->pre = temp;
                temp->reference = 1;
                temp->pfi = space;
                inactive_head = temp;
                frame[space][0] = id;
                frame[space][1] = 0;  // in inactive
                frame_in_inactive++;
            }
            if(old_id == -1);
            else
            {
                for(int i=0; i<page_num; i++)
                {
                    if(disk[i] == -1)
                    {
                        disk[i] = old_id;
                        old_disk = i;
                        break;
                    }
                }

            }
            // find where the id were
            for(int i=0; i<page_num; i++)
            {
                if(disk[i] == id)
                {
                    disk[i] = -1;
                    id_disk = i;
                }
            }
            printf("Miss, %d, %d>>%d, %d<<%d\n",space,old_id,old_disk,id,id_disk);
        }
    }


    float fault = miss_time;
    fault /= (miss_time+hit_time);
    printf("Page Fault Rate: %.3f\n",fault);

}

int main(int argc,char* argv[])
{
    char index[100];
    //read the input file
    if(fgets(index,sizeof(index),stdin) == NULL)
    {
        printf("error reeading file\n");
        return 0;
    }
    //read what policy the input file use
    if(!strcmp(index,"Policy: FIFO\n"))
    {
        fifo();
    }
    else if(!strcmp(index,"Policy: ESCA\n"))
    {
        esca();
    }
    else if(!strcmp(index,"Policy: SLRU\n"))
    {
        slru();
    }
    return 0;
}
