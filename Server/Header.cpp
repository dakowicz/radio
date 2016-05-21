//
// Created by Kamil on 2016-05-04.
//

#include <cstdio>
#include <stdexcept>
#include "Header.h"


Header::Header() {

}



Header::Header(uint8_t head[7]) {
    if(head[0]!=id_prot) {
        perror("Wrong protocol");
        throw std::invalid_argument("id_prot");
    }else if (head[1]>3){
        perror("Wrong protocol");
        throw std::invalid_argument("type");
    }
    type=head[1]; //Here is also the zero-tail
    parameters=head[2];
    length=head[3]<<24;
    length+=head[4]<<16;
    length+=head[5]<<8;
    length+=head[6];
}

void Header::createHeader(uint8_t t, uint8_t param, int l){
    type=t;
    parameters=param;
    length=l;
}

void Header::createHeaderConnect(bool start, bool end, int l){
    type=connect;
    parameters=(uint8_t)(start?1:0);
    parameters+=(uint8_t)(end?2:0);
    length=l;
}
void Header::createHeaderVote(bool cancel_vote, int l){
    type=votes;
    parameters=(uint8_t)(cancel_vote?1:0);
    parameters+=2;	//Since it's the client to server message
    length=l;
}

void Header::createHeaderList(bool ack, int l){
    type=votes;
    parameters=(uint8_t)(ack?1:0);
    length=l;
}

void Header::createHeaderStream(bool start, bool end, int l){
    type=votes;
    parameters=(uint8_t)(start?1:0);
    parameters+=(uint8_t)(end?2:0);
    length=l;
}

void Header::createHeaderFile(bool priority, uint8_t info_length, int l){// It's probably not used by server
    type=file;
    if(info_length<0)
        return;
    parameters=info_length;
    parameters+=(uint8_t)(priority?-128:0);
    length=l;
}

uint8_t *Header::createBuffer() {
    uint8_t *head = new uint8_t[7];
    head[0] = id_prot;
    head[1] = type;
    head[2] = parameters;
    head[3] = length>>24;
    head[4] = length>>16;
    head[5] = length>>8;
    head[6] = length;
    return head;
}


