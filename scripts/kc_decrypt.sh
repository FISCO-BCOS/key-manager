#! /bin/bash
[ ! -n "$1" ] && echo "Usage: sh $0 <URL 127.0.0.1:31334> <cipher text>" && exit;
curl -X POST --data '{"jsonrpc":"2.0","method":"decDataKey","params":["'$2'"],"id":83}' $1 |jq