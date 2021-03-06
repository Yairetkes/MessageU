from multiprocessing import connection
import struct
import socket

VERSION = 1
ERROR_RES_CODE = 9000
SUCCESS_SIGN_CODE = 2100
US_LIST_RES_CODE = 2101
PUB_KEY_RES_CEDE = 2102
MSG_SENT_RES_CODE = 2103
WAIT_MSGS_RES_CODE = 2104


class Respond:
    def __init__(self, res_code: int, payload_size: int, payload: bytes,connection: socket.socket) -> None:
        self.connection = connection
        self.res_code = res_code
        self.payload_size = payload_size
        self.res_header = struct.pack("<BHI", VERSION, self.res_code, payload_size)
        self.payload = payload

    def send(self):

        if self.res_code == ERROR_RES_CODE:
            self.connection.send(self.res_header)
        
        else:
            self.connection.send(self.res_header + self.payload)