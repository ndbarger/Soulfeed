import socket as sock
import threading

server_socket = sock.socket(sock.AF_INET, sock.SOCK_STREAM, sock.IPPROTO_TCP)

host = '127.0.0.1'
port = 8080

clients = []

server_socket.bind((host, port))

server_socket.listen(5)

client_socket, addr = (None, None)
msg = ""

def server_listen():
    global client_socket, addr, clients
    try:
        while True:
            client_socket, addr = server_socket.accept()
            print(f"Debug: Got connection from {addr}")

            clients.append(client_socket)
    except KeyboardInterrupt:
        return

listen_thread = threading.Thread(target=server_listen)

print(f"Server listening on {host}:{port}")

listen_thread.start()

while True:
    try:
        for i,client in enumerate(clients):
            msg = client.recv(1024)
        
            print(f"Client [{addr}]: {str(msg, "utf-8")}")
            if msg == b'end;':
                print(f"Debug: Client disconnected at {addr}")
                client.send(b"disconnected;")
                client.close()
                clients.pop(i)
            else:
                client.send(b"ok;")
    except KeyboardInterrupt:
        break

listen_thread.join()

for client in clients:
    client.close()

server_socket.close()