/*
* Ten: Le Ba Cong
* MSSV: 17020022
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#define MAX_NAME_LENGTH 100
struct udphdr {
    unsigned short fileSize;
    unsigned char fileType;
    char fileName[MAX_NAME_LENGTH];
} data;

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

int main(int argc, char const *argv[]) {

    string fileName;
    cout << "Ten kich thuoc file: ";
    cin >> data.fileSize;
    cout <<"Ten kieu file: ";
    cin >> data.fileType;
    data.fileType = data.fileType - '0';
    cout << "Nhap ten file: ";
    cin >> data.fileName;

    string str = "{\"fileSize\": " + std::to_string(data.fileSize) + "," +
    "\"fileType\": " + std::to_string(data.fileType) + ',' +
    "\"fileType\": \"" + std::string(data.fileName) + "\"}";
    ofstream fs;
    fs.open("pkt_hdr_json.json");
    fs << str;
    fs.close();

    cout << "size bin file: " << filesize("pkt_hdr.bin") << endl << "size json file: " << filesize("pkt_hdr_json.json") << endl;
    return 0;
}