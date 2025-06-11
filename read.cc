#include <iostream>
#include <fstream>
#include "contact.pb.h"

using namespace std;

void PrintContact(const contact2::Contact& c) {
    for(int i = 0; i < c.contacts_size(); i++){
        const contact2::PeopleInfo& p { c.contacts(i) };
        std::cout << "联系人(" << i+1 << "): " << p.name() << endl;
        std::cout << "age : " << p.age() << endl;
        for (int j = 0; j < p.phone_numbers_size(); j++){
            const contact2::PeopleInfo_Phone& phone { p.phone_numbers(j) };
            std::cout << "电话(" << j+1 << "): " << phone.number();
            cout << phone.PhoneType_Name(phone.type()) << endl;
        }

        if(p.has_data() && p.data().Is<contact2::Address>()){
            contact2::Address addr;
            p.data().UnpackTo(&addr);
            std::cout << "home addr : " << addr.home_addr() << endl;
            std::cout << "unit addr : " << addr.unit_addr() << endl;
        }

        switch(p.other_contact_case()){
            case contact2::PeopleInfo::OtherContactCase::kQq:
                std::cout << "qq: " << p.qq() << endl;
                break;
            case contact2::PeopleInfo::OtherContactCase::kWc:
                std::cout << "wc " << p.wc() << endl;
                break;
        }
    }
}

int main(){

    fstream input {"contacts.bin", ios::in | ios::binary};
    contact2::Contact c;
    if(!c.ParseFromIstream(&input)){
        std::cout << "p error\n";
        return 0;
    }

    PrintContact(c);
    return 0;
}