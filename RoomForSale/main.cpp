#include <iostream>
#include <fstream>
#include "array.h"

class RoomForSale {
    //int id;
    int rooms;
    int level;
    double square;
    char adress [100];
    unsigned int price;
    public: RoomForSale(int R = 0, int L = 0, double S = 0.0, const char* adr="", unsigned int P = 0) {
        rooms = R;
        level = L;
        square = S;
        strcpy(adress, adr);
        price = P;
    }
    RoomForSale(const RoomForSale &X) {
        rooms = X.rooms;
        level = X.level;
        square = X.square;
        strcpy (adress, X.adress);
        price = X.price;
    }
    ~RoomForSale() {};

    int getRooms() const {return rooms;}
    int getLevel() const {return level;}
    double getSquare() const {return square;}
    const char* getAdress() const {return adress;}
    unsigned int getPrice() const {return price;}

    bool operator == (const RoomForSale &X) const {return price == X.price;}
    bool operator < (const RoomForSale &X) const {return price < X.price;}
    RoomForSale operator = (const RoomForSale &X) {
        if (this != &X) {
            rooms = X.rooms;
            level = X.level;
            square = X.square;
            strcpy (adress, X.adress);
            price = X.price;
        }
        return *this;
    }

};
std::ostream& operator<< (std::ostream& out, const RoomForSale &X) {
    out <<X.getRooms() <<" rooms \t"  <<X.getLevel() <<" levels \t"<<X.getSquare() <<" square \t" <<std::endl
    <<"Adress: "<<X.getAdress() <<std::endl
    <<"Price: " <<X.getPrice()  <<" roubles"<<std::endl;
}
std::ofstream& operator << (std::ofstream& out, RoomForSale &X) {
    out <<X.getRooms() <<' ' <<X.getLevel() <<' ' <<X.getSquare() <<std::endl
    <<X.getAdress() <<std::endl <<X.getPrice() <<std::endl;
}
std::ifstream& operator >> (std::ifstream& in, RoomForSale &X) {
    char tmp [100];
    int troom, tlevel;
    double tsquare;
    unsigned int price;
    in >>troom >>tlevel >>tsquare;
    in.get();
    in.getline(tmp, 100);
    in >>price;
    X = RoomForSale(troom, tlevel, tsquare, tmp, price);
}
std::istream& operator >> (std::istream& in, RoomForSale &X) {
    char tmp [100] ;
    long troom, tlevel, price;
    double tsquare;
    std::cout <<"Add new record to base..." <<std::endl;
    do {
        char in [10];
        std::cout <<"Rooms -> "; std::cin >>in; std::cout <<std::endl;
        troom = atol(in);
        if (troom <=0 ) std::cout <<"Wrong type of data. Repeat input, please." <<std::endl;
    }while (troom <= 0);
     do {
        char in [10];
        std::cout <<"Level -> "; std::cin >>in; std::cout <<std::endl;
        tlevel = atol(in);
        if (tlevel <=0 ) std::cout <<"Wrong type of data. Repeat input, please." <<std::endl;
    }while (tlevel <= 0);
     do {
        char in [10];
        std::cout <<"Square -> "; std::cin >>in; std::cout <<std::endl;
        tsquare = atof(in);
        if (tsquare <=0 ) std::cout <<"Wrong type of data. Repeat input, please." <<std::endl;
    }while (tsquare <= 0);
    in.get();
    std::cout <<"Adress: "; in.getline(tmp, 100); std::cout <<std::endl;
    do {
        char in [10];
        std::cout <<"Price -> "; std::cin >>in; std::cout <<std::endl;
        price = atol(in);
        if (price <=0 ) std::cout <<"Wrong type of data. Repeat input, please." <<std::endl;
    }while (price <= 0);
    X = RoomForSale(troom, tlevel, tsquare, tmp, price);
}

typedef Array <RoomForSale> Data;
void Add(Data &Base) {
    RoomForSale new_record;
    std::cin >>new_record;
    Base.push_back(new_record);
}
typedef Array <RoomForSale> Data;
void Find(int r, int l, double s, Data &Base) {
    bool yes = false;
    for (int i = 0; i <Base.length(); ++i){
        RoomForSale *p;
        p = &(Base[i]);
        if (r==p -> getRooms() && l==p -> getLevel() &&   p -> getSquare() <=1.2*s    && p -> getSquare() >= 0.8*s) {
            std::cout <<Base[i];
            if (!yes) yes = true;
        }
    }
        if (!yes) std::cout <<"No this records" <<std::endl;
}
bool FileRead(Data &Base) {
    std::ifstream inFile("Base.txt");
    if (!inFile) std::cout <<"File cannot open!";

    while (inFile.peek() != EOF)
    {
        RoomForSale X;
        inFile >>X;
        Base.push_back(X);
    }
    inFile.close();
    return true;
}
typedef Array <RoomForSale> Data;
void ShowBase(Data &Base) {
    for (int i = 0; i < Base.length(); ++i)
        std::cout <<"--------------------------------------" <<std::endl <<"ID: " <<i+1 <<"." <<std::endl <<Base[i];
    std::cout <<"/////////////////////////////////////////////" <<std::endl;


}
void ShowBaseisRooms(Data &Base, int k) {
    int count = 0;
    for (int i = 0; i < Base.length(); ++i)
        if (Base[i].getRooms() == k) {
            std::cout <<"--------------------------------------" <<std::endl <<"ID: " <<i+1 <<"." <<std::endl <<Base[i];
            ++count;
    }
    if (count == 0) std::cout <<"No this records." <<std::endl;
    std::cout <<"/////////////////////////////////////////////" <<std::endl;

}
void WriteBaseinFile(Data &Base) {
    std::ofstream outFile ("CopyBase.txt");
    if (!outFile) std::cout <<"Cannot open write-file!";
    for (int i = 0; i < Base.length(); ++i ) outFile <<Base[i];
    outFile.close();
}
void EmptyBase() {
    std::cout <<"DataBase is empty. Operation is impossible." <<std::endl
    <<"Download DataBase from file or add records by hands." <<std::endl;
}



int main()
{
    typedef Array <RoomForSale> Data;
    Data Base;

    int go;
    std::cout <<"What do you want?" <<std::endl;
    std::cout <<"0. Read (download) DataBase from file" <<std::endl;  //прочитать из файла
    std::cout <<"1. Show DataBase" <<std::endl;         //Вывести на экран
    std::cout <<"2. Save DataBase to file" <<std::endl;      //сохранить базу в файл
    std::cout <<"3. Add new record" <<std::endl;  //добавить запись в базу
    std::cout <<"4. Find record" <<std::endl;   //найти запись в базе
    std::cout <<"5. Sort" <<std::endl;                   //сортировка
    std::cout <<"6. Sort by room count" <<std::endl;  //сортировать и вывести с выбором количества комнат
    std::cout <<"7. Delete record" <<std::endl;      //удалить запись по ID
    std::cout <<"-1. Exit" <<std::endl;            //закончить работу с базой
    bool isRead = false;
    do {
        std::cout <<"Actions ID -> "; std::cin >>go;
        switch (go) {
            case 0: {
                if (!isRead) isRead = FileRead(Base);
                std::cout <<"DataBase has been read from file." <<std::endl;
                break;
            }
            case 1: {
                if (Base.length() == 0) {
                    EmptyBase();
                } else ShowBase(Base);
                break;
            }
            case 2: {
                if (Base.length() == 0) {
                    EmptyBase();
                     break;
                }
                    WriteBaseinFile(Base);
                    std::cout<<"DataBase saved to CopyBase.txt" <<std::endl;
                break;
            }
            case 3:{
                Add(Base);
                std::cout <<"Record has been added to DataBase" <<std::endl;
                break;
            }
            case 4: {
                if (Base.length() == 0) {
                    EmptyBase();
                    break;
                }
                long frooms, flevel; double fsquare;

                std::cout <<"Input data: " <<std::endl;
                do {
                    char in [10];
                    std::cout <<"Rooms -> "; std::cin >>in; std::cout <<std::endl;
                    frooms = atol(in);
                    if (frooms <=0 ) std::cout <<"Wrong type of data. Repeat input, please." <<std::endl;
                }while (frooms <= 0);
                 do {
                    char in [10];
                    std::cout <<"Level -> "; std::cin >>in; std::cout <<std::endl;
                    flevel = atol(in);
                    if (flevel <=0 ) std::cout <<"Wrong type of data. Repeat input, please." <<std::endl;
                }while (flevel <= 0);
                 do {
                    char in [10];
                    std::cout <<"Square -> "; std::cin >>in; std::cout <<std::endl;
                    fsquare = atof(in);
                    if (fsquare <=0 ) std::cout <<"Wrong type of data. Repeat input, please." <<std::endl;
                }while (fsquare <= 0);
                Find(frooms, flevel, fsquare, Base);
            break;
            }

            case 5: {
                if (Base.length() == 0) {
                    EmptyBase();
                    break;
                }
                Base.sort();
                std::cout <<"DataBase has been sorted!" <<std::endl;
                ShowBase(Base);
                break;
            }
            case 6: {
                if (Base.length() == 0) {
                    EmptyBase();
                    break;
                }
                char in [5];
                long count;
                do {
                    std::cout <<"What rooms you can?" <<std::endl;
                    std::cout <<"-> "; std::cin >>in;
                    count = atol(in);
                    if (count <= 0) std::cout <<"Wrong type of data. Repeat input, please." <<std::endl;
                } while (count <= 0);
                Base.sort();
                ShowBaseisRooms(Base,count);
                break;
            }
            case 7: {
                if (Base.length() == 0) {
                    EmptyBase();
                    break;
                }
                char in [5];
                long k;
                do {
                    std::cout <<"Input number record ID -> ";
                    std::cin >>in;
                    std::cout <<std::endl;
                    k = atol(in);
                    if (k <=0 || k > Base.length()) std::cout <<"Wrong a scope. Repeat input, please." <<std::endl;
                } while (k <=0 || k > Base.length());
                Base.erase(k);
                std::cout <<"Record have been deleted!" <<std::endl;
                //ShowBase(Base);
                break;
            }
            case -1: break;
            default: std::cout<<"Wrong ID actions! Repeat input, please." <<std::endl; break;
        }
    }while (go != -1);

    system("pause");
    return 0;
}
