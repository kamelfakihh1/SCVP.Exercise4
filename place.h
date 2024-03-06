#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>

// Place Interface:

class placeInterface : public sc_interface 
{
    public: 

    virtual void addTokens() = 0;
    virtual void removeTokens() = 0;
    virtual bool testTokens() = 0;
};

// Place Channel:

template<unsigned int Win = 1, unsigned int Wout = 1>
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

    void addTokens()
    {
        this->tokens += Win;
    }

    void removeTokens()
    {   
        this->tokens -= Wout;
    }

    bool testTokens()
    {
        return this->tokens >= Wout;
    }
};

#endif // PLACE_H
