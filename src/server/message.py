

class Message:
    def __init__(self, id, toClient, fromClient, type, content) -> None:
        # TODO: input validations!!
        self.id = id
        self.toClient = toClient
        self.fromClient = fromClient
        self.type = type
        self.content = content