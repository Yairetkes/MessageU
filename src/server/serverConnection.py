from asyncio.windows_events import NULL
import socket
import struct
import os
import threading
import request


# key = 4

class serverConnection:
    def __init__(self, host_ip: str, info_file_name: str):
        """ 
        initializing the object.
        """
        dirname = os.path.dirname(__file__)
        filename = os.path.join(dirname, info_file_name)
        with open(filename, "r") as f:
            # TODO: check the content of the file - if it's a valid input...
            port = int(f.read())

        self.port = port
        self.host_ip = host_ip
        self.socket = NULL

    
    def connect(self):
        """ 
        This method is ment to do the first stages of server connection:
        1. socket
        2. bind
        3. listen

        """
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            self.socket = s
            s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            s.bind((self.host_ip, self.port))
            s.listen()
            print("starting to listen")
            while(True):
                self.wait_for_client()
        
        return
    

    def wait_for_client(self):
        """ 
        This method is ment to accept a connection from client.
         """
        conn, addr = self.socket.accept()
        t = threading.Thread(target=self.maintain_contact, args=(conn,addr))
        t.start()
         
    
    def maintain_contact(self, conn: socket.socket, addr: str):
        """
        This method is the main method of the class, it should manage the whole contact proccess
        with the client.
        """

        # TODO: change buffer length.
        buff_len = 438
        with conn:
            print('Connected by', addr)

            req = request.Request(conn, buff_len)

            req.process_request()