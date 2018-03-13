#include<iostream>
#include<string>

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ec.h>
#include <openssl/pem.h>

#define ECCTYPE "secp521r1"

#include "Wallet.h"
#include "utils.h"
#include "ecc.h"

Wallet::Wallet()
{
    //ctor
    GenerateKeyPair();
}

Wallet::~Wallet()
{
    //dtor
}

void Wallet::printKeys()
{
    std::cout << "public key:" + publicKey << std::endl;
    std::cout << "private key:" + privateKey << std::endl;
}

void Wallet::GenerateKeyPair()
{


    ecc_make_key(p_publicKey,p_privateKey);

    publicKey = hexStr(p_publicKey,ECC_BYTES+1);
    privateKey = hexStr(p_privateKey,ECC_BYTES);



}
