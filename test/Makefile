all: ./client/client ./server/server

./client/client: ./client/client.cc ./client/contact.pb.cc
	g++ $^ -o $@ -lprotobuf

./server/server: ./server/server.cc ./server/contact.pb.cc
	g++ $^ -o $@ -lprotobuf

clean:
	rm -f ./client/client ./server/server
