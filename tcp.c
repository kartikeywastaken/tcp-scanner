#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    const char* serverName = "127.0.0.1"; // Example IP also a pointer to char
    int serverPort = 53; // DNS port
    char msg_sent[2048] = "Okay this works";
    char msg_received[2048];

    struct sockaddr_in c; //sockaddr_in is predefined no need to redefine it
    socklen_t server_addr_len = sizeof(c);

    struct sockaddr_in my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    socklen_t mylen = sizeof(my_addr);
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(53); // htons --> host to network short

    memset(&c, 0, sizeof(c));// used to clear a variable memset func
    c.sin_family = AF_INET;
    c.sin_port = htons(serverPort); // htons --> host to network short
    // inet_aton(serverName, &c.sin_addr); // internet address to network address <-- inet_aton
    // inet converts the string to binary numbers
    for ( int i = 1; i < 255; i++)
    {
        char targetIP[20];
        sprintf(targetIP, "192.168.1.%d", i);
        printf("Checking %s...\n", targetIP); // Add this!
        fflush(stdout);
        inet_aton(targetIP, &c.sin_addr);
        int mySock = socket(AF_INET, SOCK_STREAM, 6);
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;
        setsockopt(mySock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
        setsockopt(mySock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        int myCon = connect(mySock, (struct sockaddr*)&c, sizeof(c));
        if (myCon == 0)
     {
        printf("Success!\n");
        printf("The open port found was 192.168.1.%d \n", i);
     }

     close(mySock);
    }

    printf("All ports were successfully scanned! ");

    return 0;
}