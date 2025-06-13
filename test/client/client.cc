#include <iostream>
#include <fstream>
#include "contact.pb.h"

using namespace std;

int main(){
    fstream input{"../contact.bin", ios::in | ios::binary};
    if(!input){
        cerr << "not exists, create\n";
    }
    c_contact::PeopleInfo p;
    if(!p.ParseFromIstream(&input)){
        cerr << "parse err\n";
    }
    
    std::cout << "name: " << p.name() << endl;
    std::cout << "age: " << p.age() << endl;

	
    const google::protobuf::Reflection* r { c_contact::PeopleInfo::GetReflection() };
    const google::protobuf::UnknownFieldSet& s =  r->GetUnknownFields(p);

    for(int i = 0; i < s.field_count(); i++){
    	const google::protobuf::UnknownField& uf = s.field(i);
	std::cout << i+1 << " number is " << uf.number() << std::endl;
	switch(uf.type()){
		case google::protobuf::UnknownField::Type::TYPE_VARINT:
			cout << "varient: " << uf.varint() << endl;
			break;
		case google::protobuf::UnknownField::Type::TYPE_LENGTH_DELIMITED:
			cout << "varient: " << uf.length_delimited() << endl;
			break;

	}
    }

}
