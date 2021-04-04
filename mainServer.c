#include <stdio.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>    
#include <arpa/inet.h>    
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h>   
#include <string.h>     
// Casting from Int to Char
void int_to_char_5(int i,char c[]){
    int ind = 3;
    while(ind >= 0){
        c[ind] = (i % 10) + '0';
        i = i / 10;
        ind--;
    }
}
void error(char *errorMessage){
    printf("%s\n",errorMessage);
};

int main(int argc , char *argv[])  
{   
    char nobat_0[] = "0", nobat_1[] = "1", nobat_2[] = "2",nobat_3[] = "3",nobat_4[] = "4";
    int opt = 1; 
    int server_socket , addrlen , new_socket , client_socket[50] , max_clients = 50 , sel, i , valread , socket_temp;   
    int max_socket;   
    struct sockaddr_in address;    
    char buffer[50];   
    int arr_1[5],arr_2[5],arr_3[5],arr_4[5],arr_5[5];
    int index_1 = 0,index_2 = 0, index_3 = 0,index_4 = 0,index_5 = 0;
    fd_set readfds;   
    int SERVER_PORT = atoi(argv[1]);
    int port = 4000;

    for (i = 0; i < max_clients; i++)   
    {   
        client_socket[i] = 0;   
    }   
  
    if( (server_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)   
    {   
        error("create socket failed!");   
        exit(0);   
    }   
     

    if( setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )   
    {   
        error("setsockopt failed!");   
        exit(0);   
    }   
 
    address.sin_family = AF_INET;   
    address.sin_addr.s_addr = INADDR_ANY;   
    address.sin_port = htons(SERVER_PORT);   
    printf("port : %d\n",address.sin_port);  
 
    if (bind(server_socket, (struct sockaddr *)&address, sizeof(address))<0)   
    {   
        error("bind failed");   
        exit(0);   
    }  
    addrlen = sizeof(address);  
    printf("listen on port : %d \n", SERVER_PORT);   
         
    if (listen(server_socket, 50) < 0)   
    {   
        error("listen");   
        exit(0);   
    }   
  
    printf("Waiting for connections ...\n");   
         
    while(1)   
    {    
        FD_ZERO(&readfds);   
        FD_SET(server_socket, &readfds);   
        max_socket = server_socket;   
              
        for ( i = 0 ; i < max_clients ; i++)   
        {    
            socket_temp = client_socket[i];   
            if(socket_temp > 0)   
                FD_SET( socket_temp , &readfds);   
            if(socket_temp > max_socket)   
                max_socket = socket_temp;   
        }   
      
        sel = select( max_socket + 1 , &readfds , NULL , NULL , NULL);   
       
        if ((sel < 0) && (errno!=EINTR))   
        {   
            printf("select error");   
        }   
              
        if (FD_ISSET(server_socket, &readfds))   
        {   
            if ((new_socket = accept(server_socket,(struct sockaddr *)&address, (socklen_t*)&addrlen))<0)   
            {   
                error("accept");   
                exit(0);   
            }    
            printf("new connection accept!!!\n");   
        
            for (i = 0; i < max_clients; i++)   
            {   
                if( client_socket[i] == 0)
                {   
                    client_socket[i] = new_socket;   
                    printf("client %d added\n" , i);     
                    break;   
                }   
            }   
        }   
             
        for (i = 0; i < max_clients; i++)   
        {   
            socket_temp = client_socket[i];   
                 
            if (FD_ISSET( socket_temp , &readfds))   
            {   
                buffer[0] = '\n';
                if ((valread = read( socket_temp , buffer, 1024)) == 0)   
                {   
                    printf("client %d disconnect\n" , i);   
                    close(socket_temp);   
                    client_socket[i] = 0;   
                }   
                     
                else 
                {   
                    buffer[valread] = '\0';
                    printf("%s",buffer);
                }
                if(buffer[0] == '1'){
                    arr_1[index_1] = client_socket[i];
                    index_1 ++;
                    client_socket[i] = 0;
                }
                if(buffer[0] == '2'){
                    arr_2[index_2] = client_socket[i];
                    index_2 ++;
                    client_socket[i] = 0;
                }
                if(buffer[0] == '3'){
                    arr_3[index_3] = client_socket[i];
                    index_3 ++;
                    client_socket[i] = 0; 
                }
                if(buffer[0] == '4'){
                    arr_4[index_4] = client_socket[i];
                    index_4 ++;
                    client_socket[i] = 0; 
                }
                if(buffer[0] == '5'){
                    arr_5[index_5] = client_socket[i];
                    index_5 ++;
                    client_socket[i] = 0; 
                }
                if(index_1 == 5){
                    char port_char[3] = "";
                    int_to_char_5(port,port_char);
                    send(arr_1[0] , port_char , strlen(port_char) , 0 );
                    send(arr_1[1] , port_char , strlen(port_char) , 0 );
                    send(arr_1[2] , port_char , strlen(port_char) , 0 );
                    send(arr_1[3] , port_char , strlen(port_char) , 0 );
                    send(arr_1[4] , port_char , strlen(port_char) , 0 );
                    sleep(1);
                    send(arr_1[0] , nobat_0 , strlen(nobat_0) , 0 );
                    send(arr_1[1] , nobat_1 , strlen(nobat_1) , 0 );
                    send(arr_1[2] , nobat_2 , strlen(nobat_2) , 0 );
                    send(arr_1[3] , nobat_3 , strlen(nobat_3) , 0 );
                    send(arr_1[4] , nobat_4 , strlen(nobat_4) , 0 );
                    port++;
                    index_1 = 0;
                    printf("port send : %d",port - 1);
                }
                if(index_2 == 5){
                    char port_char[3] = "";
                    int_to_char_5(port,port_char);
                    send(arr_2[0] , port_char , strlen(port_char) , 0 );
                    send(arr_2[1] , port_char , strlen(port_char) , 0 );
                    send(arr_2[2] , port_char , strlen(port_char) , 0 );
                    send(arr_2[3] , port_char , strlen(port_char) , 0 );
                    send(arr_2[4] , port_char , strlen(port_char) , 0 );
                    sleep(1);
                    send(arr_2[0] , nobat_0 , strlen(nobat_0) , 0 );
                    send(arr_2[1] , nobat_1 , strlen(nobat_1) , 0 );
                    send(arr_2[2] , nobat_2 , strlen(nobat_2) , 0 );
                    send(arr_2[3] , nobat_3 , strlen(nobat_3) , 0 );
                    send(arr_2[4] , nobat_4 , strlen(nobat_4) , 0 );
                    port++;
                    index_2 = 0;
                    printf("port send : %d",port - 1);
                }
                if(index_3 == 5){
                    char port_char[3] = "";
                    int_to_char_5(port,port_char);
                    send(arr_3[0] , port_char , strlen(port_char) , 0 );
                    send(arr_3[1] , port_char , strlen(port_char) , 0 );
                    send(arr_3[2] , port_char , strlen(port_char) , 0 );
                    send(arr_3[3] , port_char , strlen(port_char) , 0 );
                    send(arr_3[4] , port_char , strlen(port_char) , 0 );
                    sleep(1);
                    send(arr_3[0] , nobat_0 , strlen(nobat_0) , 0 );
                    send(arr_3[1] , nobat_1 , strlen(nobat_1) , 0 );
                    send(arr_3[2] , nobat_2 , strlen(nobat_2) , 0 );
                    send(arr_3[3] , nobat_3 , strlen(nobat_3) , 0 );
                    send(arr_3[4] , nobat_4 , strlen(nobat_4) , 0 );
                    port++;
                    index_3 = 0;
                    printf("port send : %d",port - 1);
                }
                if(index_4 == 5){
                    char port_char[3] = "";
                    int_to_char_5(port,port_char);
                    send(arr_4[0] , port_char , strlen(port_char) , 0 );
                    send(arr_4[1] , port_char , strlen(port_char) , 0 );
                    send(arr_4[2] , port_char , strlen(port_char) , 0 );
                    send(arr_4[3] , port_char , strlen(port_char) , 0 );
                    send(arr_4[4] , port_char , strlen(port_char) , 0 );

                    sleep(1);
                    send(arr_4[0] , nobat_0 , strlen(nobat_0) , 0 );
                    send(arr_4[1] , nobat_1 , strlen(nobat_1) , 0 );
                    send(arr_4[2] , nobat_2 , strlen(nobat_2) , 0 );
                    send(arr_4[3] , nobat_3 , strlen(nobat_3) , 0 );
                    send(arr_4[4] , nobat_4 , strlen(nobat_4) , 0 );
                    port++;
                    index_4 = 0;
                    printf("port send : %d",port - 1);
                }
            }   
        }   
    }   
         
    return 0;   
}   