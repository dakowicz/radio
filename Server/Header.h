//
// Created by Kamil on 2016-05-04.
//
#ifndef SERVER_HEADER_H
#define SERVER_HEADER_H

#include <cstdint>
#include <cstdio>

class Header {
public:
    static const int SIZE;

    Header() = delete;

    static char *createHeader();
    static char * createHeaderConnect();
    static char * createHeaderVote();
    static char *createHeaderFile();
    static char *createHeaderList();
    static char * createHeaderStream();

    static Header *createHeader(char *headerBuffer);
    static Header *createHeaderConnect(bool start, bool end, int l);
    static char * createHeaderVote(bool cancel_vote, int l);
    static Header *createHeaderFile(bool priority,  char info_length, int l);
    static char * createHeaderList(bool cancel_vote, int l);
    static char * createHeaderStream(bool start, bool end, int l);

    int getLength() const {
        return length;
    }
    char getParameters() const {
        return parameters;
    }
    char getType() const {
        return type;
    }

private:

    Header(const  char type,  char parameters, int length);

    static const char CONNECT;
    static const char STREAM;
    static const char VOTES;
    static const char FILE;
    static const char ID_PROT;

    char type; //Here is also the zero-tail
    char parameters;
    int length;

    static char *createBuffer(char type, char parameters, int length);
};


#endif //SERVER_HEADER_H
