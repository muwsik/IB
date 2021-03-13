//
// Created by Denis Rodionov on 5/17/18.
//

#ifndef RSACPP_RSAALGO_H
#define RSACPP_RSAALGO_H


#include "RSAAlgoUser.h"

class RSAAlgo {
private:
    int q = 46817;
    int p = 45659;
public:
    RSAAlgoUser creaUserWithName(string name){
        return RSAAlgoUser(name,p,q);
    }

};


#endif //RSACPP_RSAALGO_H
