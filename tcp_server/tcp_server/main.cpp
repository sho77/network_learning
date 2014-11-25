//
//  main.cpp
//  tcp_server
//
//  Created by v.a.mykhailov on 11/4/14.
//  Copyright (c) 2014 test. All rights reserved.
//

#include <netinet/in.h> //sockaddr_in
#include <sys/socket.h> // scoket
#include <arpa/inet.h>// inet_ntop

#include <time.h>

#include <string> //memset

#include <unistd.h>

#include <iostream>

#include <stdio.h>
#include <signal.h>

int conn = 0;

void server_shut_down()
{
    if (conn)
        close(conn);
    
    std::cout<<"Server is turned off"<<"\n";
}

void server_shut_down_handler(int)
{
    server_shut_down();
}

int main(int argc, const char * argv[])
{
    atexit(&server_shut_down);
    signal(SIGKILL, &server_shut_down_handler);
    
    std::string time_str;
    
    struct sockaddr_in serv_adr;
    
    memset(&serv_adr, 0, sizeof(sockaddr_in));
    
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(5000);
    
    int server_sock = 0;
    size_t status = 0;
    
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
        std::cout<<"Socket creation error:"<<status<<"\n";
    
    status = bind(server_sock, (const struct sockaddr*)(&serv_adr), sizeof(sockaddr_in));
    if (status)
        std::cout<<"Bind socket error:"<<status<<"\n";
    
    status = listen(server_sock, SOMAXCONN);
    if (status)
        std::cout<<"Listen error:"<<status<<"\n";
    
    char addres_str[64];
    inet_ntop(serv_adr.sin_family, &serv_adr.sin_addr, addres_str, 64);
    std::cout<<"Server runs at "<< addres_str <<" : "<< serv_adr.sin_port<<"\n";
    
    for (;;)
    {
        conn = accept(server_sock, NULL, NULL);
        if (conn <= 0)
            std::cout<<"Accept connection error:"<<conn<<"\n";
        
        std::cout<<"New connection accepted "<<conn<<"\n";
        
        time_t rawtime;
        struct tm * timeinfo;
        
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        
        time_str = asctime (timeinfo);
        
        status = send(conn, time_str.c_str(), time_str.length(), 0);
        if (status <= 0)
            std::cout<<"Sending error:"<<status<<"\n";
        
        std::cout<<"Data send ["<<time_str<<"]\n";
        
        close(conn);
    }
    
    
    return 0;
}

