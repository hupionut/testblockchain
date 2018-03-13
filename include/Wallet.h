#include<string>

#ifndef WALLET_H
#define WALLET_H

#include "ecc.h"

class Wallet
{
    public:
        std::string publicKey;
        std::string privateKey;

        uint8_t p_publicKey[ECC_BYTES+1];
        uint8_t p_privateKey[ECC_BYTES];
        Wallet();
        virtual ~Wallet();
        void GenerateKeyPair();
        void printKeys();
    protected:

    private:
};

#endif // WALLET_H
