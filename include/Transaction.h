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
        uint8_t sender[ECC_BYTES+1];//sender public key
        uint8_t receiver[ECC_BYTES+1];
        std::string senderString;
        std::string receiverString;
        float value;
        uint8_t signature[ECC_BYTES*2];
        std::string signatureString;
        uint8_t transactionBytes[ECC_BYTES];




        std::vector<TransactionInput> inputs;
        std::vector<TransactionOutput> outputs;





        Transaction();
        Transaction(uint8_t from[ECC_BYTES+1], uint8_t to[ECC_BYTES+1],float value,std::vector<TransactionInput> inputs);
        Transaction(uint8_t from[ECC_BYTES+1], uint8_t to[ECC_BYTES+1],float value);
        virtual ~Transaction();

        std::string calculateHash();


        void generateSignature(uint8_t privateKey[ECC_BYTES]);
        bool verifySignature();



    protected:

    private:
    int sequence = 0;

};

#endif // TRANSACTION_H
