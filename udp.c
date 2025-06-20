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