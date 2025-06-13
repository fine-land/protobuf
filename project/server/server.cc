#include "httplib.h"
#include "contact.pb.h"
#include <iostream>

using namespace std;
using namespace httplib;

int main(){
    cout << "................start server.............." << endl;
    Server s;

    s.Post("/contact-add", [](const Request& req, Response& res) {
        cout << "receive post" << endl;
        res.status = 200;
	contact::Request r;
	if(!r.ParseFromString(req.body)){
		cerr << "parse from string request fail\n";
		return ;
	}
	cout << "name: " << r.name() << " age: " << r.age() << endl;
	contact::Response re;
	re.set_uid(1);
	if(!re.SerializeToString(&res.body)){
		cout << "seril to string, res body fail\n";
		return ;
	}
    });

    s.Get("/test-get", [](const Request& req, Response& res) { 
        cout << "receive get" << endl;
        res.status = 200;
    });

    s.listen("0.0.0.0", 8123);
    return 0;
}
