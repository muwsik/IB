//#include <iostream>
//#include <fstream>
//#include "Block.h"
//#include "Encryptor.h"
//
//
//static vector<uint8_t> readAllBytes(string filename) {
//    ifstream ifs(filename, ios::binary | ios::ate);
//    ifstream::pos_type pos = ifs.tellg();
//
//    std::vector<uint8_t> result(pos);
//
//    ifs.seekg(0, ios::beg);
//    ifs.read(reinterpret_cast<char *>(&result[0]), pos);
//
//    return result;
//}
//
//static void writeAllBytes(vector<uint8_t> bytes, const string &fileName){
//    ofstream outfile(fileName, ios::out | ios::binary);
//    outfile.write(reinterpret_cast<const char *>(&bytes[0]), bytes.size());
//}
//
//int main() {
//    string fileName = "a.txt";
//    string fileNameEnc = "a_enc.txt";
//    string fileNameDec = "a_dec.txt";
//
//    vector<uint8_t> data = readAllBytes(fileName);
//    std::cout << "File contains: ";
//    for (auto c : data) {
//        std::cout << c;
//    }
//    std::cout << '\n';
//
//    uint32_t keyArr[8] = {0xFF5A52, 0x655F, 0x735A66, 0xFA76F5B, 0x65A52, 0x1A5F, 0x735A6F, 0xFA7DA};
//
//    Encryptor encryptor(Block(0x9F7865F5, 0xA714F5));
//
//    vector<uint8_t> encrypted = encryptor.encrypt(data, keyArr, true);
//    writeAllBytes(encrypted, fileNameEnc);
//  //  std::cout << "File encrypted: ";
//    /*
//    for (unsigned char i : encrypted) {
//        std::cout << (char) i;
//    }
//    std::cout << '\n';
//    */
//
//    vector<uint8_t> data2 = readAllBytes(fileNameEnc);
//    vector<uint8_t> decrypted = encryptor.encrypt(data2, keyArr, false);
//    writeAllBytes(decrypted, fileNameDec);
//   // std::cout << "File decrypted: ";
//    /*
//    for (unsigned char i : decrypted) {
//        std::cout << (char) i;
//    }
//    std::cout << '\n';
//    */
//
//
//    return 0;
//}
//
