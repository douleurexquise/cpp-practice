from src.order import Order, OrderStatus


class OrderDB:
    def __init__(self, filename="data/orders.txt"):
        self.filename = filename
        self.orders = []
        self.next_id = 1
        self._load_from_file()

    def _load_from_file(self):
        try:
            with open(self.filename, "r", encoding="utf-8") as file:
                for line in file:
                    line = line.strip()
                    if not line:
                        continue
                    order = Order.from_string(line)
                    self.orders.append(order)
                    if order.get_id() >= self.next_id:
                        self.next_id = order.get_id() + 1
        except FileNotFoundError:
            pass

    def _save_to_file(self):
        with open(self.filename, "w", encoding="utf-8") as file:
            for order in self.orders:
                file.write(order.to_string() + "\n")

    def add_order(self, client_id, days, status, is_emergency, items):
        new_order = Order(self.next_id, client_id, days, status, is_emergency, items)
        self.orders.append(new_order)
        self.next_id += 1
        self._save_to_file()

    def update_order(self, id, days, status, is_emergency, items):
        for order in self.orders:
            if order.get_id() == id:
                order.set_days(days)
                order.set_status(status)
                order.set_is_emergency(is_emergency)
                order.set_items(items)
                self._save_to_file()
                return True
        return False

    def update_order_status(self, id, new_status):
        for order in self.orders:
            if order.get_id() == id:
                order.set_status(new_status)
                self._save_to_file()
                return True
        return False

    def get_order_by_id(self, id):
        for order in self.orders:
            if order.get_id() == id:
                return order
        return Order()

    def get_all_orders(self):
        return self.orders

    def get_orders_by_client_id(self, client_id):
        result = []
        for order in self.orders:
            if order.get_client_id() == client_id:
                result.append(order)
        return result

    def close_shift(self):
        i = 0
        while i < len(self.orders):
            if self.orders[i].get_status() == OrderStatus.CANCELLED:
                self.orders.pop(i)
            else:
                self.orders[i].set_days(self.orders[i].get_days() + 1)
                i += 1
        self._save_to_file()