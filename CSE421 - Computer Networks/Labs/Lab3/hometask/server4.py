import socket 

port = 5050

buffer_for_length = 16

format = 'utf-8'

device_name = socket.gethostname()

ip_address = socket.gethostbyname(device_name)

server_socket_address = (ip_address, port)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) ## Server object
server.bind(server_socket_address)
server.listen()


print('Our server has started listening ')


def calculate_salary(hours):
    
    
    if hours <= 40:
        salary = hours* 200
        
    elif hours >40:
        salary = (hours - 40) * 300 + 8000
    
    return salary
while True:
    
    conn,addr = server.accept()
    
    print('Connected to',addr)
    
    connected = True
    
    while connected:
        length_of_upcoming_msg = conn.recv(buffer_for_length).decode(format)
        if length_of_upcoming_msg:
            length_of_upcoming_msg = int(length_of_upcoming_msg)
            hours = conn.recv(length_of_upcoming_msg).decode(format)
            if hours == "Off":
                print('Terminating connection with',addr)
                conn.send('Server: Goodbye! It was nice to serve you'.encode(format))
                connected = False
            else:
                hours = float(hours)
                salary= calculate_salary(hours)
                conn.send(f'Taka: {salary}'.encode(format))
    conn.close()
    