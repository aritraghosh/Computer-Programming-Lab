


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "doubly.h"
#include "packet.h"



//All the functions have the head pointer and first pointer as the arguments and returns the head pointer except
//the printallmessage function
// function for receiving a packet by keying in a message, sender’s
//address and receiver’s address and the packet must get added to the buffer.
//extern typedef struct struct Packet1 struct Packet;


struct Packet *receivemessage2(struct Packet *list, struct Packet *head) {

    list = (struct Packet *) malloc(sizeof (struct Packet));
    printf("Enter the message\n");
    scanf("%s", list->message);
    printf("Enter the sender's address\n");
    scanf("%s", list->senderaddress);
    printf("Enter receiver's address\n");
    scanf("%s", list->receiveaddress);

    if (head == NULL) {
        head = list;
        list->next = list;
        list->prev = list;
    } else {
        list->next = head;

        list->prev = head->prev;

        head->prev->next = list;
        head->prev = list;
        head = list;
    }
    return (head);
    list = list->next;
}



//sending a packet by (i) searching for a particular message, (ii) printing a
//sent message, and then (iii) deleting it from the buffer.

struct Packet* sendmessage2(struct Packet *pointer, struct Packet *head) {
    int flag = 0;
    struct Packet *temp;
    temp=head;
    char searchmessage[200],raddress[50];
    printf("Please type the message to send\n");
    scanf("%s", searchmessage);
    printf("Enter the address of the receiver\n");
    scanf("%s",raddress);
   
    pointer = head;
    do {
         if (strcmp(pointer->message, searchmessage) == 0) {
            flag = 1;

            printf("The message %s has been successfully sent to %s\n",searchmessage,raddress);

            pointer->prev->next = pointer->next;
            pointer->next->prev = pointer->prev;
            if (pointer == head) {
                head = NULL;
                
                
            }
            free(pointer);
      

        }



       
         else
            pointer = pointer->next;
    } while (pointer != temp);

    if (flag == 0)
        printf("The message has not been found\n");
    return (head);

}


//function to send all messages from a particular sender

struct Packet* sendmessageparticularsender(struct Packet *pointer, struct Packet *head) {
    struct Packet *temp;
    temp = head;
    int flag = 0, temp1 = 0;
    char senderadd[50];
    printf("Enter the address of the sender\n");
    scanf("%s", senderadd);
    pointer = head;
    do {
        if (strcmp(pointer->senderaddress, senderadd) == 0) {
            flag = 1;

            printf("%s\n", pointer->message);

            pointer->prev->next = pointer->next;
            pointer->next->prev = pointer->prev;
            if (pointer == head) {
                head = head->next;
                temp = head;
                temp1 = 1;
            }
            free(pointer);
            if (temp1 == 1) {
                pointer = head;
            }

        }



        pointer = pointer->next;
    } while (pointer != temp);

    if (flag == 1)printf("The above messages of %s have been sent\n", senderadd);
    if (flag == 0)
        printf("The sender has not been found\n");
    return (head);
}


//function to send all messages from a particular reciever

struct Packet* sendmessageparticularreceiver(struct Packet *pointer, struct Packet *head) {
    struct Packet *temp;
    temp = head;
    int flag = 0, temp1 = 0;
    char radd[50];
    printf("Enter the address of the receiver\n");
    scanf("%s", radd);
    pointer = head;
    do {

        if (strcmp(pointer->receiveaddress, radd) == 0) {
            flag = 1;

            printf("%s\n", pointer->message);

            pointer->prev->next = pointer->next;
            pointer->next->prev = pointer->prev;
            if (pointer == head) {
                head = head->next;
                temp = head;
                temp1 = 1;
            }
            free(pointer);
            if (temp1 == 1) {
                pointer = head;
            }

        }


        pointer = pointer->next;
    } while (pointer != temp);

    if (flag == 1)printf("The above messages of %s have been sent\n", radd);
    if (flag == 0)
        printf("The receiver has not been found\n");
    return (head);
}



//function to print all the messages in the buffer

void printallmessage2(struct Packet *head) {

    struct Packet *temp;
    temp = head;
    if (head == NULL)
        printf("The buffer is empty\n");
    else {
        printf("The messages in the buffer are\n");
        do {

            printf("%s\n", temp->message);
            temp = temp->next;
        } while (temp != head);

    }
}