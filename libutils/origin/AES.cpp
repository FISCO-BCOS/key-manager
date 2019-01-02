/*
 This file is part of cpp-ethereum.

 cpp-ethereum is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 cpp-ethereum is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
 */
/** @file AES.cpp
 * @author Alex Leverington <nessence@gmail.com>
 * @date 2014
 */

#include "../Crypto.h"
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/sha.h>
#include <stdlib.h>
#include <string>


using namespace std;
using namespace dev;
using namespace CryptoPP;

char* ascii2hex(const char* chs, int len)
{
    char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    char* ascii = (char*)calloc(len * 3 + 1, sizeof(char));  // calloc ascii

    int i = 0;
    while (i < len)
    {
        int b = chs[i] & 0x000000ff;
        ascii[i * 2] = hex[b / 16];
        ascii[i * 2 + 1] = hex[b % 16];
        ++i;
    }
    return ascii;
}


bytes dev::aesCBCEncrypt(bytesConstRef _plainData, bytesConstRef _key)
{
    bytesConstRef ivData = _key.cropped(0, 16);
    string cipherData;
    CryptoPP::AES::Encryption aesEncryption(_key.data(), _key.size());
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, ivData.data());
    CryptoPP::StreamTransformationFilter stfEncryptor(
        cbcEncryption, new CryptoPP::StringSink(cipherData));
    stfEncryptor.Put(_plainData.data(), _plainData.size());
    stfEncryptor.MessageEnd();
    return asBytes(cipherData);
}

bytes dev::aesCBCDecrypt(bytesConstRef _cypherData, bytesConstRef _key)
{
    bytes ivData = _key.cropped(0, 16).toBytes();
    // bytesConstRef ivData = _key.cropped(0, 16);
    // LOG(DEBUG)<<"AES DE TYPE....................";
    string decryptedData;
    CryptoPP::AES::Decryption aesDecryption(_key.data(), _key.size());
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, ref(ivData).data());
    CryptoPP::StreamTransformationFilter stfDecryptor(
        cbcDecryption, new CryptoPP::StringSink(decryptedData));
    // stfDecryptor.Put( reinterpret_cast<const unsigned char*>( cipherData.c_str() ),cipherLen);
    stfDecryptor.Put(_cypherData.data(), _cypherData.size());
    stfDecryptor.MessageEnd();
    return asBytes(decryptedData);
}

bytes dev::uniformKey(bytesConstRef _readableKeyBytes)
{
    // uniform/compress key to a fixed size bytes of size 32
    return sha3(_readableKeyBytes);
}
