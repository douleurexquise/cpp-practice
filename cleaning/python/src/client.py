class Client:
    def __init__(self, id=0, name="", email=""):
        self.id = id
        self.name = name
        self.email = email
    
    def get_id(self):
        return self.id
    
    def get_name(self):
        return self.name
    
    def get_email(self):
        return self.email
    
    def set_id(self, id):
        self.id = id
    
    def set_name(self, name):
        self.name = name
    
    def set_email(self, email):
        self.email = email
    
    def to_string(self):
        return f"{self.id};{self.name};{self.email}"
    
    @staticmethod
    def from_string(line):
        parts = line.split(';')
        if len(parts) >= 3:
            id = int(parts[0])
            name = parts[1]
            email = parts[2]
            return Client(id, name, email)
        return Client()