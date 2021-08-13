import socket
import random
import time
import datetime

def server_program(port):
    arr = ["Hočem ven!", "Ali je zunaj lepo vreme?", "Posodi mi radirko.", "Gremo na pivo."]
    s = socket.socket()  # get instance
    s.bind((socket.gethostname(), port))  # bind host address and port together

    s.listen(5) #number of clients that can listen simultaneously
    conn, address = s.accept()  # accept new connection
    print("Connection from: " + str(address))
    curr_time = datetime.datetime.now()
    curr = curr_time.strftime("%Y-%m-%d %H:%M:%S")
    seedHour = curr_time.hour
    random.seed(curr)
    rand = random.randint(1,40)
    print(curr)
    while True:
        time.sleep(1)
        curr_time = datetime.datetime.now()
        curr = curr_time.strftime("%Y-%m-%d %H:%M:%S")
        if seedHour != curr_time.hour:
            random.seed(curr)
            print("changing seed")
            seedHour = curr_time.hour
            rand = random.randint(1,40)
            print(curr)
        value = arr[random.randint(0,3)]
        data = ""
        for i in range(0, len(value)):
            data += chr(ord(value[i]) + rand)
        conn.send(data.encode())  # send data to the client

    conn.close() # terminate connection

if __name__ == '__main__':
    port = input(' -> ')
    server_program(int(port))

