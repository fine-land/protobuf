write:write.cc contact.pb.cc
	g++ write.cc contact.pb.cc -o write -lprotobuf

read:read.cc contact.pb.cc
	g++ read.cc contact.pb.cc -o read -lprotobuf