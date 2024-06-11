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

def vowelcount(message):
    vowels ='aeiouAEIOU'
    count = 0
    for i in msg:
        if i in vowels:
            count += 1
            
    return count

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
                vowel_count = vowelcount(msg)
                
                if vowel_count <= 0:
                    conn.send('Not enough vowels'.encode(format))
                elif vowel_count >0 and vowel_count <=2:
                    conn.send('Enough vowels I guess'.encode(format))
                elif vowel_count >2:
                    conn.send('Too many vowels'.encode(format))
                
                # count = 0
                # for char in msg:
                #     if char == "o":
                #         count+=1
                # print(msg)
                # conn.send(f"Number of o's in message: {str(count)}".encode(format))
    conn.close( )# Close the connection with the client
    
    