#ifndef __HASHMM_D_
#define __HASHMM_D_
#include "array.h"
#include "list.h"
#include <iostream>
#include <fstream>

template <class KeyType, class ValueType, class Hasher>
class HashMultiMap {

    class KeyVal {
        public:
          KeyType key;
          ValueType value;
          KeyVal (const KeyType& k, const ValueType& v) {
            key = k;
            value = v;
          }
          bool operator == (const KeyVal& X) const {return key == X.key;}
          bool operator != (const KeyVal& X) const {return key != X.key;}

    };



    typedef List <KeyVal> HashList;
    Array <HashList> HMM;

    public: void insert (KeyType k, ValueType v) {
        Hasher hash;
        int i = hash(k);
        KeyVal X(k,v);
        X.key = k; X.value = v;
        HMM[i].push_back(X);
    }
    void initialization(const int t) {
        HashList x;
        for (int i = 0; i < t; ++i) HMM.push_back(x);
    }
    ValueType search(KeyType k, ValueType t) {
        Hasher hash;
        int i = hash(k);
        KeyVal X(k,0);
        int j = 0;
        while (j < HMM[i].size() && HMM[i][j] != X) ++j;
        if (j == HMM[i].size()) return t; else
        return (HMM[i][j].value);
    }
    void show () {
        for (int i = 0; i < HMM.size(); ++i){
            for (int j = 0; j < HMM[i].size(); ++j)
                std::cout <<HMM[i][j].key <<' ' <<HMM[i][j].value <<std::endl;
            if (HMM[i].size() > 0)std::cout <<"*****************************************"<<std::endl;
        }
    }
    void deleted(KeyType k) {
        Hasher hash;
        int i = hash(k);
        if (i >= 0 && i < HMM.size()) {

            KeyVal X(k,0);
            HMM[i].erase(X);

        }

    }

};




#endif // __HASHMM_D_
