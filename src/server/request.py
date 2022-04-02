from asyncio.windows_events import NULL
from calendar import c
import socket
import struct
from typing_extensions import Self
import clientUser as cl
import respond


# variables needed to the use of the class
client_id_idx = 0
version_idx = 1
code_idx = 2
payload_size_idx = 3
payload_idx = 4
REQUEST_MAX_LEN = 1024
#TODO: change REQUEST_MAX_LEN to the right value.
# should be compatible with this variable at file ClientUi.cpp on server (plus header
# which is 23 bytes long)

ERROR_RES_CODE = 9000
SUCCESS_SIGN_CODE = 2100
US_LIST_RES_CODE = 2101
PUB_KEY_RES_CEDE = 2102
MSG_SENT_RES_CODE = 2103
WAIT_MSGS_RES_CODE = 2104

HEADER_LENGTH = 23

class Request:
    """
    class Request will recieve data packet from client, proccess it and perform the command.
    """
    def __init__(self, conn: socket.socket) -> None:
        """
        The __init__ method will recieve data packet from client.
        """
        # TODO: implemnt the method.
        self.connection = conn
        self.messages = []
        self.client_users = []

        self.buffer_recv = self.connection.recv(REQUEST_MAX_LEN)
        # TODO: might be unsafe to use recv()
        # print("message recieved: " + str(self.buffer_recv) + "\n\n")

        # preparing the request - mostly unpacking.
        self.packed_header = struct.unpack('<16cBHI', self.buffer_recv[0:HEADER_LENGTH])
        struct_str = "<16sBHI" + str(int.from_bytes(self.packed_header[payload_size_idx], byteorder="little")) + "s"
        self.request_length = HEADER_LENGTH + int.from_bytes( self.packed_header[payload_size_idx], byteorder="little")
        print("******* request_length = ", str(self.request_length))
        self.packed_request = struct.unpack(struct_str, self.buffer_recv[0:self.request_length])
        print("packed_request = " + str(self.packed_request))


    # TODO: test
    def sign_client(self) -> int:
        # TODO add to final report - by the protocol any user can sign up as many
        #  times as he wants with different names. 
        payload = self.packed_request[payload_idx]
        name, public_key = (payload.split(b'\x00'))
        print("name = ", name)
        print("public_key = ", public_key)

        if name in self.client_users:
            raise NameError('The name already appear in the users list (the user already signed)')
        else:
            client = cl.clientUser(name, public_key)
            self.client_users.append(client)
            return client.get_id()

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
    def error_response(self):
        res = respond.Respond(ERROR_RES_CODE, 0, bytes(), self.connection)
        res.send()

    # TODO: implement
    def sign_response(id: int):
        pass

    # TODO: implement
    def process_request(self):
        """
        this method will proccess the request and call the right function to fullfil it.
        
        """
        code_signing = 1100
        code_users_list = 1101
        code_public_key = 1102
        code_extract_msgs = 1104
        code_send_msg = 1103
        # code_get_sym_key = 151
        # code_send_sym_key = 152
        

        if self.packed_header[code_idx] == code_signing:
            try:
                id = self.sign_client()
                self.sign_response(id)
            except NameError:
                print("NameError when trying to sign a new client user")
                self.error_response()

        if self.packed_header[code_idx] == code_users_list:
            self.send_users_list()

        if self.packed_header[code_idx] == code_public_key:
            self.get_public_key()

        if self.packed_header[code_idx] == code_extract_msgs:
            self.extract_msgs()

        if self.packed_header[code_idx] == code_send_msg:
            self.send_msg()