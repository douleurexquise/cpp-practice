from src.client import Client


class ClientDB:
    def __init__(self, filename="data/clients.txt"):
        self.filename = filename
        self.clients = []
        self.next_id = 1
        self._load_from_file()

    def _load_from_file(self):
        """Загружает клиентов из файла при создании объекта"""
        try:
            with open(self.filename, "r", encoding="utf-8") as file:
                for line in file:
                    line = line.strip()
                    if not line:
                        continue
                    client = Client.from_string(line)
                    self.clients.append(client)
                    if client.get_id() >= self.next_id:
                        self.next_id = client.get_id() + 1
        except FileNotFoundError:
            # Если файла ещё нет — просто начинаем с пустой базы
            pass

    def _save_to_file(self):
        """Сохраняет всех клиентов в файл (перезаписывает)"""
        with open(self.filename, "w", encoding="utf-8") as file:
            for client in self.clients:
                file.write(client.to_string() + "\n")

    def add_client(self, name, email):
        """Добавляет нового клиента с автоматическим ID"""
        new_client = Client(self.next_id, name, email)
        self.clients.append(new_client)
        self.next_id += 1
        self._save_to_file()

    def update_client(self, id, name, email):
        """Обновляет данные существующего клиента"""
        for client in self.clients:
            if client.get_id() == id:
                client.set_name(name)
                client.set_email(email)
                self._save_to_file()
                return True
        return False

    def get_client_by_id(self, id):
        """Возвращает клиента по ID или пустого клиента, если не найден"""
        for client in self.clients:
            if client.get_id() == id:
                return client
        return Client()

    def get_all_clients(self):
        """Возвращает список всех клиентов"""
        return self.clients

    def client_exists(self, id):
        """Проверяет, существует ли клиент с таким ID"""
        return self.get_client_by_id(id).get_id() != 0