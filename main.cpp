#include <iostream>
#include <string>
#include <vector>


#include "BlockChain.h"
#include "Wallet.h"
#include "Transaction.h"
#include "ecc.h"
#include "picosha2.h"
#include "utils.h"

using namespace std;

int main()
{

    BlockChain blchain;
    Wallet WalletA;
    Wallet WalletB;

    blchain.difficulty = 2;

    blchain.CreateGenisysBlock("THE GENISYS BLOCK YO!!!!");
    blchain.InsertBlock("another block son!");
    blchain.InsertBlock("and another one yo!");


    uint8_t pubKey[ECC_BYTES+1],priKey[ECC_BYTES],signature[ECC_BYTES*2],message[ECC_BYTES],i;
    std::vector<uint8_t> messageVector;

    ecc_make_key(pubKey,priKey);


    cout << blchain.GetBlocksJSON() << endl;

    //blchain.ChangeSomeData();


    if (blchain.IsChainValid())
    {
        cout << "BlockChain is Valid!!\n";
    }
    else
    {
        cout << "Blockchain is NOT VALID!!!!\n";
    }

    WalletA.printKeys();

    WalletB.printKeys();

    Transaction transaction(WalletA.p_publicKey,WalletB.p_publicKey,5);

    transaction.generateSignature(WalletA.p_privateKey);

   cout << "Is signature verified: " << std::to_string(transaction.verifySignature()) << endl;




    return 0;
}



