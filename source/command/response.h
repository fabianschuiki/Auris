#pragma once
#include <pthread.h>
#include <string>
#include "../blob.h"

class Response;


class ResponseHandler {
public:
    //virtual void onResponseFinished(Response * r) = 0;
    virtual void onResponseData(Response * r, const char * data, unsigned long length) = 0;
};


class Response {
	friend class ResponseHandler;
	
private:
    bool finished;
    unsigned long expectedLength;
    bool successful;
    pthread_mutex_t mutex;
    
public:
    ResponseHandler * const handler;
    
    Response(ResponseHandler * handler);
    ~Response();
    
    void finish();
    void setExpectedLength(unsigned long l);
    void setSuccessful(bool s);
    
	bool isFinished();
	unsigned long getExpectedLength();
	bool isSuccessful();

    void write(const char * data, unsigned long length);
    void write(Blob * data);
    
    Response & operator << (Blob * data);
    Response & operator << (const std::string & s);
};