#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <stdio.h>    
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <stdlib.h>     
#include <string.h>    
#include <unistd.h>
#include <signal.h>
#include <netinet/in.h>  
#include <sys/time.h>   
#include <errno.h> 

volatile sig_atomic_t alarm_flag = 0;


static void print_console (const char *s)
{
    size_t len = 0;
    while (*s++){
        len++;
    }
    write (STDOUT_FILENO, s, strlen(s));
}

void handle_alarm( int sig ) {
    alarm_flag = 1;
}

void send_message(int sockfd()){
    char buff[50]; 
    int n; 
    while ((buff[n++] = getchar()) != '\n') ; 
    write(sockfd, buff, sizeof(buff));
} 


int char_to_int_4(char c[]){
    int res = 0,temp = 0;
    for(int i = 0; i <= 3; i++){
        temp = c[i] - '0';
        res = res *10 + temp;
    }
    return res;
}

void error(char *errorMessage){
    printf("%s\n",errorMessage);
}; 
int main(int argc, char *argv[])
{ 
    fd_set fds;
    FD_ZERO(&fds);
    int max_fd = 0,nobat = 0;
    //print_console("salam\n");
    int PORT = atoi(argv[1]),port = 0;
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
    int max_player = 0;
    int max_size_string = 100;
    signal( SIGALRM, handle_alarm );
    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 

    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 

    // connect the client socket to server socket 
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for chat 
    int sel = 0;
    FD_SET(sockfd, &fds);
    max_fd = sockfd;
    char projName[5][20] = {
                         "Super Mario\n",
                         "Maze\n",
                         "Ping Pong\n",
                         "TIC TAC TOE\n",
                         "Snakes\n"
    };
    int i,j;
    for(j = 0; j < 5; j++){
        printf("%d - ",j+1);
        for(i = 0; projName[j][i] != '\0'; i++)
        {
        printf("%c",projName[j][i]);
        }
    }
    printf("Which Project do you prefer???\n");
    int n = 0; 
    char buff[50]; 
    FD_SET(STDIN_FILENO, &fds);
    if(STDIN_FILENO > max_fd)max_fd = STDIN_FILENO;
    while(1){
        sel = select(max_fd + 1, &fds, NULL, NULL, NULL);
        if(FD_ISSET(STDIN_FILENO, &fds)){
            while ((buff[n++] = getchar()) != '\n') ;
            printf("%s\n",buff);
            write(sockfd, buff, sizeof(buff));
            max_player = buff[0] - '0';
            printf("You Choosed Project Number %d.\n",max_player);
            bzero(buff, sizeof(buff)); 
            break;
        }
    }
    FD_ZERO(&fds);
    FD_SET(sockfd, &fds);
    max_fd = sockfd;
    while (1){
        sel = select(max_fd + 1, &fds, NULL, NULL, NULL);
        if(FD_ISSET(sockfd, &fds)){
            read(sockfd, buff, sizeof(buff));
            printf("port: %s\n",buff);
            port = char_to_int_4(buff);
            printf("port : %d\n",port);
            break;
        }
    } 
    sleep(1);
    while(1){
        sel = select(max_fd + 1, &fds, NULL, NULL, NULL);
        if(FD_ISSET(sockfd, &fds)){
            read(sockfd, buff, sizeof(buff));
            nobat = buff[0] - '0';
            printf("nobat: %d\n",nobat);
            break;
        }
    }

    int player_score[max_player];
    sleep(1);
    printf("___________START____________\n");
    for(int i = 0; i < max_player; i++){
        player_score[i] = 0;
    }







    
    char recvString[max_size_string+1];
    int recvStringLen;
    int new_sock;
    struct sockaddr_in broadcastAddr; 
    char *broadcastIP;             
    unsigned short broadcastPort;              
    int broadcastPermission,reuse;               
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));
    if ((new_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        error("socket() failed");
    broadcastPermission = 1;
    reuse = 1;
    if (setsockopt(new_sock, SOL_SOCKET, SO_BROADCAST,(void*) &broadcastPermission, sizeof(broadcastPermission)) < 0) error("setsockopt() failed");
    if (setsockopt(new_sock, SOL_SOCKET, SO_REUSEADDR,(void*) &reuse, sizeof(reuse)) < 0) error("setsockopt() failed");
    
    max_fd = new_sock;
    FD_SET(max_fd, &fds);
    broadcastAddr.sin_family = AF_INET;                 
    broadcastAddr.sin_addr.s_addr = inet_addr("127.255.255.255");
    broadcastAddr.sin_port = htons(port);  
        

    if (bind(new_sock, (const struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr)) < 0)error("bind() failed");
    char* str = argv[1];
    char x,y,jahat;
    alarm_flag = 0;
    int tedad = 0;
    while (tedad < 5) 
    {   
        
        if(tedad % max_player == nobat){
            alarm(10);
            char send_str[] = "x\n";
            printf("its your turn:\n");
            FD_ZERO(&fds);
            FD_SET(new_sock, &fds);
            max_fd = new_sock;  
            sel = 0; 
            while(1){
                FD_SET(STDIN_FILENO, &fds);
                if(STDIN_FILENO > max_fd)max_fd = STDIN_FILENO;
                sel = select(max_fd + 1, &fds, NULL, NULL, NULL);
                if(alarm_flag == 1 || sel == -1){
                    send_str[0] = '999999';
                    printf("%s",send_str);
                    sendto(new_sock, send_str, strlen(send_str), 0,(struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr));
                    printf("your time end!!!!\n");
                    alarm_flag = 0;
                    break;
                }
                else if(FD_ISSET(STDIN_FILENO, &fds)){
                    n = 0;
                    while ((send_str[n++] = getchar()) != '\n');
                    sendto(new_sock, send_str, strlen(send_str), 0,(struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr));
                    printf("%s\n",send_str);
                    alarm(0);
                    break;
                }
            }
            
        }
        while (1)
        {
            sel = select(max_fd + 1, &fds, NULL, NULL, NULL);
            if(FD_ISSET(new_sock, &fds)){
                if ((recvStringLen = recvfrom(new_sock, recvString, max_size_string, 0, NULL, 0)) < 0)
                    error("recvfrom() failed");
                recvString[recvStringLen] = '\0';
                printf("Received: %s\n", recvString);   
                sleep(1); 
                x = recvString[0];
                player_score[tedad] = x;
                tedad ++;
                break;
            }
        }
    }
    int winer = 0;
    for(int temp = 0; temp < max_player; temp++){
        if(player_score[temp] > player_score[winer])winer = temp;
    }
    printf("player %d win!!!\n",winer);
    // close the socket 
    close(sockfd); 
} 