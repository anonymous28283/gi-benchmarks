
void error()
{
    perror("Socket Creation Failed");
    exit(EXIT_FAILURE);
}


int main()
{

    uint32_t sockfd,
        conn;
    char recvbuff[1024],
        sendbuff[1024];


    struct sockaddr_in server_addr,
        client_addr;


    socklen_t ClientLen;


    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        error();

    }


    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("Server is running...\n");


    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        error();
    }

    listen(sockfd, 5);

    printf("Server is listening...\n");


    conn = accept(sockfd, (struct sockaddr *)NULL, NULL);

    printf("Server is connected...\n");
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        while (1)
        {
            bzero(&recvbuff, sizeof(recvbuff));
            recv(conn, recvbuff, sizeof(recvbuff), 0);
            printf("\nCLIENT : %s\n", recvbuff);
            sleep(5);

        }
    }
    else
    {
        while (1)
        {
            bzero(&sendbuff, sizeof(sendbuff));
            printf("\nType message here: ");
            fgets(sendbuff, 1024, stdin);
            send(conn, sendbuff, strlen(sendbuff) + 1, 0);
            printf("\nMessage Sent!\n");
            sleep(5);

        }
    }


    close(sockfd);
    printf("Server is offline...\n");
    return 0;
}
