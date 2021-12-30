#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <poll.h>
#include <math.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
//#include <malloc.h>



#define MAX_QUEUE 5
#define MEM_INC_SIZE 8
#define BUF_SIZE 256
#define NAME_SIZE 16


int clients;
char tmp[NAME_SIZE];
char buf[BUF_SIZE];
char message[BUF_SIZE];
struct pollfd * fds, * temp_fds;
//struct privates * private_list;
int main_socket, port, max_clients, events, temp_socket, i;
ssize_t n_read;
struct sockaddr_in adr;
char name[NAME_SIZE];
char ** name_list;

enum client_state {
    NEW_CLIENT,
    WAITING_FOR_A_NAME,
    WAITING_FOR_CONFORMATION,
    ONLINE,
    OFFLINE,
    EMPTY
};

struct user
{
    enum client_state current_state;
    int sock; //socket
    char nick[NAME_SIZE];
    int pr_size; //size of private_list
    char ** private_list; //array of nicknames user has sent private messages
};

struct user *user_list = NULL;

void new_user (int f_socket)
{
    //printf("DEB_f \n");
    //sleep(1);
    //memset(message, '\0', BUF_SIZE-1);
    //strcat(message, "Server v0.0.1\n Please, enter your name (not more than 16 symbols):");
    //strcat(message, "Please, enter your name (not more than 16 symbols):");
    //send(f_socket, message, BUF_SIZE, 0);
    //write(f_socket,"Server v0.0.1\n",strlen("Server v0.0.1\n"));
    //send(f_socket,"Please, enter your name (not more than 16 symbols):",strlen("Please, enter your name (not more than 16 symbols):"), 0);
    
    
    if (user_list == NULL)
    {
        user_list = (struct user *) calloc (1, sizeof (struct user));
        //user_list[0].private_list = (char **) malloc (sizeof (char *));
    }
    else
    {
        user_list = (struct user *) realloc (user_list, (sizeof (struct user)*clients));
        //user_list[clients-1].private_list = (char**) realloc (user_list[clients-1].private_list, (sizeof (char *)*clients));

    }
    

    memset (user_list[clients-1].nick, '\0', 16); 
    user_list[clients-1].sock = f_socket;
    user_list[clients-1].pr_size = 0;
    user_list[clients-1].private_list = NULL;

    
    
    //creating temporary name of guest equal to it's number
    user_list[clients-1].current_state = WAITING_FOR_A_NAME;
    char tmp[NAME_SIZE];
    memset(tmp, '\0', NAME_SIZE);
    sprintf(tmp, "%d", clients);
    tmp[((int)log10(clients)) + 1] = '\0';
    //printf("DEB_tmp: %s\n", tmp);
    strcpy(user_list[clients-1].nick, tmp);
    //user_list[clients-1].pr_size = 0;
    //user_list[clients-1].private_list[clients-1] = NULL;
    
    
    
    
    /*
     printf("DEB_f 2\n");
     //read(f_socket, user_list[clients].nick, 16);
     recv(f_socket, user_list[clients].nick, 16, 0);
     user_list[clients].nick[15] = '\0';
     
     
     
     printf("Server: %s\n", user_list[clients].nick);
     
     send(f_socket, "Your nick is: ", strlen("Your nick is: "), 0);
     send(f_socket, user_list[clients].nick, 16, 0);
     printf("DEB_f 4\n");
     */
    
    /*
     for (int j = 0; j < clients; j++)
     {
     printf("\nNICK: %s\n", user_list[j].nick);
     if (user_list[j].current_state ==  NEW_CLIENT)
     printf("%s\n", "NEW_CLIENT");
     if (user_list[j].current_state ==  WAITING_FOR_A_NAME)
     printf("%s\n", "WAITING_FOR_A_NAME");
     if (user_list[j].current_state ==  ONLINE)
     printf("%s\n", "ONLINE");
     
     }
     */
}
void Other_name(int i)
{
    send(user_list[i-1].sock, "Please, enter your name (not more than 16 symbols):",strlen("Please, enter your name (not more than 16 symbols):"), 0);
    user_list[i-1].current_state = WAITING_FOR_A_NAME;
    char tmp[NAME_SIZE];
    memset(tmp, '\0', NAME_SIZE);
    sprintf(tmp, "%d", clients);
    tmp[((int)log10(i)) + 1] = '\0';
    //printf("DEB_tmp: %s\n", tmp);
    strcpy(user_list[i-1].nick, tmp);
}


int check_the_private_name(char* new_name, int index)
{
    int result = 1;
    for (int tmp_i = 0; tmp_i < user_list[index].pr_size; tmp_i++)
    {
        if (!strcmp(user_list[index].private_list[tmp_i], new_name))
        {
            result = 0;
            break;
        }
        
    }
    return result;
}

void Send_private_list(int i)
{
    memset(message, '\0', BUF_SIZE);
    strcat(message, "Server: List of users you have sent private messages: \n");
    //send(fds[i].fd, message, BUF_SIZE, 0);
    
    //memset(message, '\0', BUF_SIZE);
    strcat(message, "Server: ");
    
    for (int p = 0; p < user_list[i-1].pr_size; p++)
    {
        //printf("DEB_PRIVS_2: %s\n", user_list[i-1].private_list[p]);
        //user_list[i-1].private_list[NAME_SIZE-1] = "\0";
        strcat(message, (user_list[i-1].private_list[p]));
        strcat(message, " ");
    }
    //printf("DEB_PRIVS_3: %s\n", message);
    send(fds[i].fd, message, BUF_SIZE, 0);
}

void Show_users(int i)
{
    char message[1024];
    memset(message, '\0', 1024);
    memset(buf, '\0', BUF_SIZE);
    strcat(buf, "Server: \n");
    for (int j = 0; j < clients; j++)
    {
        memset(buf, '\0', BUF_SIZE);
        strcat(buf, "\n");
        strcat(buf,"    NICK of user ");
        
        memset(tmp, '\0', NAME_SIZE);
        sprintf(tmp, "%d", j+1);
        strcat(buf, tmp);
        
        strcat(buf, ": ");
        strcat(buf, user_list[j].nick);
        //send(fds[i].fd, buf, 255, 0);
        strcat(buf, "\n");
        
        if (user_list[j].current_state ==  NEW_CLIENT)
            strcat(buf, "   Current State: NEW_CLIENT\n");
        if (user_list[j].current_state ==  WAITING_FOR_A_NAME)
            strcat(buf, "   Current State: WAITING_FOR_A_NAME\n");
        if (user_list[j].current_state ==  ONLINE)
            strcat(buf, "   Current State: ONLINE\n");
        if (user_list[j].current_state ==  OFFLINE)
            strcat(buf, "   Current State: OFFLINE\n");
        if (user_list[j].current_state ==  EMPTY)
            strcat(buf, "   Current State: EMPTY\n");
        strcat(message, buf);
        
    }
    send(fds[i].fd, message, BUF_SIZE, 0);
}

void Send_user_out(int i, char * last_message)
{
    for(int p = 0; p < clients; p++)
    {
        if(user_list[p].current_state == ONLINE)
        {
            memset(message, '\0', BUF_SIZE);
            strcat(message, "Server: ");
            strcat(message, "User ");
            strcat(message, user_list[i-1].nick);
            strcat(message, " disconnected\n");
            //send(fds[p+1].fd, message, BUF_SIZE, 0);
            //printf("%s: %s\n",user_list[i-1].nick, word);
            //printf("User %s disconnected\n", user_list[i-1].nick);
            //memset(message, '\0', BUF_SIZE);
            strcat(message, "Server: ");
            strcat(message, "Last message: ");
            strcat(message, last_message);
            send(fds[p+1].fd, message, BUF_SIZE, 0);
        }
    }
}

int chek_new_name(char *buf)
{
    int result = 0;
    int p;
    for( p = 0; p < clients; p++)
    {
        if (!strcmp(buf, user_list[p].nick))
        {
            if (user_list[p].current_state != EMPTY)
            {
                result = 1;
                //printf("YES\n");
                break;
            }
        }
    }
    return result;
}
int Index_equal_name (char *buf)
{
    int p;
    for( p = 0; p < clients; p++)
    {
        if (!strcmp(buf, user_list[p].nick))
        {
            if (user_list[p].current_state != EMPTY)
            {
                break;
            }
        }
    }
    return p;
}

void delete_client(int n)
{
    //printf("DEB_F_DEL\n");
    if(n == 0)
        for(int i = 0; i < clients ; i++)
    {
        shutdown(user_list[i].sock,2);
        close(user_list[i].sock);
    }
    else
    {

        shutdown(user_list[n].sock,2);
        close(user_list[n].sock);
        user_list[n].sock = 0;
        strcpy(user_list[n].nick," ");
    }
}

void sigHndlr(int s)
{
    free(fds);
    free(temp_fds);
    delete_client(0);

    for (int  i = 0; i < clients ; i++)
    {
        for (int j = 0; j < user_list[i].pr_size; j++)
        {
            free(user_list[i].private_list[j]);
        }
             free(user_list[i].private_list);

    }

    free(user_list);



    printf("Good Bye! \n");
    exit(0);
}


int main(int argc, char * argv[]){
    //char tmp;
    
            struct addrinfo hints;
            struct addrinfo *result, *rp;
            int sfd, s;
            struct sockaddr_storage peer_addr;
            socklen_t peer_addr_len;
    
    signal(SIGINT,sigHndlr);
    
    if(argc < 1){
        fprintf(stderr,"Необходимо указать номер порта в параметрах\n");
        return 1;
    }
    
                memset(&hints, 0, sizeof(struct addrinfo));
               hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
               hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
               hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
               hints.ai_protocol = 0;          /* Any protocol */
               hints.ai_canonname = NULL;
               hints.ai_addr = NULL;
               hints.ai_next = NULL;
    
                s = getaddrinfo(NULL, argv[1], &hints, &result);
               if (s != 0) {
                   fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
                   exit(EXIT_FAILURE);
               }
               for (rp = result; rp != NULL; rp = rp->ai_next) {
                   main_socket =  socket(rp->ai_family, rp->ai_socktype,0);
                   if (main_socket  == -1)
                       continue;

                   errno = 0;
                   
                   
                   if (bind(main_socket, rp->ai_addr, rp->ai_addrlen) == 0)
                                     break;                  /* Success */

                   //close(mai);
                   
               }

               if (rp == NULL) {               /* No address succeeded */
                   fprintf(stderr, "Could not bind\n");
                   exit(EXIT_FAILURE);
               }

               //freeaddrinfo(result);
    
    
    
    
    /*
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    getaddrinfo(NULL, MYPORT, &hints, &res);

    // создадим сокет, биндим его, и слушаем:

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(sockfd, res->ai_addr, res->ai_addrlen);
    listen(sockfd, BACKLOG);

    // теперь принимаем входящее соединение:
    */
    /*
    port = atoi(argv[1]);
    
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    adr.sin_addr.s_addr = INADDR_ANY;

    errno = 0;
    main_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (main_socket == -1){
        fprintf(stderr, "%s (%d): Сокет не был создан: %s\n",
                __FILE__, __LINE__ - 2,  strerror(errno));
        exit(1);
    }
    
    errno = 0;
    if(bind(main_socket, (struct sockaddr *) &adr, sizeof(adr)) == -1){
        fprintf(stderr, "%s (%d): Не удалось привязать к адресу: %s\n",
                __FILE__, __LINE__ - 2,  strerror(errno));
        exit(1);
    }
     */
    
    errno = 0;
    if(listen(main_socket, MAX_QUEUE) == -1){
        fprintf(stderr, "%s (%d): Не удалось установить сокет в режим TCP: %s\n",
                __FILE__, __LINE__ - 2,  strerror(errno));
        exit(1);
    }
    
    max_clients = MEM_INC_SIZE;
    clients = 0;
    
    errno =  0;
    fds = malloc(sizeof(struct pollfd) * (max_clients + 1));
    if(fds == NULL){
        fprintf(stderr, "%s (%d): Структура не была создана: %s\n",
                __FILE__, __LINE__ - 2,  strerror(errno));
        exit(1);
    }
    
    fds[0].fd = main_socket;
    fds[0].events = POLLIN | POLLERR | POLLPRI | POLLOUT;
    fds[0].revents = 0;
    
    
    
    for(;;){
        //printf("Hello\n");
        events = poll(fds, clients + 1, 1000);
        
        if(events == -1){
            fprintf(stderr, "%s (%d): Проблемы с poll: %s\n",
                    __FILE__, __LINE__ - 2,  strerror(errno));
            exit(1);
        }
        
        if(events == 0)
            continue;
        
        
        
        
        
        
        if(fds[0].revents)
        {
            temp_socket = accept(main_socket, NULL, NULL);
            if(temp_socket == -1){
                fprintf(stderr, "%s (%d): Не удалось принять: %s\n",
                        __FILE__, __LINE__ - 2,  strerror(errno));
                exit(1);
            }
            
            //new_user(temp_socket);
            clients++;//////////////
            
            
            //printf("User %d joined\n", clients);
            if(clients >= max_clients){
                max_clients += MEM_INC_SIZE;
                temp_fds = fds;
                fds = realloc(fds, sizeof(struct pollfd) * (max_clients + 1));
                if(fds == NULL){
                    fprintf(stderr, "%s (%d): Ошибка realloc: %s\n",
                            __FILE__, __LINE__ - 2,  strerror(errno));
                    free(temp_fds);
                    exit(1);
                }
            }
            
            fds[clients].fd = temp_socket;
            fds[clients].events = POLLIN | POLLERR | POLLPRI | POLLHUP;
            fds[clients].revents = 0;
            
            
            
            
            memset(message, '\0', BUF_SIZE-1);
            strcat(message, "Server v0.0.1\n Please, enter your name (not more than 16 symbols):");
            //strcat(message, "Please, enter your name (not more than 16 symbols):");
            send(fds[clients].fd, message, 255, 0);
            new_user(temp_socket);
            
            
            fds[0].revents=0;
            fds[clients].revents=0;
            
        }
        
        
        for(i = 1; i <= clients; i++){
            //printf("DEBUG_ev %d: %d\n", i, fds[i].revents);
            
            if(fds[i].revents){
                //printf("DEBUG_ev %d: %d\n", i, fds[i].revents);
                
                memset(buf, '\0', 255);//in the end
                
                //while((n_read = read(fds[i].fd, buf, 255)) > 0)
                n_read = read(fds[i].fd, buf, 255);
                {
                    //printf("DEB_READ: %zd\n", n_read);
                    
                    for (int tmp = 0; tmp < n_read; tmp ++)
                    {
                        if(buf[tmp] == '\n')
                            buf[tmp] = '\0';
                    }
                    //printf("DEB_MES: %s\n", buf);
                    
                    if(n_read == 0){//Case of ctrl-c in client for example
                        printf("User %s disconnected\n", user_list[i-1].nick);
                        user_list[i-1].current_state = OFFLINE;
                        close(fds[i].fd);
                        fds[i].fd = -1;
                        
                        for(int p = 0; p < clients; p++)
                        {
                            if(user_list[p].current_state == ONLINE)
                            {
                                memset(message, '\0', BUF_SIZE);
                                strcat(message, "Server: ");
                                strcat(message, "User ");
                                strcat(message, user_list[i-1].nick);
                                strcat(message, " disconnected");
                                send(fds[p+1].fd, message, BUF_SIZE, 0);
                                //printf("%s: %s\n",user_list[i-1].nick, word);
                                //printf("User %s disconnected\n", user_list[i-1].nick);
                            }
                        }
                    }
                    if(n_read == -1){
                        fprintf(stderr, "%s (%d): Ошибка при чтении из сокета: %s\n",
                                __FILE__, __LINE__ - 2,  strerror(errno));
                        close(fds[i].fd);
                        fds[i].fd = -1;
                        exit(1);
                    }
                    
                    if(n_read > 0 && buf[0] != '\0' && buf[0] != '\n')
                    {
                        //printf("DEB 2\n");
                        
                        switch (user_list[i-1].current_state)
                        {
                            case NEW_CLIENT:
                                //printf("WAIT 1\n");
                                user_list[i-1].current_state = WAITING_FOR_A_NAME;
                                
                                break;
                                
                            case WAITING_FOR_A_NAME:
                                //printf("WAIT 2\n");
                                //read(f_socket, user_list[clients].nick, 16);
                                //recv(fds[i].fd, user_list[i].nick, 16, 0);
                                //printf("Server: %s\n", buf);
                                buf[15]='\0';
                                
                                for(int w = 0; w < NAME_SIZE; w++)//deleting \n symbol to make it comparable with existing names
                                {
                                    if(buf[w] == '\n')
                                        buf[w] = '\0';
                                }
                                int p;
                                if  (((p = chek_new_name(buf)) > 0) || buf[0] == '\0' || buf[0] == '\n')//p is index
                                {
                                    //printf("DEB_WAIT_NAME_p: %d\n", p);
                                    memset(message, '\0', BUF_SIZE);
                                    strcat(message, "Server: User with this name aready exist or name format prohibited\n");
                                    //strcat(message, user_list[i-1].nick);
                                    //strcat(message,"Do you want to connect to accout(y) or to create new one(n)? (y/n) \n");
                                    strcat(message,"Try another name \n");
                                    //printf("User with this name aready exist\n");
                                    //printf("Do you want to connect to accout(y) or to create new one(n)? (y/n) \n");
                                    send(fds[i].fd, message, BUF_SIZE, 0);
                                    Other_name(i);
                                    
                                    
                                    /*
                                     send(fds[i].fd, message, BUF_SIZE, 0);
                                     
                                     user_list[i-1].current_state = WAITING_FOR_CONFORMATION;
                                     
                                     
                                     //Anyway the new account with this name was created (in order to save it)
                                     memset(user_list[i-1].nick, '\0', 16);
                                     //deleting \n symbol in the end of string
                                     strcpy(user_list[i-1].nick, buf);
                                     user_list[i-1].nick[15] = '\0';
                                     for(int w = 0; w < 16; w++)
                                     {
                                     if(user_list[i-1].nick[w] == '\n')
                                     user_list[i-1].nick[w] = '\0';
                                     }
                                     */
                                    
                                    break;
                                }
                                else
                                {
                                    memset(user_list[i-1].nick, '\0', NAME_SIZE);
                                    //deleting \n symbol in the end of string
                                    strcpy(user_list[i-1].nick, buf);
                                    user_list[i-1].nick[NAME_SIZE-1] = '\0';
                                    for(int w = 0; w < NAME_SIZE; w++)
                                    {
                                        if(user_list[i-1].nick[w] == '\n')
                                            user_list[i-1].nick[w] = '\0';
                                    }
                                    
                                    
                                    
                                    //printf("Server: %s\n", user_list[i-1].nick);
                                    
                                    send(fds[i].fd, "Your nick is: ", strlen("Your nick is: "), 0);
                                    send(fds[i].fd, user_list[i-1].nick, NAME_SIZE, 0);
                                    //printf("WAIT 4\n");
                                    user_list[i-1].current_state = ONLINE;
                                    
                                    
                                    printf("User %s joined\n", user_list[i-1].nick);
                                    
                                    memset(message, '\0', BUF_SIZE);
                                    strcat(message, "Server: User ");
                                    strcat(message, user_list[i-1].nick);
                                    strcat(message," joined");
                                    for(int p = 0; p < clients; p++)
                                    {
                                        if(user_list[p].current_state == ONLINE)
                                            send(fds[p+1].fd, message, BUF_SIZE, 0);
                                    }
                                    
                                }
                                
                                break;
                                
                            case WAITING_FOR_CONFORMATION://State of waiting of user's solution to connect to exist account or to create new one
                                /* if(buf[0] == 'y' || buf[0] == 'Y')
                                 {
                                 int connection_index;
                                 connection_index = Index_equal_name(user_list[i-1].nick);//connection_index is an index of account we want to connect
                                 //user_list[connection_index].sock = user_list[i-1].sock;
                                 user_list[i-1].sock = -1;
                                 user_list[i-1].current_state = EMPTY;//in future new user can register in this field
                                 printf("User %s joined\n", user_list[i-1].nick);
                                 user_list[connection_index].current_state = ONLINE;
                                 printf("DEB_IND: %d\n", connection_index);
                                 printf("DEB_IND: %d\n", i-1);
                                 
                                 sprintf(tmp, "%d", user_list[connection_index].sock);
                                 memset(message, '\0', 255);
                                 strcat(message,"sock ");
                                 strcat(message, tmp);
                                 send(fds[i].fd, message, BUF_SIZE, 0);
                                 
                                 
                                 memset(message, '\0', 255);
                                 strcat(message, "Server: User ");
                                 strcat(message, user_list[i-1].nick);
                                 strcat(message," joined\n");
                                 
                                 for(int p = 0; p < clients; p++)
                                 {
                                 if(user_list[p].current_state == ONLINE)
                                 send(fds[p+1].fd, message, 255, 0);
                                 }
                                 
                                 }
                                 else*/
                            {
                                Other_name(i);
                                break;
                            }
                                break;
                                
                            default:
                                //printf("WAIT 3\n");
                                buf[n_read]='\0';
                                //printf("CMP %s  |   %s\n", "/names", buf);
                                //printf("CMP %d\n", strcmp("/names", buf));
                                //char names[] = "/names";
                                
                                /*
                                 int y = 0;
                                 while(buf[y])
                                 {
                                 printf("%d: %c\n",y, buf[y]);
                                 y++;
                                 }
                                 */
                                
                                
                                //Call from user of command /names
                                char * word;
                                char buf2[BUF_SIZE];
                                strcpy(buf2, buf);
                                word = strtok(buf2, " ");
                                if(!strcmp(word, "/names") || !strcmp(word, "/names\n"))
                                {
                                    Show_users(i);
                                    
                                }
                                else
                                {
                                    if(!strcmp(word, "/quit") || !strcmp(word, "/quit\n"))
                                    {
                                        word = strtok(NULL, "\0");
                                        user_list[i-1].current_state =  OFFLINE;
                                        close(fds[i].fd);
                                        fds[i].fd = -1;
                                        
                                        Send_user_out(i, word);
                                        
                                        
                                    }
                                    else
                                    {
                                        if(!strcmp(word, "/private") || !strcmp(word, "/private\n"))//private message to user
                                        {
                                            word = strtok(NULL, " ");
                                            if(word == NULL)
                                            {
                                                //printf("DEB_WORD2: %s\n", word);
                                                memset(message, '\0', BUF_SIZE);
                                                strcat(message, "Server: No such user or no name input");
                                                send(fds[i].fd, message, BUF_SIZE, 0);
                                                break;
                                                
                                            }
                                            //printf("DEB_WORD: %s\n", word);
                                            int p;
                                            for(p = 0; p < clients; p++)//searching for destination user
                                            {
                                                if (!strcmp(word, user_list[p].nick))
                                                    break;
                                            }
                                            
                                            if (p ==  clients)//if there is no user with such name
                                            {
                                                memset(message, '\0', BUF_SIZE);
                                                strcat(message, "Server: No such user or no name input");
                                                send(fds[i].fd, message, BUF_SIZE, 0);
                                            }
                                            else
                                            {
                                                if((word = strtok(NULL, "\0")) != NULL)//word is message of user
                                                {
                                                    //printf("DEB_MES: %s\n", word);
                                                    memset(message, '\0', BUF_SIZE);
                                                    strcat(message, user_list[i-1].nick);
                                                    strcat(message, "(private): ");
                                                    strcat(message, word);
                                                    send(fds[p+1].fd, message, BUF_SIZE, 0);
                                                    
                                                    if(check_the_private_name(user_list[p].nick, i-1))//checking if the user is in the list already
                                                    {
                                                        //addind user's name to the list
                                                        int tmp_id = user_list[i-1].pr_size++;
                                                        int j = i-1;
                                                        user_list[j].private_list = (char**) realloc (user_list[j].private_list, (sizeof (char *)*(tmp_id+1)));
                                                        user_list[j].private_list[tmp_id] = NULL;
                                                        user_list[j].private_list[tmp_id] = realloc(user_list[j].private_list[tmp_id],NAME_SIZE*(sizeof(char)));
                                                        memset(user_list[j].private_list[tmp_id], '\0', NAME_SIZE);
                                                        strcpy(user_list[j].private_list[tmp_id],
                                                               user_list[p].nick);
                                                        //printf("DEB_PRIVS: %s\n", user_list[i-1].private_list[tmp_id]);
                                                    }
                                                    
                                                    
                                                }
                                                else
                                                {
                                                    memset(message, '\0', BUF_SIZE);
                                                    strcat(message, "Server: No message");
                                                    send(fds[i].fd, message, BUF_SIZE, 0);
                                                }
                                            }
                                            
                                        }
                                        else
                                        {
                                            if(!strcmp(word, "/privates") || !strcmp(word, "/privates\n"))
                                            {
                                                Send_private_list(i);
                                            }
                                            else
                                            {
                                                if(!strcmp(word, "/help") || !strcmp(word, "/help\n"))
                                                {
                                                    memset(message, '\0', BUF_SIZE);
                                                    strcpy(message,"Commands: \n/help - command list \n/quit <message> - leave the chat with last message\n/names - list of current users \n/private <nickname> <message> - send private message\n/privates - list of  private messages");
                                                    send(fds[i].fd, message, BUF_SIZE, 0);
                                                }
                                                else//it's a case of normal message sent for everyone
                                                {
                                                    buf[n_read]='\0';
                                                    //for everyone!!!
                                                    for( int p = 0; p < clients; p++)
                                                    {
                                                        if((user_list[p].current_state == ONLINE) && (p != i-1) )
                                                        {
                                                            memset(message, '\0', BUF_SIZE);
                                                            strcat(message, user_list[i-1].nick);
                                                            strcat(message, ": ");
                                                            strcat(message, buf);
                                                            send(fds[p+1].fd, message, BUF_SIZE, 0);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                break;
                        }
                    }
                    memset(buf, '\0', 255);//in the end
                }
            }
            //printf("DEB_OUT\n");
            fds[i].revents = 0;//to make poll usefull again
        }
    }
    printf("BYBY\n");
    return 0;
}

