import socket

port = 5050
buffer_for_length = 16
format = "utf-8"
device_name = socket.gethostname()

ip_address = socket.gethostbyname(device_name)

server_socket_address = (ip_address, port)

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect(server_socket_address)

print('Our client is trying to connect')



def message_to_send(hours):
    hours = str(hours).encode(format)
    hours_length = len(hours)
    hours_length = str(hours_length).encode(format)
    hours_length += b" " * (buffer_for_length - len(hours_length))
    
    
    client.send(hours_length)
    client.send(hours)
    
    sent_from_server = client.recv(2048).decode(format)
    print(sent_from_server)
    
    
while True:
    #print('Enter the number of hours worked: ')
    
    inp = input('Enter the number of hours worked: ')
    if inp == 'Off':
        message_to_send(inp)
        break
    else:
        inp  = float(inp)
        message_to_send(inp)