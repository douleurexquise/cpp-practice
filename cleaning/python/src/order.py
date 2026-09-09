from enum import Enum

class OrderStatus(Enum):
    ACCEPTED = "Принят"
    IN_PROGRESS = "В работе"
    READY = "Готов"
    ISSUED = "Выдан"
    CANCELLED = "Отменён"

CATALOG = ["Куртка", "Пальто", "Брюки", "Рубашка", "Платье", "Обувь", "Аксессуар"]

class Order:
    def __init__(self, id=0, client_id=0, days=0, status=OrderStatus.ACCEPTED, is_emergency=False, items=None):
        self.id = id
        self.client_id = client_id
        self.days = days
        self.status = status
        self.is_emergency = is_emergency
        self.items = items if items is not None else []
    
    def get_id(self):
        return self.id
    
    def get_client_id(self):
        return self.client_id
    
    def get_days(self):
        return self.days
    
    def get_status(self):
        return self.status
    
    def get_is_emergency(self):
        return self.is_emergency
    
    def get_items(self):
        return self.items
    
    def set_id(self, id):
        self.id = id
    
    def set_client_id(self, client_id):
        self.client_id = client_id
    
    def set_days(self, days):
        self.days = days
    
    def set_status(self, status):
        self.status = status
    
    def set_is_emergency(self, is_emergency):
        self.is_emergency = is_emergency
    
    def set_items(self, items):
        self.items = items
    
    @staticmethod
    def get_catalog():
        return CATALOG
    
    @staticmethod
    def is_valid_item(item):
        item_lower = item.lower()
        for catalog_item in CATALOG:
            if item_lower == catalog_item.lower():
                return True
        return False
    
    @staticmethod
    def status_to_string(status):
        return status.value
    
    @staticmethod
    def status_from_string(status_str):
        for status in OrderStatus:
            if status.value == status_str:
                return status
        return OrderStatus.ACCEPTED
    
    def to_string(self):
        emergency_int = 1 if self.is_emergency else 0
        items_str = ",".join(self.items)
        return f"{self.id};{self.client_id};{self.days};{self.status.value};{emergency_int};{items_str}"
    
    @staticmethod
    def from_string(line):
        parts = line.split(';')
        if len(parts) >= 6:
            id = int(parts[0])
            client_id = int(parts[1])
            days = int(parts[2])
            status = Order.status_from_string(parts[3])
            is_emergency = parts[4] == '1'
            items_str = parts[5]
            items = items_str.split(',') if items_str else []
            return Order(id, client_id, days, status, is_emergency, items)
        return Order()