//
// Created by Kamil on 2016-05-04.
//

#include "Header.h"


//uint8_t* Header::createHeaderConnect(bool start, bool end, int l){
//    type=connect;
//    parameters=(uint8_t)(start?1:0);
//    parameters+=(uint8_t)(end?2:0);
//    length=l;
//}
//uint8_t* Header::createHeaderVote(bool cancel_vote, int l){
//    type=votes;
//    parameters=(uint8_t)(cancel_vote?1:0);
//    parameters+=2;	//Since it's the client to server message
//    length=l;
//}

//Header Header::createHeaderList(bool ack, int l){
//    type=votes;
//    parameters=(uint8_t)(ack?1:0);
//    length=l;
//}

//Header Header::createHeaderStream(bool start, bool end, int l){
//    type=votes;
//    parameters=(uint8_t)(start?1:0);
//    parameters+=(uint8_t)(end?2:0);
//    length=l;
//}


//Header Header::createHeaderFile(bool priority, uint8_t info_length, int l){
// It's probably not used by server
//    type=file;
//    if(info_length<0)
//        return;
//    parameters=info_length;
//    parameters+=(uint8_t)(priority?-128:0);
//    length=l;
//}

//uint8_t *Header::createBuffer() {
//    uint8_t *head = new uint8_t[7];
//    head[0] = id_prot;
//    head[1] = type;
//    head[2] = parameters;
//    head[3] = (uint8_t) (length >> 24);
//    head[4] = (uint8_t) (length >> 16);
//    head[5] = (uint8_t) (length >> 8);
//    head[6] = (uint8_t) length;
//    return head;
//}



unsigned char *Header::createHeader(unsigned char t, unsigned char param, int l) {
    return 0;
}

unsigned char *Header::createHeaderConnect(bool start, bool end, int l) {
    return 0;
}

unsigned char *Header::createHeaderVote(bool cancel_vote, int l) {
    return 0;
}

unsigned char *Header::createHeaderFile(bool priority, unsigned char info_length, int l) {
    return 0;
}

unsigned char *Header::createHeaderList(bool cancel_vote, int l) {
    return 0;
}

unsigned char *Header::createHeaderStream(bool start, bool end, int l) {
    return 0;
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























