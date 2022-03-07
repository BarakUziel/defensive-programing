import socket
import threading
from numpy.core import integer

ip = '127.0.0.1'
f = open("myport.info.txt", "r")
PORT = f.read()

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((ip, PORT))
server.listen()

clients = []


def broadcast(message):
    for client in clients:
        client.send(message)


def handle(client):
    while True:
        try:
            message = client.recv(1024)
            broadcast(message)
        except:
            clients.remove(client)
            client.close()
            break


def receive():
    while True:
        client = server.accept()
        clients.append(client)
        thread = threading.Thread(target=handle, args=(client,))
        thread.start()

receive()
