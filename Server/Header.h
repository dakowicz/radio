//
// Created by Kamil on 2016-05-04.
//
#ifndef SERVER_HEADER_H
#define SERVER_HEADER_H

#include <cstdint>

class Header {
public:
    Header() = delete;

    static unsigned char *createHeader();
    static unsigned char *createHeaderConnect();
    static unsigned char *createHeaderVote();
    static unsigned char *createHeaderFile();
    static unsigned char *createHeaderList();
    static unsigned char *createHeaderStream();

    static unsigned char *createHeader(unsigned char t, unsigned char param, int l);
    static unsigned char *createHeaderConnect(bool start, bool end, int l);
    static unsigned char *createHeaderVote(bool cancel_vote, int l);
    static unsigned char *createHeaderFile(bool priority, unsigned char info_length, int l);
    static unsigned char *createHeaderList(bool cancel_vote, int l);
    static unsigned char *createHeaderStream(bool start, bool end, int l);

private:
    const unsigned char connect=0;
    const unsigned char stream=1;
    const unsigned char votes=2;
    const unsigned char file=3;
    const unsigned char id_prot=90;
    unsigned char type; //Here is also the zero-tail
    unsigned char parameters;
    int length;
};


#endif //SERVER_HEADER_H
