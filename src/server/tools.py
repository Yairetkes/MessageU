import os


def create_info_file(file_name: str, port_num: int):
    dirname = os.path.dirname(__file__)
    filename = os.path.join(dirname, file_name)
    with open(filename, "w+") as f:
        data = f.read()
        f.seek(0)
        f.write(str(port_num))
        f.truncate()