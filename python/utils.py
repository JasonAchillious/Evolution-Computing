# utils for reading tsp file


def read_tsp(file_path: str) -> list:
    with open(file_path) as f:
        context = f.read().splitlines()
    return context


def is_string_exist(context: list, string: str) -> bool:
    flag = False
    for line in context:
        if string in line:
            flag = True
    return flag


def get_key_value(string: str) -> (str, str):
    key=None
    value=None
    if string.count(":") == 1:
        key, value = string.split(":")
        key = key.strip()
        value = value.strip()
    return key,value


def get_coord(string: str) -> (int, float, float):
    index, x, y = string.split(" ")
    index = int(index)
    x = float(x)
    y = float(y)
    return index, x, y


def context2dict(context: list) -> dict:
    data = dict()
    sign = "NODE_COORD_SECTION"
    data[sign] = []
    coord_mode = False
    for line in context:
        if coord_mode:
            index, x, y = get_coord(line)
            data[sign].append((x, y))
        else:
            if sign in line:
                coord_mode = True
                continue
            key, value = get_key_value(line)

            if value.isdigit():
                value = int(value)
            data[key] = value

    return data
