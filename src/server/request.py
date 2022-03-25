from asyncio.windows_events import NULL
from calendar import c
import socket
import struct


# variables needed to the use of the class
client_id_idx = 0
version_idx = 1
code_idx = 2
payload_size_idx = 3
payload_idx = 4

class Request:
    """
    class Request will recieve data packet from client, proccess it and perform the command.
    """
    def __init__(self, conn: socket.socket, buffer_length: int) -> None:
        """
        The __init__ method will recieve data packet from client.
        """
        # TODO: implemnt the method.
        self.connection = conn
        self.buffer_length = buffer_length
        self.messages = []
        self.client_users = []

        buffer_recv = self.connection.recv(self.buffer_length)
        print("message recieved: " + str(buffer_recv) + "\n\n")
        self.packed_buffer = struct.unpack('<16cBHI255s160s', buffer_recv)
        print("packed_buffer = " + str(self.packed_buffer))


    # TODO: implement
    def sign_client(self):
        pass

    # TODO: implement
    def send_users_list():
        pass

    #TODO: implement
    def get_public_key():
        pass

    # TODO: implement
    def extract_msgs():
        pass

    # TODO: implement
    def send_msg():
        pass

    # TODO: implement
    def get_sym_key():
        pass

    # TODO: implement
    def send_sym_key():
        pass

    # TODO: implement
    def process_request(self):
        """
        suggestion - 
        this method will proccess the request and return the below data -
        1. request number.
        2. all other needed data.
        then it will return this values to serverConnection class in order for it to 
        create a sub class which is the relevant request, for instance getAllConnectionsReq...
        
        """
        code_signing = 110
        code_users_list = 120
        code_public_key = 130
        code_extract_msgs = 140
        code_send_msg = 150
        code_get_sym_key = 151
        code_send_sym_key = 152
        

        if self.packed_buffer[code_idx] == code_signing:
            self.sign_client()

        if self.packed_buffer[code_idx] == code_users_list:
            self.send_users_list()

        if self.packed_buffer[code_idx] == code_public_key:
            self.get_public_key()

        if self.packed_buffer[code_idx] == code_extract_msgs:
            self.extract_msgs()

        if self.packed_buffer[code_idx] == code_send_msg:
            self.send_msg()

        if self.packed_buffer[code_idx] == code_get_sym_key:
            self.get_sym_key()

        if self.packed_buffer[code_idx] == code_send_sym_key:
            self.send_sym_key()