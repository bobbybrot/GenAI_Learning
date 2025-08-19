#include <stdio.h>
#include <stdint.h> // For uint32_t

/**
 * @brief Converts a 32-bit integer from host byte order to network byte order (Big-Endian).
 * @param host_long The 32-bit integer in the host machine's format.
 * @return The 32-bit integer in network byte order.
 */
uint32_t host_to_network_long(uint32_t host_long) {
    // HINT: Use bitwise shifts (>> and <<) and AND (&) to isolate and move each byte.
    // For example, to get the first byte (the '4D' in 0x1A2B3C4D), you can use (host_long & 0x000000FF).
    // To move it to the most significant position, you would then shift it left by 24 bits.
    // Repeat this logic for all four bytes.

    uint32_t network_long;

    // --- Your implementation goes here ---
    network_long = ( (host_long & 0xFFu) << 24 )    |
                ((host_long & 0xFF00u) << 8)     |
                ((host_long & 0xFF0000u) >> 8)   |
                ((host_long & 0xFF000000) >> 24);

    return network_long;
}

// Helper function to print the bytes of a 32-bit integer
void print_bytes(uint32_t n) {
    unsigned char *p = (unsigned char *)&n;
    // On a little-endian machine, this will print the bytes in reverse order of significance
    printf("Bytes in memory: %02X %02X %02X %02X\n", p[0], p[1], p[2], p[3]);
}

int main() {
    uint32_t my_value = 0x1A2B3C4D;

    printf("Original Value: 0x%X\n", my_value);
    printf("Host (Little-Endian) Machine Representation:\n");
    print_bytes(my_value);
    printf("--> If sent directly, a network server would incorrectly read this as 0x4D3C2B1A\n\n");

    // Convert to network byte order
    uint32_t network_value = host_to_network_long(my_value);

    printf("Network Value (Big-Endian): 0x%X\n", network_value);
    printf("Network Packet Representation:\n");
    print_bytes(network_value);
    printf("--> This is the correct byte order to send over the network.\n");

    return 0;
}
