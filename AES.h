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
/** @file AES.h
 * @author Alex Leverington <nessence@gmail.com>
 * @date 2014
 *
 * AES
 * todo: use openssl
 */

#pragma once

#include "Common.h"
#include "CommonData.h"
#include "vector_ref.h"

namespace dev
{
bytes aesCBCEncrypt(bytesConstRef _plainData, bytesConstRef _key);
bytes aesCBCDecrypt(bytesConstRef _cypherData, bytesConstRef _key);
bytes readableKeyBytes(const std::string& _readableKey);
}  // namespace dev
