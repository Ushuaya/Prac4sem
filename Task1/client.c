#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <signal.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



#define _GNU_SOURCE

#define Family AF_INET
//#define Port htons(4000)
#define Addr htonl(INADDR_LOOPBACK)
#define SIZE 128
#define MAX_SIZE 64
int sock;
char nick[16];
int Port;

void sigHndlr(int s)
{
    //char last[] = "Left the chat";
    //send(sock, last, 13, 0);
    shutdown(sock, 2);
    close(sock);
    //printf("You have left tne chat\n");
    exit(0);
}


int main(int argc, char **argv)
{
    int len, len2;
    char buf[SIZE];
    //char *msg;
    struct addrinfo hints;
   struct addrinfo *result, *rp;
   int sfd, s, j;
   //size_t len;
   //ssize_t nread;
   //char buf[BUF_SIZE];

    
    
    if (argc < 3)
    {
       printf("There is no enough arguments \n");
       return 0;
    }
    int tmp = atoi(argv[2]);
    Port = htons(tmp);
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = Family;
    server_addr.sin_port = Port;
    server_addr.sin_addr.s_addr = Addr;
    /*
    // Error checking omitted for expository purposes
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Bind to a specific network interface (and optionally a specific local port)
    struct sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = inet_addr("192.168.1.100");
    localaddr.sin_port = 0;  // Any local port will do
    bind(sockfd, (struct sockaddr *)&localaddr, sizeof(localaddr));

    // Connect to the remote server
    struct sockaddr_in remoteaddr;
    remoteaddr.sin_family = AF_INET;
    remoteaddr.sin_addr.s_addr = inet_addr(server_ip);
    remoteaddr.sin_port = htons(server_port);
    connect(sockfd, (struct sockaddr *)&remoteaddr, sizeof(remoteaddr));
     */


    signal(SIGINT, sigHndlr);
    signal(SIGTSTP, sigHndlr);
    
   // int getaddrinfo(const char *node, const char *service,
                     //      const struct addrinfo *hints,
                        //   struct addrinfo **res);

    
                memset(&hints, 0, sizeof(struct addrinfo));
               hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
               hints.ai_socktype = SOCK_STREAM; /* Stream socket */
               hints.ai_flags = 0;
               hints.ai_protocol = 0;          /* Any protocol */

               s = getaddrinfo(argv[1], argv[2], &hints, &result);
               if (s != 0) {
                   fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
                   exit(EXIT_FAILURE);
               }

               /* getaddrinfo() returns a list of address structures.
                  Try each address until we successfully connect(2).
                  If socket(2) (or connect(2)) fails, we (close the socket
                  and) try the next address. */

               for (rp = result; rp != NULL; rp = rp->ai_next) {
                   sock = socket(rp->ai_family, rp->ai_socktype,
                                0);
                   if (sock == -1)
                       continue;

                   if (connect(sock, rp->ai_addr, rp->ai_addrlen) != -1)
                       break;                  /* Success */

                   //close(sfd);
               }

               if (rp == NULL) {               /* No address succeeded */
                   fprintf(stderr, "Could not connect\n");
                   exit(EXIT_FAILURE);
               }

               //freeaddrinfo(result);           /* No longer needed */
    
    
    
    
    
   /*

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket ");
        sigHndlr(0);
    }
    if(connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
    {
        perror("connect ");
        sigHndlr(0);
    }
   */
   
    /*
    if(fork() == 0)
    {
        while(1)
        {
            memset(buf,0,SIZE);
            //fgets(buf, SIZE, stdin);
            if((len2 = read(1, buf, SIZE-1)) > 0)
            {
                
                buf[len2] = '\0';
                //printf("DEB_MES: %s\n", buf);
                if(strcmp(buf,"\n"))
                {
                    //buf[strlen(buf)-1] = '\0';
                    send(sock, buf, SIZE, 0);
                }
                
            }
            else{
                sigHndlr(0);
            }

        }
    }
    else
        while(1)
            if((len = recv(sock, buf, SIZE, 0)) > 0)
            {
                buf[len] = '\0';
                if(strcmp(buf,"\n"))
                {
                    printf("%s", buf);
                }
            }
            else
            {
                printf("You have left the chat\n");
                sigHndlr(0);
            }

          */
    if(fork() == 0)
        {
            
            //char *text;
            int SPAMER_KICK = 0;
            while(1)
            {
                memset(buf,0,SIZE);
                //fgets(buf, SIZE, stdin);
                if((len2 = read(0, buf, SIZE-1)) > 0)
                {
                    
                    
                    if (MAX_SIZE >= len2)
                    {
                        SPAMER_KICK = 0;
                        printf("Processing\n");
                        buf[len2] = '\0';
                        //printf("DEB_MES: %s\n", buf);
                        
                        if(strcmp(buf,"\n"))
                        {
                            buf[strlen(buf)-1] = '\0';
                            write(sock, buf, SIZE);
                           // sleep(1); //without this sleep large message won't reach
                           // sleep(1); //without this sleep large message won't reach
                        }
                    }
                    else
                    {
                        SPAMER_KICK++;
                        if(SPAMER_KICK>10)
                        {
                            printf("SPAMER DETECTED\n");
                            sigHndlr(0);
                        }
                        printf("TOO BIG MESSAGE\n");
                        rewind(stdin);
                        if (fseek (stdin, 0, SEEK_SET))
                        {
                            //printf("ERROR STDIN\n");
                            //sigHndlr(0);   
                        }

                    }
                    
                }
                else{
                    sigHndlr(0);
                }


            }
        }
        else
            while(1)
                if((len = recv(sock, buf, SIZE, 0)) > 0)
                {
                    buf[len] = '\0';
                    if(strcmp(buf,"\n"))
                    {
                        printf("%s\n", buf);
                    }
                }
                else
                {
                    printf("You have left the chat\n");
                    sigHndlr(0);
                }

                
    return 0;
}


