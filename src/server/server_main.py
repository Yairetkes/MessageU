import server_connection as sc
import tools
import threading


PORT, HOST_IP, FILE_NAME = 7000, '127.0.0.1', "myport.info"

def main():
    # TODO: reading server info file, (creating if not exist?).
    tools.create_info_file(FILE_NAME, PORT)
    server = sc.server_connection(HOST_IP, FILE_NAME)
    server.connect()


if __name__ == "__main__":
    main()