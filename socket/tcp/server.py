import socket

HOST = '127.0.0.1'
PORT = 65432

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        while True:
            try:
                data = conn.recv(1024)
                print(data.decode())
            except ConnectionResetError:
                print("Connection reset by peer")
                break
            
            conn.sendall(data)