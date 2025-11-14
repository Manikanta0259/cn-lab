//(C) Viewing Captured Traffic 
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>

void packet_handler(u_char *user, const struct pcap_pkthdr *header, constu_char*packet) {
    struct ether_header *eth_header;
    eth_header = (struct ether_header *) packet;

    printf("Packet captured at %ld.%06ld seconds", header->ts.tv_sec, header->ts.tv_usec);
    printf("Packet length: %d bytes", header->len);

    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) {
        struct ip *ip_header = (struct ip *)(packet + sizeof(struct ether_header));
        printf("Source IP: %s", inet_ntoa(ip_header->ip_src));
        printf("Destination IP: %s", inet_ntoa(ip_header->ip_dst));
        printf("Protocol: %d", ip_header->ip_p);
    } else if (ntohs(eth_header->ether_type) == ETHERTYPE_ARP) {
        printf("ARP packet detected.");
    } else {
        printf("Non-IP packet: 0x%04x", ntohs(eth_header->ether_type));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pcap file>", argv[0]);
        return EXIT_FAILURE;
    }

    char errbuff[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_offline(argv[1], errbuff);
    if (!handle) {
        fprintf(stderr, "Error opening pcap file: %s", errbuff);
        return EXIT_FAILURE;
    }

    printf("Reading packets from %s...", argv[1]);
    if (pcap_loop(handle, 0, packet_handler, NULL) < 0) {
        fprintf(stderr, "Error reading packets: %s", pcap_geterr(handle));
        pcap_close(handle);
        return EXIT_FAILURE;
    }

    pcap_close(handle);
    printf("
Capture file processing complete.");
    return EXIT_SUCCESS;
}
