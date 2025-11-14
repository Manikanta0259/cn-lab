//Starting Wire shark 
#include <stdio.h>
#include <stdlib.h>

int main() {
    // This command starts Wireshark. You can add options, e.g. "-i eth0" to capture on eth0.
    int ret = system("wireshark &"); // Use "wireshark" for Linux; "Wireshark.exe" for Windows.
    if (ret == -1) {
        perror("Failed to start Wireshark");
        return 1;
    }
    printf("Wireshark launched successfully.");
    return 0;
}
