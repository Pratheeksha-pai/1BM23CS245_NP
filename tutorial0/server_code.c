#include "unp.h"

int main(int argc, char **argv)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    int n;

    /* Create socket */
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    /* Fill server address structure */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    /* Bind socket to port 9877 */
    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

    /* Listen for connections */
    Listen(listenfd, LISTENQ);

    printf("TCP server listening on port 9877...\n");

    while (1)
    {
        /* Accept client connection */
        connfd = Accept(listenfd, (SA *)NULL, NULL);

        printf("Client connected.\n");

        /* Receive and echo data */
        while ((n = Read(connfd, buf, MAXLINE)) > 0)
        {
            Write(connfd, buf, n);
        }

        Close(connfd);

        printf("Client disconnected.\n");
    }
}
