//i. Packet Capture Using Wire shark 

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>

void packet_handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet) {
    printf("Packet captured. Length: %d", header->len);
    // For Wireshark analysis, you may write packets to a pcap file from here.
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    char *dev;

    // Find a default device to capture on
    dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        fprintf(stderr, "Couldn't find device: %s", errbuf);
        return 1;
    }
    printf("Capturing on device: %s", dev);

    // Open device for live capture
    handle = pcap_open_live(dev, 65536, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device: %s", errbuf);
        return 2;
    }

    // Capture packets with callback
    pcap_loop(handle, 10, packet_handler, NULL); // Capture 10 packets

    pcap_close(handle);
    return 0;
}
