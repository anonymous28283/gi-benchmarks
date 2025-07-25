
void error()
{
    perror("Socket Creation Failed");
    exit(EXIT_FAILURE);
}


int main()
{

    uint32_t
        sockfd;
    struct sockaddr_in
        server_addr;


    char serverResponse[10000],
        clientResponse[10000];



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


    while (1)
    {
        bzero(&serverResponse, sizeof(serverResponse));
        bzero(&clientResponse, sizeof(clientResponse));


        recv(sockfd, serverResponse, sizeof(serverResponse), 0);
        printf("\nServer message: %s \n", serverResponse);


        printf("\nEnter message here: ");
        fgets(clientResponse, 10000, stdin);
        send(sockfd, clientResponse, strlen(clientResponse) + 1, 0);
    }


    close(sockfd);
    printf("Client is offline...\n");
    return 0;
}
