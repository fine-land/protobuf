#include "httplib.h"
#include "contact.pb.h"
#include <iostream>

using namespace std;
using namespace httplib;


int main(){
    Client c("127.0.0.1", 8123);

    while(true){
        cout << "select: 0) quit, 1) add" << endl;
        int select;
        cin >> select;
        if(select == 0){
            break;
        } else if (select == 1){
            string name;
            int age;
            cout << "name: ";
            cin >> name;
            cout << "age: ";
            cin >> age;

            contact::Request r;
            r.set_name(name);
            r.set_age(age);
            string s;
            if(!r.SerializeToString(&s)){
                cerr << "seri err\n";
                return 0;
            }
            Result r1 = c.Post("/contact-add", s, "application/protobuf");
            if(r1->status != 200){
                cout << "add fail";
            }

            contact::Response res;
            if(!res.ParseFromString(r1->body)){
                cerr << "res body, parse fail\n";
                return 0;
            }
            cout << "uid: " << res.uid() << endl;
        }
    }

    return 0;
}
