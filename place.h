#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>

// Place Interface:

class placeInterface : public sc_interface 
{
    public: 

    virtual void addTokens(unsigned int n) = 0;
    virtual void removeTokens(unsigned int n) = 0;
    virtual unsigned int testTokens() = 0;
};

// Place Channel:

class place : public placeInterface
{
    private : 

    // current number of tokens in the place1
    int tokens;

    public :

    place(int tokens)
    {
        this->tokens = tokens;
    }

    void addTokens(unsigned int n)
    {
        this->tokens += n;
    }

    void removeTokens(unsigned int n)
    {   
        this->tokens -= n;
    }

    unsigned int testTokens()
    {
        return this->tokens;
    }
};

#endif // PLACE_H
