#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

int main(){
    int sock; long valread;
    struct sockaddr_in serv_address;
    char *hello = "Hello from client";
    char buffer[10000] = {0};

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Creation of socket failed");
        exit(EXIT_FAILURE);
    }
    memset(&serv_address, '\0', sizeof(serv_address));

    serv_address.sin_family = AF_INET;
    serv_address.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_address.sin_port = htons(PORT);

    if(connect(sock, (struct sockaddr *)&serv_address, sizeof(serv_address)) < 0){
        perror("Connection to server failed");
        exit(EXIT_FAILURE);
    }

    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sock, buffer, 10000);
    printf("%s\n", buffer);

    close(sock);

	return 0;
}
