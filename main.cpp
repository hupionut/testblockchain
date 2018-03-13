#include <iostream>
#include <string>
#include <vector>


#include "BlockChain.h"
#include "Wallet.h"

using namespace std;

int main()
{

    BlockChain blchain;
    Wallet myWallet;

    blchain.difficulty = 2;

    blchain.CreateGenisysBlock("THE GENISYS BLOCK YO!!!!");
    blchain.InsertBlock("another block son!");
    blchain.InsertBlock("and another one yo!");



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

    myWallet.printKeys();

    return 0;
}



