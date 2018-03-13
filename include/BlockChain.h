#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H


#include<iostream>
#include<string>
#include<vector>
#include<cstdint>

#include"Block.h"


class BlockChain
{
    public:

        uint64_t difficulty;

        BlockChain();
        virtual ~BlockChain();
        uint64_t NumberOfBlocks();
        void InsertBlock(std::string data);
        void CreateGenisysBlock(std::string genesysdata);
        bool IsChainValid();
        void ChangeSomeData();

        std::string GetBlocksJSON();
    protected:

    private:
        uint64_t numberOfBlocks;
        std::vector<Block> blockChain;

};

#endif // BLOCKCHAIN_H
