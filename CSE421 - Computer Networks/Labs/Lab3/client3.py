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



def message_to_send(msg):
    message = msg.encode(format)
    message_length = len(message)
    message_length = str(message_length).encode(format)
    message_length += b" "*(buffer_for_length - len(message_length))
    
    client.send(message_length)
    client.send(message)
    
    sent_from_server = client.recv(2048).decode(format)
    print(sent_from_server)
    
#message_to_send(f"Client :The device name of the client is {device_name} and the IP adddress of the client is {ip_address}")


while True:
    print('Enter your message:')
    inp = input()
    message_to_send(inp)
    if inp == "Off":
        break