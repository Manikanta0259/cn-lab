//(D) . Analysis and Statistics & Filters
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <string.h>

int tcp_count = 0, udp_count = 0, icmp_count = 0, other_count = 0, total_count = 0;

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    struct ip *ip_header = (struct ip *)(packet + 14); // Assume Ethernet header is 14 bytes
    ++total_count;
    switch(ip_header->ip_p) {
        case IPPROTO_TCP:
            ++tcp_count;
            break;
        case IPPROTO_UDP:
            ++udp_count;
            break;
        case IPPROTO_ICMP:
            ++icmp_count;
            break;
        default:
            ++other_count;
    }
}

int main(int argc, char **argv) {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct bpf_program fp;
    char filter_exp[] = "ip"; // filter: only IP packets
    bpf_u_int32 net = 0, mask = 0;
    char *dev;

    if (argc == 2) {
        dev = argv[1];
    } else {
        dev = pcap_lookupdev(errbuf);
        if (dev == NULL) {
            fprintf(stderr, "Couldn't find default device: %s", errbuf);
            return 1;
        }
    }

    if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
        fprintf(stderr, "Couldn't get netmask for device %s: %s", dev, errbuf);
        net = 0;
        mask = 0;
    }

    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s", dev, errbuf);
        return 2;
    }

    // Compile and set the filter
    if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
        fprintf(stderr, "Bad filter - %s", pcap_geterr(handle));
        return 2;
    }
    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Error setting filter - %s", pcap_geterr(handle));
        return 2;
    }

    printf("Capturing packets on device: %s", dev);
    pcap_loop(handle, 100, packet_handler, NULL); // capture 100 packets

    printf("Capture Statistics:");
    printf("Total Packets: %d", total_count);
    printf("TCP Packets: %d", tcp_count);
    printf("UDP Packets: %d", udp_count);
    printf("ICMP Packets: %d", icmp_count);
    printf("Other IP Packets: %d", other_count);

    pcap_freecode(&fp);
    pcap_close(handle);

    return 0;
}
