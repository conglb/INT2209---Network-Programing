/*
* Ten: Le Ba Cong
* MSSV: 17020022
*

*/



#include <iostream>
#include <cstring>
#include <jsoncpp/json/json.h>
#include <jsoncpp.json/reading.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>

using namespace std;

#define MAX_NAME_LENGTH 100
struct udphdr {
    unsigned short fileSize;
    unsigned char fileType;
    string fileName;
}data;

udphdr string_to_obj(strings) {
    struct udphdr out;
    Json::Value root;
    Json::Reader reader;
    bool ok = reader.parse( s.c_str(), root );

    if (!ok ) {
        std::cout <<"Lose";
        return out;
    }
    out.fileName = root.get("fileName", "null").asString();
    out.fileSize = root.get("fileSize", 0).asInt();
    out.fileType = root.get("fileType", 0).asInt();
    return out;
}

int main() {
    ifstream f("pkt_hdr_json.json");
    string str((istreambuf_iterator<char>(f))), istreambuf_iterator<char>());
    struct udphdr data = string_to_obj(str);
    cout << "File name: " << data.fileName << endl;
    return 0;
}