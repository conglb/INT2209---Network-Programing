/*
* Ho va Ten: Le Ba Cong
* MSSV: 17020022
*/

#include <iostream>
#include <cstring>

using namespace std;

#define MAX_NAME_LENGTH 100

struct udphdr {
    unsigned short fileSize;
    unsigned char fileType;
    unsigned char fileNameLength;
    char fileName[MAX_NAME_LENGTH];
} data;

int main(int argc, char const *argv[]) {
    FILE * fd = fopen("pkt_hdr.bin", "rb");
    fread(&data, sizeof(udphdr), 1, fd);
    fclose(fd);
    cout << "Kich thuoc file: " << data.fileSize << endl;
    cout << "Kieu file: " << int(data.fileType) << endl;
    cout << "Do dai ten file: " << int(data.fileNameLength) << endl;
    cout << "Ten file: " << data.fileName;
    return 0;
}