//
// Created by Kamil on 2016-05-04.
//
#ifndef SERVER_HEADER_H
#define SERVER_HEADER_H

#include <cstdint>

class Header {
public:
    static int const HEADER_LENGTH;

    Header() = delete;

    static unsigned char* createHeader();
    static unsigned char* createHeaderConnect();
    static unsigned char* createHeaderVote();
    static unsigned char* createHeaderFile();
    static unsigned char* createHeaderList();

    static unsigned char* createHeaderStream();
    static Header *createHeader(unsigned char *head);
    static Header *createHeaderConnect(bool start, bool end, int l);
    static Header *createHeaderVote(bool cancel_vote, int l);
    static Header *createHeaderFile(bool priority, unsigned char info_length, int l);
    static Header *createHeaderList(bool cancel_vote, int l);
    static Header *createHeaderStream(bool start, bool end, int l);

    int getLength() const {
        return length;
    }
    unsigned char getParameters() const {
        return parameters;
    }
    unsigned char getType() const {
        return type;
    }

private:

    Header(const unsigned char type, unsigned char parameters, int length);

    static const unsigned char connect;
    static const unsigned char stream;
    static const unsigned char votes;
    static const unsigned char file;
    static const unsigned char id_prot;

    unsigned char type; //Here is also the zero-tail
    unsigned char parameters;
    int length;

    unsigned char *createBuffer();
};


#endif //SERVER_HEADER_H
