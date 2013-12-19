/* 
 * File:   singly.h
 * Author: aghosh
 *
 * Created on 6 August, 2012, 3:35 PM
 */

#ifndef SINGLY_H
#define	SINGLY_H


#ifdef	__cplusplus
extern "C" {
#endif
 //   extern typedef struct struct Packet1 struct Packet;

    //prototype to all the functions
    struct Packet *receivemessage(struct Packet* , struct Packet*); //returns the head pointer
    struct Packet *sendmessage(struct Packet *p, struct Packet *h);
    struct Packet *sendmessparticularsender(struct Packet *p, struct Packet *h); //the function names are self explanatory
    struct Packet *sendmessparticularreceiver(struct Packet *p, struct Packet *h);
    void printallmessage(struct Packet *h);





#ifdef	__cplusplus
}
#endif

#endif	/* SINGLY_H */

