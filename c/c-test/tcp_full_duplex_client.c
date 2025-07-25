
void error()
{
    perror("Socket Creation Failed");
    exit(EXIT_FAILURE);
}


int main()
{

    uint32_t
        sockfd;
    char sendbuff[1024],
        recvbuff[1024];


    struct sockaddr_in
        server_addr;




    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        error();
    }


    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("Client is running...\n");


    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Client is connected...\n");


    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        while (1)
        {
            bzero(&sendbuff, sizeof(sendbuff));
            printf("\nType message here: ");
            fgets(sendbuff, 1024, stdin);
            send(sockfd, sendbuff, strlen(sendbuff) + 1, 0);
            printf("\nMessage sent!\n");
            sleep(5);

        }
    }
    else
    {
        while (1)
        {
            bzero(&recvbuff, sizeof(recvbuff));
            recv(sockfd, recvbuff, sizeof(recvbuff), 0);
            printf("\nSERVER: %s\n", recvbuff);
            sleep(5);

        }
    }


    close(sockfd);
    printf("Client is offline...\n");
    return 0;
}
