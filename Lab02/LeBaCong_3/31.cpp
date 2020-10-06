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

int main(int argc, char const * argv[]) {
    struct udphdr data;
    char binType;
    string filename;
    cout<< "Nhap file size: ";
    cin >> data.fileSize;
    cout << "Nhap kieu file: ";
    cin >> data.fileType;
    data.fileType = data.fileType -'0';
    cout <<"Nhap ten file: ";
    cin >> data.fileName;
    data.fileNameLength = strlen(data.fileName);

    FILE* fd = fopen("pkt_hdr.bin", "wb");

    if (fd == NULL) {
        cout << "Error";
        exit(1);
    }

    fwrite(&data, sizeof(udphdr), 1, fd);
    fclose(fd);
    return 0;
}