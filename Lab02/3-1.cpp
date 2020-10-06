#include <stdio.h>
#include <iostream>

#define MAX_NAME_LENGTH 100
using namespace std;
struct udphdr {
    unsigned short fileSize;
    unsigned char fileType;
    unsigned char fileNameLength;
    char fileName[MAX_NAME_LENGTH];
} packet;

int main() {
    setbuf(stdout, NULL);
    printf("File size (bytes): ");
    scanf("%hu", &packet.fileSize);
    printf("File type: ");
    scanf("%c \n", &packet.fileType);
    printf("File name: ");
    scanf("%c", &packet.fileNameLength);

    FILE *fd;
    fd = fopen("pkt_hdr.bin", "rb");

    if (packet.fileType == 0x01) {
        fwrite(&packet, sizeof(packet),1,fd);
        //fwrite(&packet.fileType, sizeof(packet.fileType),1,fd);
        //fwrite(&packet.fileNameLength, sizeof(packet.fileNameLength),1,fd);
        //fwrite(&packet.fileName, sizeof(packet.fileName),1,fd);
    } else {

    }
    fclose(fd);
    return 0;
}
