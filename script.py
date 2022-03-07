import sqlite3

connection = sqlite3.connect('server.db')
cursor = connection.cursor()

q1 = """CREATE TABLE IF NOT EXISTS clients(
                ID integer PRIMARY KEY AUTOINCREMENT,
                UserName text,
                PublicKey text,
                LastSeen text
                )"""
cursor.execute(q1)

q2 = """CREATE TABLE IF NOT EXISTS messages(
                ID integer PRIMARY KEY AUTOINCREMENT,
                Type boolean,
                Content text,
                ToClient integer,
                FromClient integer,
                foreign key(ToClient) REFERENCES clients(ID),
                foreign key(FromClient) REFERENCES clients(ID)
                )"""
cursor.execute(q2)


def create_user(UserName, PublicKey, LastSeen):
    try:
        cursor.execute("INSERT INTO clients (UserName, PublicKey, LastSeen) VALUES (?, ?, ?)",
                       (UserName, PublicKey, LastSeen))
        return 'successful'
    except sqlite3.Error as er:
        return 'unsuccessful, user name already exists'
    connection.commit()


def get_clients_list():
    cursor.execute("SELECT userName FROM clients")
    clients_list = cursor.fetchall()
    return clients_list


def client_send_message(message, to_who, from_who):
    try:
        cursor.execute("INSERT INTO messages (Type, Content, ToClient, FromClient) VALUES (?, ?, ?, ?)",
                       (message.type, message.content, to_who, from_who))
        return 'successful'
    except sqlite3.Error as er:
        return 'unsuccessful'
    connection.commit()


def client_request_message(to_who):
    try:
        cursor.execute("SELECT content FROM messages WHERE ToClient=VALUE (?)", 2)
        client_messages = cursor.fetchall()
        return client_messages
    except sqlite3.Error as er:
        return 'unsuccessful'
    connection.commit()