from asyncio.windows_events import NULL
from calendar import c
from distutils.log import error
import socket
import struct
import clientUser as cl
import respond
import message as msg

# variables needed to the use of the class
code_signing = 1100
code_users_list = 1101
code_public_key = 1102
code_extract_msgs = 1104
code_send_msg = 1103

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
        self.messages = [msg.Message]
        self.client_users = [cl.clientUser]

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

        if self.packed_header[int(client_id_idx)] in [user.get_id() for user in self.client_users]:
            raise NameError('The name already appear in the users list (the user already signed)')
        else:
            client = cl.clientUser(name, public_key)
            self.client_users.append(client)
            return client.get_id()

    # TODO: test
    def send_users_list(self):
        if (not self.client_users):
            raise error("no other clients!")
        values = []
        struct_str = '<'
        for user in self.client_users:
            if user.get_id == self.packed_header[client_id_idx]:
                continue # becuse this is our clients ID.
            else:
                values.append(bytes(str(user.get_id()), encoding='utf8'))
                values.append(bytes(str(user.get_name()), encoding='utf8'))
                struct_str += '16s255s'

        payload = struct.pack(struct_str, *values)
        res = respond.Respond(code_users_list, len(payload), payload, self.connection)
        res.send()

    #TODO: test
    def get_public_key(self):
        id = "-1"
        pub_key = "-1"
        for user in self.client_users:
            if user.get_id == int(self.packed_request[payload_idx]):
                id = str(user.get_id())
                pub_key = str(user.get_public_key())
        
        if id == "-1":
            raise NameError("there is no client with ID " + str(self.packed_request[payload_idx]))

        payload = struct.pack('<16s160s', bytes(id,encoding='utf8'), bytes(pub_key,encoding='utf8'))
        res = respond.Respond(PUB_KEY_RES_CEDE, len(payload), payload, self.connection)
        res.send()

    # TODO: implement
    def extract_msgs(self):
        pass

    # TODO: test
    def send_msg(self):
        payload = self.packed_request[payload_idx]
        id, type, size, message = (payload.split(b'\x00'))
        print("id = ", id)
        print("type = ", type)
        print("size = ", size)
        print("message = ", message)

        if id not in [user.get_id() for user in self.client_users]:
            raise NameError('The id does not appear in the users list.')
        else:
            mesg = msg.Message(id, )#TODO: continue here - create id 
            # self.client_users.append(client)
            # return client.get_id()

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
        if self.packed_header[code_idx] == code_signing:
            try:
                id = self.sign_client()
                self.sign_response(id)
            except NameError:
                print("NameError when trying to sign a new client user")
                self.error_response()

        if self.packed_header[code_idx] == code_users_list:
            try:
                self.send_users_list()
            except error:
                print("Error! theres no other clients that are signed")
                self.error_response()

        if self.packed_header[code_idx] == code_public_key:
            try:
                self.get_public_key()
            except NameError:
                print("The requested user does not appear to exist.")
                self.error_response()

        if self.packed_header[code_idx] == code_extract_msgs:
            self.extract_msgs()

        if self.packed_header[code_idx] == code_send_msg:
            try:
                self.send_msg()
            except NameError:
                print("The destination user does not seem to apear.")
                self.error_response()
