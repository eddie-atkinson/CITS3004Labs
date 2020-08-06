#!/usr/bin/env python3

def crack():
    alphabet = "".join([chr(i) for i in range(65, 91, 1)])
    to_crack = input("Enter the string to crack: ")
    out_string = ""
