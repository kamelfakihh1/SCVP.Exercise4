#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>
#include <iostream>

#include "place.h"

// Transition:
template<unsigned int N = 1, unsigned int M = 1, unsigned int L = 0>
SC_MODULE(transition)
{
    public:

    sc_port<placeInterface, L, SC_ZERO_OR_MORE_BOUND> inhibitors;
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

        // check if there are any tokens in inhibitors 
        for(int i = 0; i<inhibitors.size(); i++)
        {
            if(inhibitors[i]->testTokens() == true)
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
