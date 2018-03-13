#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include<iostream>
#include<string>
#include<vector>
#include<cstdint>

#include "ecc.h"

std::string printDateTime(time_t myTime);

constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

std::string hexStr(uint8_t *data, int len);
std::vector<uint8_t>HexToBytes(const std::string& hex);
std::string applyECDSASig(uint8_t privateKey[ECC_BYTES],std::string input);
bool verifyECDSASig(uint8_t publicKey[ECC_BYTES+1],std::string data, uint8_t signature[ECC_BYTES*2]);

#endif // UTILS_H_INCLUDED
