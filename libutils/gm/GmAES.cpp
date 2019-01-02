/*
 * @CopyRight:
 * FISCO-BCOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FISCO-BCOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FISCO-BCOS.  If not, see <http://www.gnu.org/licenses/>
 * (c) 2016-2018 fisco-dev contributors.
 */
/** @file GmAES.cpp
 * @author Asherli
 * @date 2018
 */

#include "../Crypto.h"
#include "sm4/sm4.h"
#include <stdlib.h>
#include <string.h>

using namespace dev;
using namespace std;


bytes dev::aesCBCEncrypt(bytesConstRef _plainData, bytesConstRef _key)
{
    bytesConstRef ivData = _key.cropped(0, 16);
    int padding = _plainData.size() % 16;
    int nSize = 16 - padding;
    int inDataVLen = _plainData.size() + nSize;
    bytes inDataV(inDataVLen);
    memcpy(inDataV.data(), (unsigned char*)_plainData.data(), _plainData.size());
    memset(inDataV.data() + _plainData.size(), nSize, nSize);

    bytes enData(inDataVLen);
    SM4::getInstance().setKey((unsigned char*)_key.data(), _key.size());
    SM4::getInstance().cbcEncrypt(
        inDataV.data(), enData.data(), inDataVLen, (unsigned char*)ivData.data(), 1);
    // LOG(DEBUG)<<"ivData:"<<ascii2hex((const char*)ivData.data(),ivData.size());
    return enData;
}
bytes dev::aesCBCDecrypt(bytesConstRef _cypherData, bytesConstRef _key)
{
    bytesConstRef ivData = _key.cropped(0, 16);
    bytes deData(_cypherData.size());
    SM4::getInstance().setKey((unsigned char*)_key.data(), _key.size());
    SM4::getInstance().cbcEncrypt((unsigned char*)_cypherData.data(), deData.data(),
        _cypherData.size(), (unsigned char*)ivData.data(), 0);
    int padding = deData.data()[_cypherData.size() - 1];
    int deLen = _cypherData.size() - padding;
    deData.resize(deLen);
    return deData;
}

bytes dev::uniformKey(bytesConstRef _readableKeyBytes)
{
    // uniform/compress key to a fixed size bytes of size 128
    bytes oneTurn = sha3(_readableKeyBytes);
    return oneTurn + oneTurn + oneTurn + oneTurn;  // 4 * 32 = 128 bits
}