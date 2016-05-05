//
// Created by Kamil on 2016-05-04.
//
#ifndef SERVER_HEADER_H
#define SERVER_HEADER_H

#include <cstdint>

class Header {
public:
    Header(uint8_t head[7]);
    void createHeader(uint8_t t, uint8_t param, int l);
    void createHeaderConnect(bool start, bool end, int l);
    void createHeaderVote(bool cancel_vote, int l);
    void createHeaderFile(bool priority, uint8_t info_length, int l);
    void createHeaderList(bool cancel_vote, int l);
    void createHeaderStream(bool start, bool end, int l);

private:
    const uint8_t connect=0;
    const uint8_t stream=1;
    const uint8_t votes=2;
    const uint8_t file=3;
    const uint8_t id_prot=2;
    uint8_t type; //Here is also the zero-tail
    uint8_t parameters;
    int length;
};


#endif //SERVER_HEADER_H
