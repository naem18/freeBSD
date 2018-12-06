#define _POSIX_C_SOURCE 200112L

#include <sys/socket.h>

#include <netinet/in.h>

#include <unistd.h>

#include <stdlib.h>

#include <string.h>

#include <stdio.h>



int main(int argc, char **argv) {

   struct sockaddr_in saddr;

   socklen_t addr_len = sizeof(saddr);

   int port = 12121, n, ld, connfd, servfd;

   char buffer[25];

   pid_t pid;



   if((ld = socket(AF_INET,SOCK_STREAM,0)) == -1){

      printf("socket error\n");

      return 0;

   }



   saddr.sin_family = AF_INET;

   saddr.sin_port    = 12121;



   if(bind(ld,(struct sockaddr *)&saddr,addr_len) == -1){

      printf("bind error\n");

      return 0;

   }



   if(listen(ld,5) == -1){

      printf("listen error\n");

      return 0;

   }



   pid = fork();

   if(pid==0){

      if((connfd = socket(AF_INET,SOCK_STREAM,0)) == -1){

         printf("socket error\n");

         exit(0);

      }


      if(connect(connfd,(struct sockaddr *)&saddr,addr_len) == -1){

         printf("connect error\n");

         exit(0);

      }



      printf("C: Sending regular data\n");

      send(connfd,"123",3,0);

      printf("C: Sending OOB data\n");

      send(connfd,"ab",2,MSG_OOB);


      close(connfd);

      exit(0);

   }


   else {

      servfd = accept(ld,(struct sockaddr *)&saddr,&addr_len);

      if(servfd == -1) {

         printf("accept error\n");

         exit(0);

      }


      sleep(5);

      memset(buffer,0,sizeof(buffer));

      recv(servfd,&buffer,sizeof(buffer),0);

      printf("S: Received \"%s\"\n",buffer);


      memset(buffer,0,sizeof(buffer));


      n = sockatmark(servfd);

      if(n == 1) printf("S: At the mark\n");

      recv(servfd,&buffer,sizeof(buffer),MSG_OOB);

      printf("S: Received \"%s\"\n",buffer);


      close(servfd);

      close(ld);

   }

}
