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
/** @file AES.h
 * @author chuwen
 * @date 2022-05-12
 */

#pragma once

#include "../Common.h"
#include "SHA3.h"

namespace dev
{

class AES
{
public:
    AES() = default;
    ~AES() = default;

public:
    bytes aesCBCEncrypt(bytesConstRef _plainData, bytesConstRef _key);
    bytes aesCBCDecrypt(bytesConstRef _cypherData, bytesConstRef _key);

    bytes uniformKey(bytesConstRef _readableKeyBytes);

private:
    SHA3 m_sha3;
};

}  // namespace dev