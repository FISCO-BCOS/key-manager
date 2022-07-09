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
/** @file GmAES.h
 * @author chuwen
 * @date 2022-05-12
 */

#pragma once

#include "../Crypto.h"
#include "GmAES.h"

namespace dev
{

class GmCrypto : public Crypto
{
    bytes aesCBCEncrypt(bytesConstRef _plainData, bytesConstRef _key) override
    {
        return m_gmAES.aesCBCEncrypt(_plainData, _key);
    }

    bytes aesCBCDecrypt(bytesConstRef _cypherData, bytesConstRef _key) override
    {
        return m_gmAES.aesCBCDecrypt(_cypherData, _key);
    }

    bytes uniformKey(bytesConstRef _readableKeyBytes) override
    {
        return m_gmAES.uniformKey(_readableKeyBytes);
    }

private:
    GmAES m_gmAES;
};

}  // namespace dev