#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    const char* serverName = "127.0.0.1"; // Example IP also a pointer to char
    int serverPort = 8080; // Echo port
    char msg_sent[2048] = "Okay this works";
    char msg_received[2048];

    struct sockaddr_in c; //sockaddr_in is predefined no need to redefine it
    socklen_t server_addr_len = sizeof(c);

    struct sockaddr_in my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    socklen_t mylen = sizeof(my_addr);
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(53); // htons --> host to network short
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    memset(&c, 0, sizeof(c));// used to clear a variable memset func
    c.sin_family = AF_INET;
    c.sin_port = htons(serverPort); // htons --> host to network short
    inet_aton(serverName, &c.sin_addr); // internet address to network address <-- inet_aton

    int mySock = socket(AF_INET, SOCK_STREAM, 6);
    int myBind = bind(mySock, (struct sockaddr*)&my_addr, mylen);

    int myCon = connect(mySock, (struct sockaddr*)&c, mylen);
    if (myCon == -1)
    {
        perror("Error: ");
    }
    
    return 0;
}