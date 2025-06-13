#include <iostream>
#include <fstream>
#include "contact.pb.h"

using namespace std;

int main(){
    fstream input{"../contact.bin", ios::in | ios::binary};
    if(!input){
        cerr << "not exists, create\n";
    }
    s_contact::PeopleInfo p;
    if(!p.ParseFromIstream(&input)){
        cerr << "parse err\n";
    }
    
    std::cout << "name: ";
    std::string name;
    std::cin >> name;
    std::cout << "birthday: ";
    int age;
    cin >> age;
    p.set_name(name);
    p.set_birthday(age);

    fstream output{"../contact.bin", ios::out | ios::trunc | ios::binary};
    if(!p.SerializeToOstream(&output)){
        cerr << "serialize fail\n";
    }

    return 0;
}
