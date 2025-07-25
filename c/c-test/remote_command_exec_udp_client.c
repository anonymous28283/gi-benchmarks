void error()
{
    perror("Socket Creation Failed");
    exit(EXIT_FAILURE);
}


int main()
{

    uint32_t
        sockfd;
    char send_msg[1024],
        recv_msg[1024];


    struct sockaddr_in
        server_addr;


    socklen_t serverLength = sizeof(server_addr);


    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        error();
    }


    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("Client is running...\n");


    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Client is Connected Successfully...\n");


    while (1)
    {
        printf("\nEnter Command To Be Executed Remotely: \n");
        fgets(send_msg, sizeof(send_msg), stdin);
        sendto(sockfd, send_msg, sizeof(send_msg), 0,
               (struct sockaddr *)&server_addr, serverLength);
        recvfrom(sockfd, recv_msg, sizeof(recv_msg), 0,
                 (struct sockaddr *)&server_addr, &serverLength);
        printf("Server Reply: %s\n", recv_msg);
    }


    close(sockfd);
    printf("Client is offline...\n");
    return 0;
}
