#ifndef SOCKET_UTILS_H_
#define SOCKET_UTILS_H_

/* Includes section */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <sys/ioctl.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h>
#include <net/if.h>
#include <ifaddrs.h>

/* Constant variables / MACROS */
#define PORT        8000
#define PORT1       8001
#define MAXLINE     1024
#define STR_EQUAL   0 
#define False       0
#define True        1

#define IP          1   
#define ADDRESS     2
#define MASK        3

/* Function Headers */

void initClient(char *srv_ip, char *clt_message);
void initUAVClient(char *srv_ip, char *clt_message, char *result);

void checkHostName(int hostname);
void checkHostEntry(struct hostent * hostentry);
void getIfIp(char* iface, char *result);
void getMaskPrefixLength(char *mask, char *result);
void print_ip(unsigned int ip, char *result);

void initServer();
void execCommand(char* command, char *result);
void execAliveCheck(char *result);

#endif /* SOCKET_UTILS_H_*/