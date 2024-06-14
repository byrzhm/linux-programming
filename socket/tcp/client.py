import socket

HOST = '127.0.0.1'
PORT = 65432

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

    while True:
        try:
            input_string = input("Enter a string: ")
        except EOFError:
            break
        
        s.sendall(input_string.encode())
