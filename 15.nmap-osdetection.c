#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define CMD_SIZE 256

void run_nmap_os_detection(const char *target_ip) {
    char command[CMD_SIZE];
    char buffer[BUFFER_SIZE];
    FILE *pipe;

    snprintf(command, sizeof(command), "sudo nmap -O %s", target_ip);

    pipe = popen(command, "r");
    if (!pipe) {
        perror("popen failed");
        return;
    }

    printf("Nmap OS Detection result for target %s:\n", target_ip);

    while (fgets(buffer, sizeof(buffer), pipe)) {
        if (strstr(buffer, "OS details") ||
            strstr(buffer, "OS detection performed") ||
            strstr(buffer, "Running:")) {
            
            printf("%s", buffer);
        }
    }

    pclose(pipe);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target_ip>\n", argv[0]);
        return 1;
    }

    run_nmap_os_detection(argv[1]);

    return 0;
}