import random

ID_BIT_LENGTH = 128

class clientUser:
    def __init__(self, name: str, public_key) -> None:
        # TODO: turn the fields into private? with __
        if len(name) > 255:
            raise ValueError('client name is too long')
        else:
            self.__name = name
            self.__public_key = public_key
            # TODO: implement key
            self.__id = random.getrandbits(ID_BIT_LENGTH)
            self.__last_seen = 0

    
    def get_name(self):
        return self.__name

    def get_public_key(self):
        return self.__public_key

    def get_id(self):
        return self.__id

    def get_last_seen(self):
        return self.__last_seen

    # TODO: implement
    def set_last_seen(self, time: int):
        pass

