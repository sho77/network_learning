#include <iostream>
#include <cstring>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

void server(int& SocketFD)
{

 if (-1 == listen(SocketFD, 10)) {
      perror("listen failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
  
    for (;;) {
      int ConnectFD = accept(SocketFD, NULL, NULL);
  
      if (0 > ConnectFD) {
        perror("accept failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
      }

   }
   
   close (SocketFD);
}

void client ()
{

}

int main()
{
    struct sockaddr_in sa;
    int sc = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  
    if (-1 == sc){
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
  
    memset(&sa, 0, sizeof sa);
  
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1100);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
  
    if (-1 == bind(sc,(struct sockaddr *)&sa, sizeof( sa))) {
      perror("bind failed");
      close(sc);
      exit(EXIT_FAILURE);
    }

    pid_t pID = fork();
    if(pID == 0)
    {
        std::cout<<"Child process"<<"\n";
        server(sc);    
    }
    else if (pID < 0)
    {
        std::cerr << "Failed to fork" <<std::endl;
	exit(1);
    }
    else
    {
        std::cout<<"Parent process"<<"\n";
        server(sc);    
    }

    return 0;
}
