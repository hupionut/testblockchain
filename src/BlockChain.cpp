#include <iostream>


#include "BlockChain.h"
#include "utils.h"
#include "sha512.h"

BlockChain::BlockChain()
{
    //ctor
}

BlockChain::~BlockChain()
{
    //dtor
}




void BlockChain::ChangeSomeData()
{
    blockChain.front().transactions = "HAHAH CHANGED!";
}

bool BlockChain::IsChainValid()
{

    bool blockChainValid = true;

    std::vector<Block>::const_iterator it;

    Block previousBlock;

    for (it = blockChain.begin(); it != blockChain.end(); it++)
    {

        if ((*it).blockHash != sha512(printDateTime((*it).timestamp) + (*it).transactions + std::to_string((*it).nonce) + (*it).previousHash))
        {
            std::cout << "Current Hash: " + (*it).blockHash + "!=" + sha512(printDateTime((*it).timestamp) + (*it).transactions  + std::to_string((*it).nonce) + (*it).previousHash) <<std::endl;
            blockChainValid = false;
        }

        if((*it).previousHash != "0") //not genisys block check if previous hash is good
        {
            if((*it).previousHash != sha512(printDateTime(previousBlock.timestamp) + previousBlock.transactions + std::to_string(previousBlock.nonce) + previousBlock.previousHash))
            {
                std::cout << "Previous Hash: " + (*it).previousHash + "!=" + sha512(printDateTime(previousBlock.timestamp) + previousBlock.transactions + std::to_string(previousBlock.nonce) + previousBlock.previousHash) <<std::endl;
                blockChainValid = false;
            }
        }

        previousBlock = (*it);

    }

    return blockChainValid;
}


uint64_t BlockChain::NumberOfBlocks()
{
    return blockChain.size();
}

void BlockChain::InsertBlock(std::string data)
{
    Block insertedBlock;

    std::string targetDifficultyString;
    std::string currentHash;
    time_t startTime;


    uint64_t i,numOfHashes;






    time(&insertedBlock.timestamp);
    insertedBlock.transactions = data;
    insertedBlock.previousHash = blockChain.back().blockHash;
    insertedBlock.nonce = 0;




    for(i = 0; i < difficulty; i++)
    {
        targetDifficultyString = targetDifficultyString + "0";
    }




    std::cout << "Attempting to mine inserted block with difficulty " + std::to_string(difficulty) + "..." <<std::endl;


    time(&startTime);
    numOfHashes =0;

    while(targetDifficultyString != currentHash.substr(0,difficulty) )
    {
        numOfHashes++;
        insertedBlock.nonce++;
        currentHash = sha512(printDateTime(insertedBlock.timestamp) + insertedBlock.transactions + std::to_string(insertedBlock.nonce) +insertedBlock.previousHash  );
        if(abs(difftime(startTime,time(NULL) )) > 1)
        {
            time(&startTime);
            std::cout << std::to_string(numOfHashes) + " H/s" <<std::endl;
            numOfHashes = 0;
        }
    }
    std::cout << currentHash << std::endl;
    std::cout << "Found with difficulty " << std::to_string(difficulty) << std::endl;
    insertedBlock.blockHash = sha512(printDateTime(insertedBlock.timestamp) + insertedBlock.transactions + std::to_string(insertedBlock.nonce) + insertedBlock.previousHash);

    blockChain.push_back(insertedBlock);


}
void BlockChain::CreateGenisysBlock(std::string genesysdata)
{


    Block genBlock;
    std::string targetDifficultyString;
    std::string currentHash;
    time_t startTime;


    uint64_t i,numOfHashes;






    for(i = 0; i < difficulty; i++)
    {


        targetDifficultyString = targetDifficultyString + "0";
    }




    time(&genBlock.timestamp);
    genBlock.transactions = genesysdata;
    genBlock.previousHash = "0";
    genBlock.nonce = 0;

    std::cout << "Attempting to mine genisys block with difficulty " + std::to_string(difficulty) + "..." <<std::endl;

    time(&startTime);
    numOfHashes =0;

    while(targetDifficultyString != currentHash.substr(0,difficulty) )
    {
        numOfHashes++;
        genBlock.nonce++;
        currentHash = sha512(printDateTime(genBlock.timestamp) + genBlock.transactions + std::to_string(genBlock.nonce) +genBlock.previousHash  );

        if(abs(difftime(startTime,time(NULL) )) > 1)
        {
            time(&startTime);
            std::cout << std::to_string(numOfHashes) + " H/s" <<std::endl;
            numOfHashes = 0;
        }


    }
    std::cout << currentHash << std::endl;
    std::cout << "Found with difficulty " << std::to_string(difficulty) << std::endl;



    genBlock.blockHash = sha512(printDateTime(genBlock.timestamp) + genBlock.transactions + std::to_string(genBlock.nonce)  + genBlock.previousHash );
    blockChain.push_back(genBlock);
}
std::string BlockChain::GetBlocksJSON()
{
    std::vector<Block>::const_iterator it;
    std::string jsonData;
    unsigned int counter =0;

    jsonData = "[\n";

    for (it = blockChain.begin(); it != blockChain.end(); it++)
    {
        counter++;
        jsonData = jsonData + "\t{\n";
        jsonData = jsonData + "\t\t\"timestamp\": " + "\"" + printDateTime((time_t)(*it).timestamp) + "\",\n";
        jsonData = jsonData + "\t\t\"transactions\": " + "\"" + (*it).transactions + "\",\n";
        jsonData = jsonData + "\t\t\"hash\": " + "\"" + (*it).blockHash + "\",\n";
        jsonData = jsonData + "\t\t\"nonce\": " + "\"" + std::to_string((*it).nonce) + "\",\n";
        jsonData = jsonData + "\t\t\"previousHash\": " + "\"" + (*it).previousHash + "\"\n";

        if (counter != blockChain.size())
        {

            jsonData = jsonData + "\t},\n";
        }
        else
        {
            jsonData = jsonData + "\t}\n";

        }
    }

    jsonData =  jsonData + "]";

    return jsonData;
}
