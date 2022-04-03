import random

ID_BIT_LENGTH = 32

class Message:
    def __init__(self, id, toClient, fromClient, type, content) -> None:
        # TODO: input validations!!
        self.__id = random.getrandbits(ID_BIT_LENGTH)
        self.__toClient = toClient
        self.__fromClient = fromClient
        self.__type = type
        self.__content = content

    def get_id(self):
        return self.__id

    def get_toClient(self):
        return self.__toClient

    def get_fromClient(self):
        return self.__fromClient

    def get_type(self):
        return self.__type

    def get_content(self):
        return self.__content

    
    # def set_id(self):
    #     return self.__id

    # def set_toClient(self):
    #     return self.__toClient

    # def set_fromClient(self):
    #     return self.__fromClient

    # def set_type(self):
    #     return self.__type

    # def set_content(self):
    #     return self.__content