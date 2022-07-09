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

namespace dev
{

class SHA3
{
public:
    SHA3() = default;
    ~SHA3() = default;

public:
    /// Calculate SHA3-256 hash of the given input and load it into the given output.
    /// @returns false if o_output.size() != 32.
    bool sha3(bytesConstRef _input, bytesRef o_output);

    /// Calculate SHA3-256 hash of the given input, returning as a 256-bit hash.
    inline bytes sha3(bytesConstRef _input)
    {
        bytes ret(32, 0);
        sha3(_input, ref(ret));
        return ret;
    }

    inline bytes sha3(std::string const& _input) { return sha3(bytesConstRef(_input)); }
};

}  // namespace dev