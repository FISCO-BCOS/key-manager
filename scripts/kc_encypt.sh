#! /bin/bash
[ ! -n "$1" ] && echo "Usage: sh $0 <URL 127.0.0.1:8150> <plain text>" && exit;
curl -X POST --data '{"jsonrpc":"2.0","method":"encDataKey","params":["'$2'"],"id":83}' $1 |jq