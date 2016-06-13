//
// Created by Kamil on 2016-05-04.
//


#include "Header.h"

const int Header::SIZE = 7;

const  char Header::CONNECT = 0;
const  char Header::STREAM = 1;
const  char Header::VOTES = 2;
const  char Header::FILE = 3;
const  char Header::ID_PROT = 90;

Header::Header(const  char type,  char parameters, int length) {
    this->type = type;
    this->parameters = parameters;
    this->length = length;
}

Header *Header::createHeader(char *headerBuffer) {
    if(headerBuffer[0]!=Header::ID_PROT||headerBuffer[1]>3) {
        perror("Wrong protocol");
        return nullptr;
    }
    char type = headerBuffer[1]; //Here is also the zero-tail
    char parameters = headerBuffer[2];
    int length = headerBuffer[3]<<24;
    length += headerBuffer[4]<<16;
    length += headerBuffer[5]<<8;
    length += headerBuffer[6];
    return new Header(type, parameters, length);
}
Header * Header::createHeaderConnect(bool start, bool end, int l){

    char parameters=(char)(start?1:0);
    parameters+=(uint8_t)(end?2:0);

    return new Header(Header::CONNECT, parameters, l);
}

char * Header::createHeaderVote(bool cancel_vote, int l){

    char parameters=(char)(cancel_vote?1:0);
    parameters+=2;	//Since it's the client to server message
    return createBuffer(Header::VOTES, parameters, l);
}

Header * Header::createHeaderList(bool ack, int l){

     char parameters=( char)(ack?1:0);
    return new Header(Header::VOTES, parameters, l);
}


char * Header::createHeaderStream(bool start, bool end, int l){

    char parameters=(char)(start?1:0);
    parameters+=( char)(end?2:0);
    return createBuffer(Header::STREAM, parameters, l);;
}

Header * Header::createHeaderFile(bool priority, char info_length, int l){
    //It's probably not used by server
    if(info_length<0)
        return nullptr;
     char parameters=info_length;
    parameters+=(uint8_t)(priority?-128:0);

    return new Header(Header::FILE, parameters, l);
}

char *Header::createBuffer(char type, char parameters, int length) {
    char *head = new char[7];
    head[0] = ID_PROT;
    head[1] = type;
    head[2] = parameters;
    head[3] = ( char) (length >> 24);
    head[4] = ( char) (length >> 16);
    head[5] = ( char) (length >> 8);
    head[6] = ( char) length;
    return head;
}

 char *Header::createHeader() {
    return nullptr;
}

char * Header::createHeaderConnect() {
    return nullptr;
}

char * Header::createHeaderVote() {
    return nullptr;
}

 char *Header::createHeaderFile() {
    return nullptr;
}

 char *Header::createHeaderList() {
    return nullptr;
}

char * Header::createHeaderStream() {
    return nullptr;
}