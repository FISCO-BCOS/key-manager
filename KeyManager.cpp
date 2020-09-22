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
/**
 * @brief : key-manager server
 * @author: jimmyshi
 * @date: 2018-12-04
 */
#include "KeyManager.h"
#include "libutils/Crypto.h"
#include <signal.h>
#include <unistd.h>
#include <exception>
#include <iostream>

using namespace std;
using namespace dev;
using namespace jsonrpc;

// method
void BaseServer::decDataKey(const Json::Value& request, Json::Value& response)
{
    KCLOG(TRACE) << LOG_BADGE("Dec") << LOG_DESC("Receive") << endl
                 << request.toStyledString() << endl;
    Json::Value res;
    try
    {
        res["dataKey"] = decryptDataKeyHex(request[0u].asString());
        res["error"] = 0;
        res["info"] = "success";
    }
    catch (std::exception& e)
    {
        res["dataKey"] = "";
        res["error"] = 1;
        res["info"] = string(e.what());
    }
    response = res;
    KCLOG(TRACE) << LOG_BADGE("Dec") << LOG_DESC("Respond") << endl
                 << response.toStyledString() << endl;
}

void BaseServer::encDataKey(const Json::Value& request, Json::Value& response)
{
    KCLOG(TRACE) << LOG_BADGE("Enc") << LOG_DESC("Receive") << endl
                 << request.toStyledString() << endl;
    Json::Value res;
    try
    {
        res["dataKey"] = encryptDataKey(request[0u].asString());
        res["error"] = 0;
        res["info"] = "success";
    }
    catch (std::exception& e)
    {
        res["dataKey"] = "";
        res["error"] = 1;
        res["info"] = string(e.what());
    }
    response = res;
    KCLOG(TRACE) << LOG_BADGE("Enc") << LOG_DESC("Respond") << endl
                 << response.toStyledString() << endl;
}

void BaseServer::encWithCipherKey(const Json::Value& request, Json::Value& response)
{
    KCLOG(TRACE) << LOG_BADGE("EncWithKey") << LOG_DESC("Receive") << endl
                 << request.toStyledString() << endl;
    Json::Value res;
    try
    {
        res["dataKey"] = encryptWithCipherKey(request[0u].asString(), request[1u].asString());
        res["error"] = 0;
        res["info"] = "success";
    }
    catch (std::exception& e)
    {
        res["dataKey"] = "";
        res["error"] = 1;
        res["info"] = string(e.what());
    }
    response = res;
    KCLOG(TRACE) << LOG_BADGE("EncWithKey") << LOG_DESC("Respond") << endl
                 << response.toStyledString() << endl;
}

static bool should_exit = false;
static void exit_handler(int sig)
{
    should_exit = true;
}

std::string KeyManager::decryptDataKeyHex(const std::string& _cipherDataKey)
{
    bytes enData = fromHex(_cipherDataKey);
    bytes deData = aesCBCDecrypt(ref(enData), ref(m_superKey));
    return toHex(deData);
}

std::string KeyManager::encryptDataKey(const std::string& _dataKey)
{
    bytes dataKeyBtyes =
        bytesConstRef{(unsigned char*)_dataKey.c_str(), _dataKey.length()}.toBytes();

    bytes deData = aesCBCEncrypt(ref(dataKeyBtyes), ref(m_superKey));
    return toHex(deData);
}


std::string KeyManager::encryptWithCipherKey(
    const std::string& _data, const std::string& _cipherDataKey)
{
    bytes cipherDataKeyBytes = fromHex(_cipherDataKey);
    bytes readableDataKeyBytes = aesCBCDecrypt(ref(cipherDataKeyBytes), ref(m_superKey));
    bytes realDataKey = uniformKey(ref(readableDataKeyBytes));

    bytes dataBytes = bytesConstRef{(unsigned char*)_data.c_str(), _data.length()}.toBytes();
    bytes encData = aesCBCEncrypt(ref(dataBytes), ref(realDataKey));
    return toHex(encData);
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Usage: ./key-manager <port> <superkey>" << endl;
        cout << "Eg:    ./key-manager 8150 123xyz" << endl;
        return 0;
    }

    // Parse config
    int port;
    bytes superKey;
    try
    {
        port = atoi(argv[1]);
        string superKeyStr = argv[2];

        if (superKeyStr.empty())
        {
            KCLOG(ERROR) << LOG_BADGE("Load") << LOG_DESC("Superkey is empty") << endl;
            throw;
        }

        // uniform/compress key to a fixed size bytes of size 32/128
        superKey = uniformKey(bytesConstRef(superKeyStr));
    }
    catch (std::exception& e)
    {
        KCLOG(ERROR) << LOG_BADGE("Load") << LOG_DESC("Configure params error")
                     << LOG_KV("reason", e.what()) << endl;
        return 0;
    }

    // Start key-manager
    try
    {
        HttpServer connector(port);
        KeyManager keyManager(connector, superKey);

        if (keyManager.StartListening())
        {
            // register exit_handler signal
            signal(SIGABRT, &exit_handler);
            signal(SIGTERM, &exit_handler);
            signal(SIGINT, &exit_handler);

            KCLOG(TRACE) << LOG_BADGE("Load") << LOG_DESC("key-manager started")
                         << LOG_KV("port", port) << endl;
            while (!should_exit)
                sleep(1);
        }
        else
        {
            KCLOG(ERROR) << LOG_BADGE("Load") << LOG_DESC("Start Server failed") << endl;
        }
    }
    catch (jsonrpc::JsonRpcException& e)
    {
        KCLOG(ERROR) << LOG_BADGE("Load") << LOG_DESC("Start Server exception")
                     << LOG_KV("reason", e.what()) << endl;
    }

    return 0;
}

// curl -X POST --data '{"jsonrpc":"2.0","method":"getDataKey","params":["name"],"id":83}'
// http://127.0.0.1:8150 |jq
