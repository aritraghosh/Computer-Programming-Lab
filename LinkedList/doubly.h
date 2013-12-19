/* 
 * File:   doubly.h
 * Author: aghosh
 *
 * Created on 19 August, 2012, 8:07 PM
 */


#ifndef DOUBLY_H
#define	DOUBLY_H


//        extern typedef struct struct Packet1 struct Packet;

    //prototype of all the functions .The names are self explanatory

   struct Packet *receivemessage2(struct Packet* , struct Packet*);
    struct Packet *sendmessage2(struct Packet *p, struct Packet *h);
   struct Packet *sendmessageparticularsender(struct Packet *p, struct Packet *h);
   struct Packet *sendmessageparticularreceiver(struct Packet *p, struct Packet *h);
    void printallmessage2(struct Packet* h);






#endif	/* DOUBLY_H */

