#include <iostream>
#include <fstream>
#include "contact.pb.h"

void AddContacts(contact2::PeopleInfo* p){
    for(int i = 0;; i++){
        std::string name;
        int age;
        std::cout << "input name("<<  i+1 << "): ";
        std::cin >> name;
        p->set_name(name);
        std::cout << "input age: ";
        std::cin >> age;
        p->set_age(age);
        contact2::Address addr;
            std::cout << "输入家庭地址: " ;
            std::string home;
            std::cin >> home;
            addr.set_home_addr(home);
            std::cout << "输入单位地址: ";
            std::string unit;
            std::cin >> unit;
            addr.set_unit_addr(unit);

            p->mutable_data()->PackFrom(addr);

            std::cout << "other contact: ";
            int other_contact{};
           // contact2::OtherContactCase o;
            std::cin >> other_contact;
           if(0 == other_contact){
                std::string qq;
                std::cout << "qq: ";
                std::cin >> qq;
                p->set_qq(qq);
           } else if (1 == other_contact) {
            std::string wc;
            std::cout << "wc: ";
            std::cin >> wc;
            p->set_wc(wc);
           }
            std::cin.ignore(100, '\n');

        for(int j = 0; ; j++){
            std::cout << "input phone (" << j+1 << "): ";
            contact2::PeopleInfo_Phone* phone = p->add_phone_numbers();
            std::string ph;
            std::getline(std::cin, ph);
            if(ph.empty()){
                break;
            }
            phone->set_number(ph);
            std::cout << "set type: ";
            int type;
            std::cin >> type;
            switch(type){
                case 0:
            phone->set_type(contact2::PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_MP);
                case 1:
            phone->set_type(contact2::PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_TLP);
                default:
            phone->set_type(contact2::PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_MP);
            }
                      //  std::cin.ignore(100, '\n');
        }
        std::cin.ignore(100, '\n');
        for(int i = 0; ; i++){
        std::cout << "remark key: ";
        std::string key;
        std::getline(std::cin, key);
        if(key.empty()){
            break;
        }
        std::cout << "remark value: ";
        std::string value;
        std::getline(std::cin, value);
        p->mutable_remark()->insert({key, value});
        }
        std::cout << "Finish? :";
        std::string s;
        std::cin >> s;    
        if (s == "OK"){
            return;
        }
    }
}

int main(){
    std::fstream input{"contacts.bin", std::ios::in | std::ios::binary};
    auto iclose {[&input](){input.close();} };
    if(!input){
        std::cout << "not exist , create\n";
    }

    contact2::Contact c;
    if(!c.ParseFromIstream(&input)){
        std::cout << "error parse input\n";
        iclose();
    }

    std::fstream output{"contacts.bin", std::ios::out | std::ios::trunc | std::ios::binary};
    contact2::PeopleInfo* ps { c.add_contacts() };
    AddContacts(ps);
    if(!c.SerializeToOstream(&output)){
        std::cout << "s error\n";
        iclose();
        return 0;
    }
    return 0;
}