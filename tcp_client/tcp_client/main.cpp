//
//  main.cpp
//  tcp_client
//
//  Created by v.a.mykhailov on 11/5/14.
//  Copyright (c) 2014 test. All rights reserved.
//

#include <netinet/in.h> //sockaddr_in
#include <sys/socket.h> // scoket
#include <arpa/inet.h>// inet_ntop

#include <time.h>
 
#include <string> //memset

#include <unistd.h>

#include <iostream>

int main(int argc, const char * argv[])
{
    std::string time_str;
    
    struct sockaddr_in serv_adr;
    
    memset(&serv_adr, 0, sizeof(sockaddr_in));
    
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(5000);
    
    int client_sock = 0;
    size_t status = 0;
    
    for(;;)
    {
        client_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (client_sock < 0)
            std::cout<<"Socket creation error:"<<status<<"\n";
    
        status = connect(client_sock, (const struct sockaddr*)(&serv_adr), sizeof(struct sockaddr_in));
    
        if (status)
        {
            std::cout<<"Can not connect"<<"\n";
        }
        char buf[256];
    
        size_t l = read(client_sock, buf, sizeof(buf));
    
        buf[l] = '\0';
    
        std::cout<<buf<<"\n";
    
        close(client_sock);
        
        std::cout<<"Press any key to ping again \n";
        
        std::cin.get();
    }
    return 0;
}

