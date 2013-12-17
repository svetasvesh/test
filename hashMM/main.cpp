#include <iostream>
#include "hashMM.h"

class MyHash {
    public: int operator() (char* s) {
        int t = s[0]-96;
        return t;
    }
};
int main()
{

    HashMultiMap <char*, int, MyHash> Table;
    Table.initialization(26);

    Table.insert("banan", 39);
    Table.insert("yabloko", 45);
    Table.insert("brokkoly", 12);
    Table.insert("pomidor", 81);
    Table.insert("avokado", 95);
    Table.insert("baclaghan", 82);
    Table.insert("kabachok", 94);

    std::cout <<"Price: " <<std::endl;
    Table.show();
    std::cout <<std::endl;

    int errorcode = -1;
    int search = Table.search("brokkoly", errorcode);
    if (search == errorcode) std::cout <<"Record <brokkoly> no find" <<std::endl;
    else
        std::cout <<"Brokkoly price: " <<search <<std::endl;
    std::cout <<std::endl;

    errorcode = -1;
    search = Table.search("brokkoy", errorcode);
    if (search == errorcode) std::cout <<"Record <brokkoy> no find" <<std::endl;
    else
        std::cout <<"Brokkoly price: " <<search <<std::endl;
    std::cout <<std::endl;

    Table.deleted("banan");
    std::cout <<std::endl;

    Table.deleted("1abana");
    std::cout <<std::endl;

    std::cout <<"New price: " <<std::endl;
    Table.show();
    system ("pause");
    return 0;
}
