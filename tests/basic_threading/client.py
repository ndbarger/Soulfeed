import socket as sock

host = '127.0.0.1'
port = 8080

client_socket = sock.socket(sock.AF_INET, sock.SOCK_STREAM, sock.IPPROTO_TCP)

client_socket.connect((host, port))
print(f"Connected to server at {host}:{port}")

while True:
    try:
        client_socket.send(bytes(input("> "), "utf-8"))

        msg = client_socket.recv(1024)

        print(f"Server: {str(msg, 'utf-8')}")

        if msg == b"disconnected;":
            break
    except KeyboardInterrupt:
        break

client_socket.close()
