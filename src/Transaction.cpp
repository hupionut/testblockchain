#include<iostream>
#include<cstdint>
#include<string>
#include<cstring>
#include<algorithm>
#include<iterator>
#include<numeric>

#include "ecc.h"
#include "Transaction.h"
#inlcude "picosha2.h"


Transaction::Transaction()
{
    //ctor
}

Transaction::~Transaction()
{
    //dtor
}

Transaction::Transaction(uint8_t from[ECC_BYTES], uint8_t to[ECC_BYTES],float value,std::vector<TransactionInput> inputs)
{

    std::memcpy(this->sender,from,sizeof(uint8_t)*ECC_BYTES);
    std::memcpy(this->receiver,to,sizeof(uint8_t)*ECC_BYTES);
    this->value = value;
    std::copy(inputs.begin(),inputs.end(),std::back_inserter(this->inputs));




}


std::string Transaction::calculateHash()
{
    sequence++;  // increase the sequence to avoid 2 identical transactions having the same hash value

}
