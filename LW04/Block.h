////
//// Created by Denis Rodionov on 4/26/18.
////
//
//#ifndef GOST_ENCRYPT_BLOCK_BLOCK_H
//#define GOST_ENCRYPT_BLOCK_BLOCK_H
//
//
//#include <cstdint>
//#include <cstring>
//#include <iostream>
//
//#define BYTES_COUNT 8
//
//class Block {
//    uint8_t *data = nullptr;
//
//public:
//    Block() {
//        initWithParts(0, 0);
//    }
//
//    explicit Block(uint8_t *data) {
//        this->data = new uint8_t[BYTES_COUNT]();
//        if (data == nullptr) {
//            std::cout << "Error!!!\n";
//            initWithParts(0, 0);
//        }
//        memcpy(this->data, data, BYTES_COUNT);
//    }
//
//    Block(uint32_t partA, uint32_t partB) {
//        initWithParts(partA, partB);
//    }
//
//    Block(const Block &block) {
//        this->data = new uint8_t[BYTES_COUNT]();
//        memcpy(this->data, block.data, BYTES_COUNT);
//    }
//
//    virtual ~Block() {
//        if (data != nullptr) {
//            delete[] data;
//        }
//    }
//
//    void print() {
//        if (data != nullptr) {
//            std::cout << "partA: " << getPartA() << " partB: " << getPartB() << '\n';
//        }
//    }
//
//    uint32_t getPartA() const {
//        uint32_t *partA = (uint32_t *) data;
//        return *partA;
//    }
//
//    uint32_t getPartB() const {
//        uint32_t *partB = (uint32_t *) (data + 4);
//        return *partB;
//    }
//
//    uint8_t *getData() const {
//        uint8_t *result = new uint8_t[BYTES_COUNT];
//        memcpy(result, this->data, BYTES_COUNT);
//        return result;
//    }
//
//    void swap() {
//        uint32_t partA = getPartA();
//        uint32_t partB = getPartB();
//        memcpy(data, &partB, sizeof(partB));
//        memcpy(data + 4, &partA, sizeof(partA));
//    }
//
//    friend Block operator^(const Block &leftBlock, const Block &rightBlock) {
//        Block result(0, 0);
//        for (uint8_t i = 0; i < BYTES_COUNT; i++) {
//            result.data[i] = leftBlock.data[i] ^ rightBlock.data[i];
//        }
//        return result;
//    }
//
//    Block &operator=(const Block &block) {
//        if (this->data != nullptr) {
//            delete[] this->data;
//        }
//
//        this->data = new uint8_t[BYTES_COUNT]();
//        memcpy(this->data, block.data, BYTES_COUNT);
//        return *this;
//    }
//
//private:
//    void initWithParts(uint32_t partA, uint32_t partB) {
//        data = new uint8_t[BYTES_COUNT]();
//        memcpy(data, &partA, sizeof(partA));
//        memcpy(data + 4, &partB, sizeof(partB));
//    }
//};
//
//
//#endif //GOST_ENCRYPT_BLOCK_BLOCK_H
