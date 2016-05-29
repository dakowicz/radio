
//
// Created by Kamil on 2016-05-04.
//

#include <cstdio>
#include <stdexcept>
#include "Header.h"

const int Header::HEADER_LENGTH = 7;

const unsigned char Header::connect = 0;
const unsigned char Header::stream = 1;
const unsigned char Header::votes = 2;
const unsigned char Header::file = 3;
const unsigned char Header::id_prot = 90;

Header *Header::createHeader(unsigned char *head) {
    if(head[0]!=id_prot||head[1]>3) {
        perror("Wrong protocol");
        return nullptr;
    }
    unsigned char type = head[1]; //Here is also the zero-tail
    unsigned char parameters = head[2];
    unsigned char length = head[3]<<24;
    length += head[4]<<16;
    length += head[5]<<8;
    length += head[6];
    return new Header(type, parameters, length);
}
Header * Header::createHeaderConnect(bool start, bool end, int l){

    unsigned char parameters=(unsigned char)(start?1:0);
    parameters+=(uint8_t)(end?2:0);

    return new Header(Header::connect, parameters, l);
}

Header * Header::createHeaderVote(bool cancel_vote, int l){

    unsigned char parameters=(unsigned char)(cancel_vote?1:0);
    parameters+=2;	//Since it's the client to server message
    return new Header(Header::votes, parameters, l);
}

Header * Header::createHeaderList(bool ack, int l){

    unsigned char parameters=(unsigned char)(ack?1:0);
    return new Header(Header::votes, parameters, l);
}


Header * Header::createHeaderStream(bool start, bool end, int l){

    unsigned char parameters=(unsigned char)(start?1:0);
    parameters+=(unsigned char)(end?2:0);
    return new Header(Header::votes, parameters, l);
}

Header * Header::createHeaderFile(bool priority, uint8_t info_length, int l){
    //It's probably not used by server
    if(info_length<0)
        return nullptr;
    unsigned char parameters=info_length;
    parameters+=(uint8_t)(priority?-128:0);

    return new Header(Header::file, parameters, l);
}

unsigned char *Header::createBuffer() {
    unsigned char *head = new unsigned char[7];
    head[0] = id_prot;
    head[1] = type;
    head[2] = parameters;
    head[3] = (unsigned char) (length >> 24);
    head[4] = (unsigned char) (length >> 16);
    head[5] = (unsigned char) (length >> 8);
    head[6] = (unsigned char) length;
    return head;
}

unsigned char *Header::createHeader() {
    return nullptr;
}

unsigned char *Header::createHeaderConnect() {
    return nullptr;
}

unsigned char *Header::createHeaderVote() {
    return nullptr;
}

unsigned char *Header::createHeaderFile() {
    return nullptr;
}

unsigned char *Header::createHeaderList() {
    return nullptr;
}

unsigned char *Header::createHeaderStream() {
    return nullptr;
}

Header::Header(const unsigned char type, unsigned char parameters, int length) {
    this->type = type;
    this->parameters = parameters;
    this->length = length;
}































