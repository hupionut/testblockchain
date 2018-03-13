#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <cstdint>


struct Block {
    std::string previousHash;
    std::string blockHash;
    std::string transactions;
    uint64_t nonce;
    time_t timestamp;
};


typedef Block Block;
#endif // BLOCK_H
