#!/bin/bash

echo "MD5\n"
echo -n "this is a hash message" | openssl dgst -md5
echo -n "this ir a hash message" | openssl dgst -md5
echo "SHA256\n" 
echo -n "this is a hash message" | openssl dgst -sha256
echo -n "this ir a hash message" | openssl dgst -sha256
