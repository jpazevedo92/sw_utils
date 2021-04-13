#include "socket_utils.h"

/*
    Client init function 
*/
void initClient(char *srv_ip, char *clt_message)
{
    int sockfd; 
    struct sockaddr_in     servaddr; 
  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr(srv_ip); 

    sendto(sockfd, (const char *)clt_message, strlen(clt_message), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr));

    close(sockfd); 
   
}

/*
    Server init function 
*/
void initServer(){
    int sockfd; 
    char command[MAXLINE]; 
    char result[MAXLINE];
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    printf("UAVProtocol Server:\n\tWaiting for new commands\n");
    
    while(1)
    {
        int n;

        len = sizeof(cliaddr);  //len is value/resuslt 
        n = recvfrom(sockfd, (char *)command, MAXLINE,  
            MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
            &len); 
        command[n] = '\0'; 
        printf("Command received: %s\n", command);
        execCommand(command, result);
        sendto(sockfd, (const char *)result, strlen(result),  
              MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
              len);
        printf("Response to command %s: %s\n", command,result);

        //Wait for new connection
        printf("UAVProtocol Server:\n\tWaiting for new commands\n");
    }
}

/*
    Protocol Command functions
*/

void execCommand(char* command, char *result){
    printf("\tEnter execCommand\n");
    char *token;
    if(command[2] != '_'){
         token = strtok_r(command, "\'", &command);
    } else
     {
        token = strtok_r(command, "_", &command);
     }
    char option = token[1];
    printf("\tOption %c\n", option);
    
    switch(option){
	 
        case 'a':
        case 'A':
            printf("\tEnter execCommand: 'A' option\n");
            execAliveCheck(result);
            break;
        case 'x':
        case 'X':
             sprintf(result, "X command\n");
             break;
         default:
             sprintf(result, "Default command\n");
             break;
	}
}

void execAliveCheck(char *result){
    printf("\t\tAlive Check Command\n");
    sprintf(result, "OK");
}

