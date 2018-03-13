#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include <vector>


#include "ecc.h"
#include "TransactionInput.h"
#include "TransactionOutput.h"

class Transaction
{
    public:
        std::string transactionId;
        uint8_t sender[ECC_BYTES];//sender public key
        uint8_t receiver[ECC_BYTES];
        std::string senderString;
        std::string receiverString;
        float value;
        uint8_t *signature;



        std::vector<TransactionInput> inputs;
        std::vector<TransactionOutput> outputs;





        Transaction();
        Transaction(uint8_t from[ECC_BYTES], uint8_t to[ECC_BYTES],float value,std::vector<TransactionInput> inputs);
        virtual ~Transaction();

        std::string calculateHash();


    protected:

    private:
    int sequence = 0;

};

#endif // TRANSACTION_H
