import socket


port = 5050
buffer_for_length = 16
format = "utf-8"
device_name = socket.gethostname()

ip_address = socket.gethostbyname(device_name)

server_socket_address = (ip_address, port)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) ## Server object
server.bind(server_socket_address)
server.listen()

print('Our server has started listening')


while True:
    conn, addr= server.accept() # Establish a connection with the client
    print('Connected to',addr)
    connected =True
    while connected:
        length_of_upcoming_msg = conn.recv(buffer_for_length).decode(format)
        if length_of_upcoming_msg:
            length_of_upcoming_msg = int(length_of_upcoming_msg)
            msg = conn.recv(length_of_upcoming_msg).decode(format)
            if msg == "Off":
                print('Terminating connection with',addr)
                conn.send('Server: Goodbye! It was nice to serve you'.encode(format))
                connected = False
            else:
                print(msg)
                conn.send('Server: Message received successfuly'.encode(format))
    conn.close( )# Close the connection with the client
    
    