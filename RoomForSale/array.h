#include <iostream>
//#include "array.h"
#ifndef __ARRAY_132_
#define __ARRAY_132_

template <typename TIP>
class Array {
    TIP *data;
    unsigned int Len, maxLen;
    bool isSorted;
    void QuickSort(TIP*, unsigned int n);

    public: Array (unsigned int N = 0): Len(0), maxLen(N), data(NULL), isSorted(true){
       // Len = 0; maxLen = N; data = NULL;
        if (maxLen > 0) {
            data = new TIP [maxLen];
            if (!data) throw "Out of memory";
        }

    }

    Array(const Array& A) {
        isSorted = A.isSorted;
        Len = A.Len;
        maxLen = A.maxLen;
        data = NULL;
        if (maxLen > 0) {
            data = new TIP[maxLen];
            if (!data) throw "Out of memory";
        }
        for (unsigned int i = 0; i< Len; ++i) data[i] = A.data[i];
    }

    ~Array() {clear();}
    Array& operator=(const Array&);

    unsigned int length() const {return Len;}
    void clear() {
        if (data) delete[] data;
        data = NULL; Len = 0; maxLen = 0;
    }
    void erase(int point) {
        for (int i = point-1; i < Len-1; ++i) data[i] = data[i+1];
        --Len;
    }
    void empty() {Len = 0;}
    void push_back(const TIP&);
    unsigned int size() const{return Len;}
    TIP& operator[] (unsigned int i) const {
        if (i>=Len) throw "Out of array's bounds";
        return data[i];
    }
    void sort() {QuickSort(data, Len); isSorted = true;}

    class iterator {
        TIP *current;
        public: iterator(TIP *p = NULL): current(p){}
        TIP& operator*()const {return *current;}
        bool operator == (const iterator& p) const {return current == p.current;}
        bool operator != (const iterator& p) const {return current != p.current;}
        iterator& operator++ () {++current; return *this;}
        iterator operator++ (int) {TIP *tmp = current; ++current; return iterator(tmp);}
    };
    iterator begin () const {return iterator(data);}
    iterator end() const {return iterator (data + Len);}

    class reverse_iterator {
        TIP *current;
        public: reverse_iterator(TIP *p = NULL): current(p){}
        TIP& operator*()const {return *current;}
        bool operator == (const reverse_iterator& p) const {return current == p.current;}
        bool operator != (const reverse_iterator& p) const {return current != p.current;}
        reverse_iterator& operator++ () {--current; return *this;}
        reverse_iterator operator++ (int) {TIP *tmp = current; --current; return reverse_iterator(tmp);}
    };
    reverse_iterator rbegin () const {return reverse_iterator(data + Len -1);}
    reverse_iterator rend() const {return reverse_iterator (data - 1);}

    iterator Find (const TIP&) const;

};
//-----------------------------------------------
template <typename TIP>
void Array<TIP>::push_back(const TIP& X){
    if (Len+1 > maxLen){
        //не хватает памяти, нужно выделить новую и скопировать туда старую информацию
        unsigned int newLen;
        //newLen = maxLen+1;
        newLen = (maxLen < 10)? maxLen+1 : maxLen*1.1;
        TIP *tmp = new TIP[newLen];
        if (!tmp) throw "Out of memory";
        for (unsigned int i = 0; i < Len; ++i) tmp[i] = data[i];
        delete[] data;
        data = tmp;
        maxLen = newLen;
    }
    data[Len++] = X;
    isSorted = false;
}
//-----------------------------------------------
template <typename TIP>
void Array<TIP>::QuickSort(TIP *A, unsigned int n) {
    if (n==0) return;
    unsigned int i = 0, j = n-1;
    TIP tmp, p = A[i+(j-i)/2];
    while (i<j) {
        while (A[i]<p) ++i;
        while (p<A[j]) --j;
        if (i<j) {tmp = A[i]; A[i] = A[j]; A[j] = tmp;
        ++i; --j;
        } else if (i==j) {
            ++i; if (j) --j; else break;
        }
    }
    if (i > (n-1)/2) {
        if (i < n-1) QuickSort(A+i, n-i);
        if (j>0) QuickSort(A, j+1);
    }else {
        if (j>0) QuickSort(A, j+1);
        if (i < n-1) QuickSort(A+i, n-i);
    }

}
//-----------------------------------------------
template <typename TIP>
Array<TIP>& Array<TIP>::operator=(const Array<TIP> &A) {
    if (this != &A){
        isSorted = A.isSorted;
        Len = maxLen = A.Len;
        delete[] data;
        data = NULL;
        if (maxLen > 0) {
            data = new TIP[maxLen];
            if (!data) throw "Out of memory";
        }
        for (unsigned int i = 0; i< Len; ++i) data[i] = A.data[i];
    }
    return *this;
}
//-----------------------------------------------
template <typename TIP>
typename Array<TIP>::iterator Array<TIP>::Find(const TIP& X) const {
    if (isSorted) {
        unsigned int left = 0, right = Len - 1, p;
        while (left < right) {
            p = left + (right - left)/2;
            if (data[p] < X) left = p+1;
            else
            if (data[p] == X)  return iterator(data+p);
                else if (p ==0) break; else right = p - 1;
        }
        if (data[left] == X) return iterator (data+left);
        return end();
    }else {
        unsigned int i = 0;
        for (i = 0; i<Len; ++i)
            if (data[i] == X) return iterator (data+i);
        return end();
    }
}
//-----------------------------------------------
#endif
