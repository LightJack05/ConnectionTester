#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

void alert_user() { printf("Connection attempt failed.\n"); }
void disconnect_alert() { printf("Connection retry count exceeded.\n"); }

int connection_loop() {
        int retry_count = 0;
        while (retry_count < 5) {
                int sockfd = socket(AF_INET, SOCK_STREAM, 0);
                struct sockaddr_in address = {
                    AF_INET, htons(80), {inet_addr("1.1.1.1")}};
                if (connect(sockfd, (struct sockaddr *)&address,
                            sizeof((address))) != 0) {
                        retry_count++;
                        alert_user();
                } else {
                        retry_count = 0;
                        printf("%s", "Connection successfull.\n");
                }
                close(sockfd);
                sleep(3);
        }
        if (retry_count > 4) {
                return 1;
        }
        return 0;
}

void print_help() {}

int main(int argc, char **argv) {

        if (connection_loop()) {
                disconnect_alert();
                return 1;
        } else {
                return 0;
        }
}
