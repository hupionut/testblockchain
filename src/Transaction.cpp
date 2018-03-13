#include<iostream>
#include<cstdint>
#include<string>
#include<cstring>
#include<algorithm>
#include<iterator>
#include<numeric>

#include "ecc.h"
#include "Transaction.h"
#include "picosha2.h"
#include "utils.h"


Transaction::Transaction()
{
    //ctor
}

Transaction::~Transaction()
{
    //dtor
}

Transaction::Transaction(uint8_t from[ECC_BYTES+1], uint8_t to[ECC_BYTES+1],float value,std::vector<TransactionInput> inputs)
{

    std::memcpy(this->sender,from,sizeof(uint8_t)*(ECC_BYTES+1));
    std::memcpy(this->receiver,to,sizeof(uint8_t)*(ECC_BYTES+1));
    this->value = value;
    std::copy(inputs.begin(),inputs.end(),std::back_inserter(this->inputs));




}


Transaction::Transaction(uint8_t from[ECC_BYTES+1], uint8_t to[ECC_BYTES+1],float value)
{

    uint8_t i;
    std::vector<uint8_t> transactionVector;

    std::memcpy(this->sender,from,sizeof(uint8_t)*(ECC_BYTES+1));
    std::memcpy(this->receiver,to,sizeof(uint8_t)*(ECC_BYTES+1));
    this->value = value;

    this->senderString = hexStr(this->sender,ECC_BYTES+1);
    this->receiverString = hexStr(this->receiver,ECC_BYTES+1);



    sequence++;
    transactionVector = HexToBytes(picosha2::hash256_hex_string(senderString+receiverString+std::to_string(value) + std::to_string(sequence)));


    for (i = 0; i < transactionVector.size();i++)
    {
        transactionBytes[i] = transactionVector[i];
    }






}


std::string Transaction::calculateHash()
{
    std::string hashThis;
    sequence++;  // increase the sequence to avoid 2 identical transactions having the same hash value
    return picosha2::hash256_hex_string(hexStr(sender,ECC_BYTES) + hexStr(receiver,ECC_BYTES) + std::to_string(value));


}







void Transaction::generateSignature(uint8_t privateKey[ECC_BYTES])
{
    applyECDSASig(privateKey,this->senderString+this->receiverString+std::to_string(this->value)+std::to_string(sequence));

}


bool Transaction::verifySignature()
{
    return verifyECDSASig(sender,"test",this->signature);
}

