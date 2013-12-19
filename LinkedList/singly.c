#include "singly.h"
#include <stdio.h>
#include <stdlib.h>
#include "packet.h"


//All the functions have the pointer to list and head as input and have head as output except the printallmessage



//     function for receiving a packet by keying in a message, sender’s
//address and receiver’s address and the packet must get added to the buffer.

//extern typedef struct struct Packet1 struct Packet;

struct Packet* receivemessage(struct Packet *list, struct Packet *head) {
    list = (struct Packet *) malloc(sizeof (struct Packet));

    printf("Enter the message\n");
    scanf("%s", list->message);
    printf("Enter the sender's address\n");
    scanf("%s", list->senderaddress);
    printf("Enter receiver's address\n");
    scanf("%s", list->receiveaddress);

    if (head == NULL) {
        list->next = NULL;
    }
    else {
        list->next = head;

    }
    head = list;

    list = list->next;
    return (head);
}


















//sending a packet by (i) searching for a particular message, (ii) printing a
//sent message, and then (iii) deleting it from the buffer.

struct Packet* sendmessage(struct Packet *list, struct Packet *head) {

    char searchmessage[200], raddress[50];
    struct Packet *prev;
    prev = NULL;
    printf("Enter message to search\n");
    scanf("%s", searchmessage);
    printf("Enter the address of the receiver\n");
    scanf("%s", raddress);

    int flag = 0;

    while (list != NULL) {
        if (strcmp(list->message, searchmessage) == 0) {
            printf("The message %s has been successfully sent  to %s\n", searchmessage, raddress);
            if (prev == NULL) {
                head = list->next;
                //return head;
            } else // to delete the struct Packet after sending
                prev->next = list->next;
            free(list);
            flag = 1;
            if (flag == 1)break;
        } else {
            prev = list;
            list = list->next; //continue checking for the message
        }



    }
    if (flag == 0) {
        printf("Message not found\n");
    }
    return (head);
}





//function to send all messages from a particular sender 

struct Packet *sendmessparticularsender(struct Packet *list, struct Packet *head) {
    struct Packet *prev;
    prev = NULL;
    list = head;
    int flag = 0;
    char sadress[50];
    printf("Enter address of the sender\n");
    scanf("%s", sadress);
    while (list != NULL) {
        if (strcmp(list->senderaddress, sadress) == 0) {
            flag = 1;
            printf("%s\n", list->message);


            if (prev == NULL) {
                head = list->next;
            } else
                prev->next = list->next;
            free(list);

        } else {

            prev = list;
        }
        list = list->next;

    }
    if (flag == 1)printf("The above messages of %s have been sent\n");
    if (flag == 0)printf("Such a sender does not exist\n");
    return (head);
}

//function to send all messages from a particular reciever

struct Packet *sendmessparticularreceiver(struct Packet *list, struct Packet *head) {
    struct Packet *prev;
    prev = NULL;
    list = head;
    int flag = 0;
    char radress[50];
    printf("Enter address of the receiver\n");
    scanf("%s", radress);
    while (list != NULL) {
        if (strcmp(list->receiveaddress, radress) == 0) {
            flag = 1;
            printf("%s\n", list->message);


            if (prev == NULL) {
                head = list->next;
            } else
                prev->next = list->next;
            free(list);

        } else {

            prev = list;
        }
        list = list->next;

    }
    if (flag == 1)printf("The above messages of %s have been sent\n");
    if (flag == 0)printf("Such a receiver does not exist\n");
    return (head);
}




//function to print all the messages in the buffer

void printallmessage(struct Packet *head) {
    int flag = 0;
    struct Packet *temp3;
    temp3 = head;
    printf("The messages in the buffer are\n");
    while (temp3 != NULL) {

        flag = 1;
        printf("%s\n", temp3->message);
        temp3 = temp3->next;

    }
    if (flag == 0)printf("Sorry,The buffer is empty\n");

}






