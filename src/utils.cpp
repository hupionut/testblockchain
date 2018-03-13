
#include <iostream>
#include <string>
#include <time.h>


#include "utils.h"
#include "ecc.h"
#include "picosha2.h"


std::string printDateTime(time_t myTime) {
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&myTime);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}


std::string hexStr(uint8_t *data, int len)
{
  std::string s(len * 2, ' ');
  for (int i = 0; i < len; ++i) {
    s[2 * i]     = hexmap[(data[i] & 0xF0) >> 4];
    s[2 * i + 1] = hexmap[data[i] & 0x0F];
  }
  return s;
}

std::vector<uint8_t> HexToBytes(const std::string& hex) {
  std::vector<uint8_t> bytes;

  for (unsigned int i = 0; i < hex.length(); i += 2) {
    std::string byteString = hex.substr(i, 2);
    uint8_t byte = (uint8_t) strtol(byteString.c_str(), NULL, 16);
    bytes.push_back(byte);
  }

  return bytes;
}

std::string applyECDSASig(uint8_t privateKey[ECC_BYTES],std::string input) //requires input to be hashed
{

    std::vector<uint8_t> inputVector;

    std::string signatureString;
    uint8_t inputBytes[ECC_BYTES],signature[ECC_BYTES*2],i;

    inputVector = HexToBytes(picosha2::hash256_hex_string(input));

    for(i=0; i< inputVector.size();i++)
    {
        inputBytes[i] = inputVector[i];
    }

    ecdsa_sign(privateKey,inputBytes, signature);
    signatureString = hexStr(signature,ECC_BYTES*2);


    return signatureString;


}


bool verifyECDSASig(uint8_t publicKey[ECC_BYTES+1],std::string data, uint8_t signature[ECC_BYTES*2])  //requires that data is a hash
{

    std::vector<uint8_t> dataVector;
    uint8_t dataBytes[ECC_BYTES],i;



    dataVector = HexToBytes(picosha2::hash256_hex_string(data));

    for(i = 0; i < dataVector.size();i++)
    {
        dataBytes[i] = dataVector[i];
    }


    bool signatureVerifiedGood = false;


    if (ecdsa_verify(publicKey,dataBytes,signature) == 1)
    {
        signatureVerifiedGood = true;
    }
    //signatureString = hexStr(this->signature,ECC_BYTES*2);


    return signatureVerifiedGood;
}




