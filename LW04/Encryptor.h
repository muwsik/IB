////
//// Created by Denis Rodionov on 4/26/18.
////
//
//typedef unsigned int uint;
//
//#ifndef GOST_ENCRYPT_BLOCK_ENCRYPTOR_H
//#define GOST_ENCRYPT_BLOCK_ENCRYPTOR_H
//
//#include <vector>
//#include "Block.h"
//
//#define BLOCK_SIZE 64
//#define KEY_SIZE 256
//#define STEPS 128
//
//using namespace std;
//
//class Encryptor {
//    const Block syncData;
//    const uint32_t table[8][16] = {
//            {0x4, 0xa, 0x9, 0x2, 0xd, 0x8, 0x0, 0xe, 0x6, 0xb, 0x1, 0xc, 0x7, 0xf, 0x5, 0x3},
//            {0xe, 0xb, 0x4, 0xc, 0x6, 0xd, 0xf, 0xa, 0x2, 0x3, 0x8, 0x1, 0x0, 0x7, 0x5, 0x9},
//            {0x5, 0x8, 0x1, 0xd, 0xa, 0x3, 0x4, 0x2, 0xe, 0xf, 0xc, 0x7, 0x6, 0x0, 0x9, 0xb},
//            {0x7, 0xd, 0xa, 0x1, 0x0, 0x8, 0x9, 0xf, 0xe, 0x4, 0x6, 0xc, 0xb, 0x2, 0x5, 0x3},
//            {0x6, 0xc, 0x7, 0x1, 0x5, 0xf, 0xd, 0x8, 0x4, 0xa, 0x9, 0xe, 0x0, 0x3, 0xb, 0x2},
//            {0x4, 0xb, 0xa, 0x0, 0x7, 0x2, 0x1, 0xd, 0x3, 0x6, 0x8, 0x5, 0x9, 0xc, 0xf, 0xe},
//            {0xd, 0xb, 0x4, 0x1, 0x3, 0xf, 0x5, 0x9, 0x0, 0xa, 0xe, 0x7, 0x6, 0x8, 0x2, 0xc},
//            {0x1, 0xf, 0xd, 0x0, 0x5, 0x7, 0xa, 0x4, 0x9, 0x2, 0x3, 0xe, 0x6, 0xb, 0x8, 0xc},
//    };
//public:
//    Encryptor(const Block &syncData) : syncData(syncData) {
//
//    }
//
//    vector<uint8_t> encrypt(vector<uint8_t> data, uint32_t *key, bool encrypt) {
//        Block prevEncBlock = syncData;
//        uint8_t unusedBytesInResultData = 0;
//        if (!encrypt) {
//            unusedBytesInResultData = data[0];
//            data.erase(data.begin());
//        }
//        vector<Block> blocks = createBlocks(data);
//        vector<Block> resultBlocks;
//
//        if (encrypt) {
//            unusedBytesInResultData = blocks.size() * 8 - data.size();
//            for (const auto &block : blocks) {
//                Block encBlock = block ^prevEncBlock;
//                encBlock = encrypt32Z(encBlock, key, true);
//                prevEncBlock = encBlock;
//                resultBlocks.push_back(encBlock);
//            }
//        } else {
//            for (const auto &block : blocks) {
//                Block decBlock = encrypt32Z(block, key, false);
//                decBlock = prevEncBlock ^ decBlock;
//                prevEncBlock = block;
//                resultBlocks.push_back(decBlock);
//            }
//        }
//
//        vector<uint8_t> resultArray = createArray(resultBlocks);
//        if (encrypt) {
//            resultArray.insert(resultArray.begin(), unusedBytesInResultData);
//        } else {
//            if (unusedBytesInResultData != 0) {
//                resultArray.erase(resultArray.end() - unusedBytesInResultData, resultArray.end());
//            }
//        }
//        return resultArray;
//    }
//
//private:
//    Block encrypt32Z(const Block &block, uint32_t *key, bool encrypt) {
//        int keyCount = KEY_SIZE / 8;
//        Block resultBlock = block;
//        int keyNum = 0;
//
//        if (encrypt) {
//            for (int i = 1; i <= STEPS - keyCount; i++) {
//                if (keyNum == keyCount) {
//                    keyNum = 0;
//                }
//                resultBlock = step(resultBlock, key[keyNum]);
//                keyNum++;
//            }
//
//            keyNum = keyCount - 1;
//            for (int i = 1; i <= keyCount; i++) {
//                resultBlock = step(resultBlock, key[keyNum]);
//                keyNum -= 1;
//            }
//        } else {
//            keyNum = 0;
//            for (int i = 1; i <= keyCount; i++) {
//                resultBlock = step(resultBlock, key[keyNum]);
//                keyNum++;
//            }
//
//            keyNum = keyCount - 1;
//            for (int i = 1; i <= STEPS - keyCount; i++) {
//                if (keyNum == -1) {
//                    keyNum = keyCount - 1;
//                }
//                resultBlock = step(resultBlock, key[keyNum]);
//                keyNum -= 1;
//            }
//        }
//        resultBlock.swap();
//
//        return resultBlock;
//    }
//
//    uint32_t *getArrayOfBits(uint32_t val) {
//        uint32_t *result = new uint32_t[8]();
//        for (uint32_t i = 0; i < 8; i++) {
//            uint32_t mask = 0xF;
//            mask = mask << 4 * i;
//            result[i] = (val & mask);
//            result[i] = result[i] >> 4 * i;
//        }
//        return result;
//    }
//
//    uint32_t getUint32FromBitsArray(const uint32_t *val) {
//        uint32_t bits = 0;
//        uint32_t result = 0;
//        for (uint32_t i = 0; i < 8; i++) {
//            bits = val[i];
//            bits = bits << 4 * i;
//            result = result | bits;
//        }
//        return result;
//    }
//
//    uint32_t rotateBits(uint32_t val, uint32_t d) {
//        return (val << d) | (val >> (32 - d));
//    }
//
//    Block step(const Block &block, uint32_t keyPart) {
//        uint32_t S = 0;
//        uint32_t N1 = block.getPartA();
//        uint32_t N2 = block.getPartB();
//        S = N1 + keyPart;
//        uint32_t *bitsArray = getArrayOfBits(S);
//        for (uint i = 0; i < 8; i++) {
//            bitsArray[i] = table[i][bitsArray[i]];
//        }
//
//        S = getUint32FromBitsArray(bitsArray);
//
//        delete[] bitsArray;
//
//        S = rotateBits(S, 11);
//        S ^= N2;
//        N2 = N1;
//        N1 = S;
//        return Block(N1, N2);
//    }
//
//    vector<Block> createBlocks(const vector<uint8_t> &data) {
//        vector<Block> blocks;
//        for (unsigned long i = 0; i < data.size(); i += 8) 
//		{
//            unsigned long to = i + 7;
//            if (to >= data.size()) {
//                to = data.size() - 1;
//            }
//            uint8_t *dataPart = new uint8_t[8]();
//            memcpy(dataPart, data.data() + i, to - i + 1);
//            Block block(dataPart);
//            delete[] dataPart;
//            blocks.push_back(block);
//        }
//        return blocks;
//    }
//
//    vector<uint8_t> createArray(const vector<Block> &blocks) {
//        vector<uint8_t> result;// = new uint8_t[blocks.size()*8];
//        for (int i = 0; i < blocks.size(); i++) {
//            uint8_t *data = blocks[i].getData();
//            result.insert(result.begin() + (i * 8), data, data + 8);
//            //memcpy(result+(i*8), data, 8);
//            delete[] data;
//        }
//        return result;
//    }
//};
//
//
//#endif //GOST_ENCRYPT_BLOCK_ENCRYPTOR_H
