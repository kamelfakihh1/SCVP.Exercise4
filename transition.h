#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>
#include <iostream>

#include "place.h"

// Transition:
template<unsigned int N = 1, unsigned int M = 1>
SC_MODULE(transition)
{
    public:

    sc_port<placeInterface, N, SC_ALL_BOUND> in;    
    sc_port<placeInterface, M, SC_ALL_BOUND> out;    

    SC_CTOR(transition)        
    {

    }

    // void fire()
    // {
    //     unsigned int tokens = in->testTokens();
    //     if(tokens != 0){
    //         std::cout << this->name() << ": Fired" << std::endl;
    //         in->removeTokens(1);
    //         out->addTokens(1);
    //     }else{
    //         std::cout << this->name() << ": NOT Fired" << std::endl;
    //     }
    // }

    void fire()
    {
        // check if inputs have enough tokens
        for(int i = 0; i<in.size(); i++)
        {
            if(in[i]->testTokens() == false)
            {
                std::cout << this->name() << ": NOT Fired" << std::endl;
                return;
            }
        }

        // consume tokens
        for(int i = 0; i<in.size(); i++)
        {
            in[i]->removeTokens();
        }

        // prodice tokens
        for(int i = 0; i<out.size(); i++)
        {
            out[i]->addTokens();
        }

        std::cout << this->name() << ": Fired" << std::endl;
    }
};

#endif // TRANSITION_H
