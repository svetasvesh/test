#ifndef __STROKA_132_
#define __STROKA_132_
#include <string.h>

class stroka {
    char *data;
    int Len;
    public: stroka (const char *str = "");
    stroka (int N);
    stroka (const stroka&);
    ~stroka();
    int size() const {return Len;}
    int length() const {return strlen(data);}
    const char* str() const {return data;}
    char operator [] (int i) {if (i < 0 || i > Len) throw "Out of string limits."; else return data[i];}
    stroka operator + (const stroka&) const;
    bool operator == (const stroka& X) const { return strcmp(data, X.data) == 0; }
    bool operator != (const stroka& X) const { return !(*this == X); }
    bool operator < (const stroka& X) const { return strcmp(data, X.data) < 0; }
    stroka& operator = (const stroka&);
};
//-----------------------------------------------
stroka::stroka (const char *str) {
    Len = strlen(str);
    data = new char[Len +1];
    strcpy (data, str);
}
//-----------------------------------------------
stroka::stroka (int N) {
    Len = N;
    data = new char [Len + 1];
    data[0] = '\0';
}
//-----------------------------------------------
stroka::stroka (const stroka& X) {
    Len = X.Len;
    data = new char [Len + 1];
    strcpy (data, X.data);
}
//-----------------------------------------------
stroka::~stroka() {
    if (data) delete[]data;
    data = NULL; Len = NULL;
}
//-----------------------------------------------
stroka stroka::operator+ (const stroka& X) const {
    stroka C(Len + X.Len);
    strcpy (C.data, data);
    strcpy (C.data+Len, X.data);
    return C;
}
//-----------------------------------------------
stroka& stroka::operator = (const stroka& X) {
    if (this != &X) {
        if (data) delete[] data;
        Len = X.Len;
        data = new char[Len + 1];
        strcpy (data, X.data);
    }
    return *this;
}
//-----------------------------------------------
#include <iostream>
std::ostream& operator <<(std::ostream& out, const stroka& X) {
    out <<X.str();
    return out;
}
//-----------------------------------------------

#endif
