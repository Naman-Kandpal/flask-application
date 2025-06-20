# flask-application
Beginner Flask Application


UDP
// File: udp_server.c 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <arpa/inet.h> 
#define PORT 8080 
#define BUFFER_SIZE 1024 
int main() { 
 int sockfd; 
 char buffer[BUFFER_SIZE]; 
 struct sockaddr_in servaddr, cliaddr; 
 
 // 1. Create socket 
 sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
 if (sockfd < 0) { 
 perror("Socket creation failed"); 
 exit(EXIT_FAILURE); 
 } 
 // 2. Define server address 
 memset(&servaddr, 0, sizeof(servaddr)); 
 memset(&cliaddr, 0, sizeof(cliaddr)); 
 
 servaddr.sin_family = AF_INET; // IPv4 
 servaddr.sin_addr.s_addr = INADDR_ANY; // Any IP 
 servaddr.sin_port = htons(PORT); // Port 
 // 3. Bind the socket with the server address 
 if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 
0) { 
 perror("Bind failed"); 
 close(sockfd); 
 exit(EXIT_FAILURE); 
 } 
 printf("UDP Server is running on port %d...\n", PORT);
// 4. Receive message 
 int len, n; 
 len = sizeof(cliaddr); 
 n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) 
&cliaddr, &len); 
 buffer[n] = '\0'; 
 // 5. Display message 
 printf("Message from client: %s\n", buffer); 
 // Optional: Send reply 
 char *reply = "Message received!"; 
 sendto(sockfd, reply, strlen(reply), 0, (struct sockaddr *) &cliaddr, 
len); 
 // 6. Close socket 
 close(sockfd); 
 return 0; 
}


client 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <arpa/inet.h> 
#define PORT 8080 
#define BUFFER_SIZE 1024 
int main() { 
 int sockfd; 
 char buffer[BUFFER_SIZE]; 
 char *message = "Hello from client!"; 
 struct sockaddr_in servaddr; 
 // 1. Create socket 
 sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
 if (sockfd < 0) { 
 perror("Socket creation failed"); 
 exit(EXIT_FAILURE); 
 } 
 // 2. Define server address 
 memset(&servaddr, 0, sizeof(servaddr)); 
 servaddr.sin_family = AF_INET; 
 servaddr.sin_port = htons(PORT); 
 servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
 // 3. Send message to server 
 sendto(sockfd, message, strlen(message), 0, (const struct sockaddr *) 
&servaddr, sizeof(servaddr));
printf("Message sent to server: %s\n", message);
 // 4. Receive reply from server
 int len, n;
 len = sizeof(servaddr);
 n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) 
&servaddr, &len);
 buffer[n] = '\0';
 printf("Message from server: %s\n", buffer);
 // 5. Close socket
 close(sockfd);
 return 0;
}





TCP

// File: tcp_server.c

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h> // for close()

#include <netinet/in.h> // for sockaddr_in

#define PORT 8080

#define BUFFER_SIZE 1024

int main() {

int server_fd, new_socket;

char buffer[BUFFER_SIZE] = {0};

struct sockaddr_in address;

int addrlen = sizeof(address);

// 1. Create socket

server_fd = socket(AF_INET, SOCK_STREAM, 0);

if (server_fd == 0) {

perror("Socket failed");

exit(EXIT_FAILURE);

}

// 2. Bind socket to IP/Port

address.sin_family = AF_INET;

address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP

address.sin_port = htons(PORT);

if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {

perror("Bind failed");

exit(EXIT_FAILURE);

}

// 3. Listen

if (listen(server_fd, 3) < 0) {

perror("Listen failed");

exit(EXIT_FAILURE);

}

printf("Server is listening on port %d...\n", PORT);
// 4. Accept connection

new_socket = accept(server_fd, (struct sockaddr*)&address,

(socklen_t*)&addrlen);

if (new_socket < 0) {

perror("Accept failed");

exit(EXIT_FAILURE);

}

// 5. Read message from client

read(new_socket, buffer, BUFFER_SIZE);

printf("Message from client: %s\n", buffer);

// Optional: Send a reply

char *reply = "Hello from server!";

send(new_socket, reply, strlen(reply), 0);

// 6. Close sockets

close(new_socket);

close(server_fd);

return 0;

}

2.TCP code (C Language)

// File: tcp_client.c

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h> // for close()

#include <arpa/inet.h> // for sockaddr_in, inet_addr

#define PORT 8080

#define BUFFER_SIZE 1024

int main() {

int sock = 0;

struct sockaddr_in serv_addr;

char *message = "Hello from client!";

char buffer[BUFFER_SIZE] = {0};

// 1. Create socket

sock = socket(AF_INET, SOCK_STREAM, 0);

if (sock < 0) {

printf("\n Socket creation error \n");

return -1;

}

// 2. Set server address

serv_addr.sin_family = AF_INET;

serv_addr.sin_port = htons(PORT);

// Convert IPv4 addresses from text to binary

if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {

printf("\nInvalid address/Address not supported \n");

return -1;

}

// 3. Connect to server

if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
printf("\nConnection Failed \n");
return -1;

}
// 4. Send message to server

send(sock, message, strlen(message), 0);

printf("Message sent to server: %s\n", message);

// 5. Read server reply

read(sock, buffer, BUFFER_SIZE);

printf("Message from server: %s\n", buffer);

// 6. Close socket

close(sock);

return 0;

}

