from asyncio.windows_events import NULL
import socket
import struct


class Request:
    """
    class Request will recieve data packet from client, proccess it and perform the command.
    """
    def __init__(self, conn: socket.socket, buffer_length: int) -> None:
        """
        The __init__ method will recieve data packet from client.
        """
        # TODO: implemnt the method.
        self.request = NULL
        self.connection = conn
        self.buffer_length = buffer_length


    #TODO: implement
    def process_request(self):
        """
        suggestion - 
        this method will proccess the request and return the below data -
        1. request number.
        2. all other needed data.
        then it will return this values to serverConnection class in order for it to 
        create a sub class which is the relevant request, for instance getAllConnectionsReq...
        
        """
        buffer_recv = self.connection.recv(self.buffer_length)
        print("message recieved: " + str(buffer_recv) + "\n\n")
        packed_baffer = struct.unpack('<16cBHI255s160s', buffer_recv)
        print("packed_baffer = " + str(packed_baffer))
        # conn.sendall(d)