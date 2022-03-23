import serverConnection as sc
import tools


PORT, HOST_IP, FILE_NAME = 7000, '127.0.0.1', "myport.info"

def main():
    tools.create_info_file(FILE_NAME, PORT)
    server = sc.serverConnection(HOST_IP, FILE_NAME)
    server.connect()


if __name__ == "__main__":
    main()