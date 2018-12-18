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
 * @brief : keycenter server
 * @author: jimmyshi
 * @date: 2018-12-04
 */
#include "KeyCenter.h"
#include <signal.h>
#include <unistd.h>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <exception>
#include <iostream>

using namespace std;
using namespace dev;
using namespace jsonrpc;

// method
void BaseServer::decDataKey(const Json::Value& request, Json::Value& response)
{
    KCLOG(TRACE) << "[Dec] Receive: " << endl << request.toStyledString() << endl;
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
    KCLOG(TRACE) << "[Dec] Respond: " << endl << response.toStyledString() << endl;
}

void BaseServer::encDataKey(const Json::Value& request, Json::Value& response)
{
    KCLOG(TRACE) << "[Enc] Receive: " << endl << request.toStyledString() << endl;
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
    KCLOG(TRACE) << "[Enc] Respond: " << endl << response.toStyledString() << endl;
}

void BaseServer::encWithCipherKey(const Json::Value& request, Json::Value& response)
{
    KCLOG(TRACE) << "[EncWithKey] Receive: " << endl << request.toStyledString() << endl;
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
    KCLOG(TRACE) << "[EncWithKey] Respond: " << endl << response.toStyledString() << endl;
}

static bool should_exit = false;
static void exit_handler(int sig)
{
    should_exit = true;
}

std::string KeyCenter::decryptDataKeyHex(const std::string& _cipherDataKey)
{
    bytes enData = fromHex(_cipherDataKey);
    bytes deData = aesCBCDecrypt(ref(enData), ref(m_superKey));
    return toHex(deData);
}

std::string KeyCenter::encryptDataKey(const std::string& _dataKey)
{
    bytes dataKeyBtyes =
        bytesConstRef{(unsigned char*)_dataKey.c_str(), _dataKey.length()}.toBytes();

    bytes deData = aesCBCEncrypt(ref(dataKeyBtyes), ref(m_superKey));
    return toHex(deData);
}


std::string KeyCenter::encryptWithCipherKey(
    const std::string& _data, const std::string& _cipherDataKey)
{
    bytes enData = fromHex(_cipherDataKey);
    bytes dataKey = aesCBCDecrypt(ref(enData), ref(m_superKey));

    bytes dataBytes = bytesConstRef{(unsigned char*)_data.c_str(), _data.length()}.toBytes();
    bytes encData = aesCBCEncrypt(ref(dataBytes), ref(dataKey));
    return toHex(encData);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Usage: ./keycenter <config file>" << endl;
        cout << "Eg:    ./keycenter kcconfig.ini" << endl;
        return 0;
    }

    string path(argv[1]);

    // Parse config
    int port;
    bytes superKey;
    try
    {
        boost::property_tree::ptree pt;
        boost::property_tree::read_ini(path, pt);

        port = pt.get<int>("keycenter.port", 31443);
        superKey = readableKeyBytes(pt.get<std::string>("keycenter.superkey", ""));

        if (superKey.empty())
        {
            KCLOG(ERROR) << "Superkey is empty" << endl;
            throw;
        }
    }
    catch (std::exception& e)
    {
        KCLOG(ERROR) << "Parse configure file " << path << " failed for: " << e.what() << endl;
        return 0;
    }

    // Start keycenter
    try
    {
        HttpServer connector(port);
        KeyCenter keycenter(connector, superKey);

        if (keycenter.StartListening())
        {
            // register exit_handler signal
            signal(SIGABRT, &exit_handler);
            signal(SIGTERM, &exit_handler);
            signal(SIGINT, &exit_handler);

            KCLOG(TRACE) << "keycenter stared. Port: " << port << endl;
            while (!should_exit)
                sleep(1);
        }
        else
        {
            KCLOG(ERROR) << "Start Server failed" << endl;
        }
    }
    catch (jsonrpc::JsonRpcException& e)
    {
        KCLOG(ERROR) << e.what() << endl;
    }

    return 0;
}

// curl -X POST --data '{"jsonrpc":"2.0","method":"getDataKey","params":["name"],"id":83}'
// http://127.0.0.1:31443 |jq
