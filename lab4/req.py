import requests
import json
from time import sleep

def resolve(node):
    url = f"http://localhost:{node}/nodes/resolve"
    resp = requests.get(url)
    print(resp.text)

def mine(node):
    url = f"http://localhost:{node}/mine"
    resp = requests.get(url)
    print(resp.text)

def do_transaction(node):
    url = f"http://localhost:{node}/transactions/new"
    payload = {"sender": "d4ee26eee15148ee92c6cd394edd974e", "recipient": "someone-other-address", "amount": 5}
    resp = requests.post(url, json=payload)
    print(resp.text)


def register_nodes():
    url = "http://localhost:5000/nodes/register"
    payload = {"nodes": ["http://localhost:5001"]}
    resp = requests.post(url, json=payload)
    print(resp.text)

    sleep(2)
    url = "http://localhost:5001/nodes/register"
    payload = {"nodes": ["http://localhost:5000"]}
    resp = requests.post(url, json=payload)
    print(resp.text)


register_nodes()
mine(5000)
mine(5000)
mine(5001)
mine(5001)
mine(5001)
resolve(5000)
