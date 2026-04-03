#include<iostream>
#include<string>
#include<cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

using namespace std;

int main(){
    //1. Create a socket (IPv4, TCP)
    int server_fd=socket(AF_INET, SOCK_STREAM,0);
    if(server_fd<0){
        cerr<<"Failed to create socket"<<endl;
        return 1;
    }
    
    // Configure socket options to allow address reuse
    int opt=1;
    if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&opt, sizeof(opt))<0){
        cerr<<"Failed to set socket options"<< endl;
        return 1;
    }

    //2. Bind the socket to an ip and port
    sockaddr_in address;
    int addrlen=sizeof(address);
    address.sin_family=AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    if(bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0){
        cerr<<"Failed to bind to port 8080"<<endl;
        return 1;
    }
    
    // 3.Listen for incoming connections
    // The second parameter is the backlog (max pending connections)
    if(listen(server_fd,10)<0){
        cerr<< "Listen failed"<<endl;
        return 1;
    }
    
    cout<<"Server is listening on port 8080..."<<endl;
    
    while(true){
        // 4.Accept an incoming connections
        int client_socket = accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen);
        if(client_socket<0){
            cerr <<"Failed to accept connection" <<endl;
            continue;
        }
        
        // 5. Read the HTTP Request
        char buffer[2048]={0};
        int bytes_read=read(client_socket,buffer,sizeof(buffer)-1);
        if(bytes_read>0){
            cout<<"\n--- Incoming Request ---\n" << buffer<<endl;
        }

        //6. construct and send the HTTP Response
        // An HTTP response requires a status line, headers, a blank line, and the body.
        string body = "<html><body><h1>Hello from C++ HTTP Server!</h1></body></html";
        string response=
        "HTTP/1.1 200 OK\r\n" 
        "Content-Type: text/html\r\n"
        "Content-Length: " + to_string(body.length())+"\r\n"
        "Connection: close\r\n\r\n" +
        body;

        send(client_socket,response.c_str(),response.length(),0);

        //7. Closet the client socket
        close(client_socket);
    }
    // Close the listening socket (unreachable in this infinite loop, but good practice)
    close(server_fd);
    return 0;
}