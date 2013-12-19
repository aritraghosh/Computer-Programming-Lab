/* 
 * File:   main.c
 * Author: aghosh
 *
 * Created on 6 August, 2012, 2:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "packet.h"
#include "singly.h"
#include "doubly.h"
//extern typedef struct struct Packet1 struct Packet;
int menu() {
    int choice;
    printf("Please enter your choice\n"
            "1. Receiving a packet\n"
            "2. Sending a particular message\n"
            "3. Sending all messages from a particular sender\n"
            "4. Sending all messages from a particular receiver\n"
            "5. Printing all the messages currently in the buffer\n "
            "   To exit enter 0\n");
    printf("-------------------------------------------------\n");
    scanf("%d", &choice);
    return choice;
}

int main(int argc, char** argv) {
    int firstchoice = 0;
    int c = 1;
    printf("Enter 1 to use linear linked list and 2 to use circular doubly linked list.Enter 0 to exit\n");
    scanf("%d", &firstchoice);
    struct Packet *head;
    head = NULL;

    struct Packet *list;
    list = NULL;





    while (firstchoice != 0) {
        while (c != 0) {

            if (firstchoice == 1) {
                int choice = menu();


                while (choice != 0) {
                    switch (choice) {
                        case 1:
                            head = receivemessage(list, head);
                            printf("----------------\n");
                            break;
                        case 2:
                            head = sendmessage(head, head);
                            printf("----------------\n");
                            break;
                        case 3:
                            head = sendmessparticularsender(head, head);
                            printf("----------------\n");
                            break;
                        case 4:
                            head = sendmessparticularreceiver(head, head);
                            printf("----------------\n");
                            break;
                        case 5:
                            printallmessage(head);
                            printf("----------------\n");
                            break;
                        default:
                            printf("Please enter 1-5 only\n");
                    
                   
                    }
                    break;
                }
                
            } 
            else if (firstchoice == 2) {



                int choice2 = menu();
                while (choice2 != 0) {
                    switch (choice2) {
                        case 1:
                            head = receivemessage2(list, head);
                            printf("----------------\n");
                            break;
                        case 2:
                            head = sendmessage2(head, head);
                            printf("----------------\n");
                            break;
                        case 3:
                            head = sendmessageparticularsender(head, head);
                            printf("----------------\n");
                            break;
                        case 4:
                            head = sendmessageparticularreceiver(head, head);
                            printf("----------------\n");
                            break;
                        case 5:
                            printallmessage2(head);
                            printf("----------------\n");
                            break;
                        default:
                            printf("Please enter 1-5 only\n");
                    }
                    break;
                }
            } 
            else {
                printf("Please enter 1 or 2 only\n");
            }

            printf("To continue press any number else press 0\n");

            scanf("%d", &c);
            if (c == 0)
                firstchoice = 0;
        }
    }
}
