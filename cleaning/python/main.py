from src.client_db import ClientDB
from src.order_db import OrderDB
from src.order import Order, OrderStatus


def print_clients(db):
    """Выводит список всех клиентов"""
    clients = db.get_all_clients()
    if not clients:
        print("База клиентов пуста.")
        return
    print("\n--- Список клиентов ---")
    for c in clients:
        print(f"ID: {c.get_id()} | Имя: {c.get_name()} | Email: {c.get_email()}")
    print("-----------------------")


def print_orders(db):
    """Выводит список всех заказов"""
    orders = db.get_all_orders()
    if not orders:
        print("База заказов пуста.")
        return
    print("\n--- Список заказов ---")
    for o in orders:
        emergency_mark = "[СРОЧНО] " if o.get_is_emergency() else ""
        items_str = ", ".join(o.get_items())
        print(
            f"ID: {o.get_id()} | Клиент ID: {o.get_client_id()} | "
            f"Дней назад: {o.get_days()} | Статус: {Order.status_to_string(o.get_status())} | "
            f"{emergency_mark}Вещи: {items_str}"
        )
    print("----------------------")


def input_int(prompt):
    """Безопасный ввод целого числа (аналог cin >> choice с проверкой)"""
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            print("Ошибка ввода. Введите число.")


def main():
    print(
        "**************************************************************************\n"
        "* Нижегородский государственный технический университет                  *\n"
        "* Курсовая работа по дисциплине \"Программирование\"                     *\n"
        "* Система управления заказами в химчистке                                *\n"
        "* Выполнил студент группы 24-ВМв Ложкин Степан Владимирович              *\n"
        "**************************************************************************"
    )

    client_db = ClientDB()
    order_db = OrderDB()

    while True:
        print("\n=== СИСТЕМА УПРАВЛЕНИЯ ЗАКАЗАМИ В ХИМЧИСТКЕ ===")
        print("1. Добавить клиента")
        print("2. Посмотреть клиентов")
        print("3. Создать заказ")
        print("4. Посмотреть заказы")
        print("5. Изменить статус заказа")
        print("6. Закрыть смену")
        print("7. Выход")

        choice = input_int("Выберите действие: ")

        if choice == 1:
            name = input("Введите имя клиента: ")
            email = input("Введите email: ")
            client_db.add_client(name, email)
            print("Клиент успешно добавлен.")

        elif choice == 2:
            print_clients(client_db)

        elif choice == 3:
            print_clients(client_db)
            client_id = input_int("Введите ID клиента для заказа: ")

            if not client_db.client_exists(client_id):
                print("Клиент не найден!")
                continue

            days = input_int("Сколько дней назад сдали вещи? ")
            emergency = input_int("Заказ срочный? (1 - да, 0 - нет): ")

            catalog = Order.get_catalog()
            print("Доступные вещи: ", end="")
            for item in catalog:
                print(f"[{item}] ", end="")
            print()

            print("Вводите вещи по одной (для завершения введите 'стоп'):")
            valid_items = []
            while True:
                item_input = input()
                if item_input.strip().lower() == "стоп":
                    break
                if not item_input.strip():
                    continue
                if Order.is_valid_item(item_input):
                    valid_items.append(item_input)
                    print(f"Добавлено: {item_input}")
                else:
                    print("Вещи нет в каталоге. Попробуйте снова.")

            if not valid_items:
                print("Заказ не создан: нет вещей.")
            else:
                order_db.add_order(
                    client_id,
                    days,
                    OrderStatus.ACCEPTED,
                    emergency != 0,
                    valid_items,
                )
                print("Заказ успешно создан!")

        elif choice == 4:
            print_orders(order_db)

        elif choice == 5:
            print_orders(order_db)
            order_id = input_int("Введите ID заказа для изменения статуса: ")

            current_order = order_db.get_order_by_id(order_id)
            if current_order.get_id() == 0:
                print("Заказ с таким ID не найден!")
                continue

            print(f"Текущий статус: {Order.status_to_string(current_order.get_status())}")
            print("Выберите новый статус:")
            print("1. Принят")
            print("2. В работе")
            print("3. Готов")
            print("4. Выдан")
            print("5. Отменён")

            status_choice = input_int("Ваш выбор (1-5): ")

            status_map = {
                1: OrderStatus.ACCEPTED,
                2: OrderStatus.IN_PROGRESS,
                3: OrderStatus.READY,
                4: OrderStatus.ISSUED,
                5: OrderStatus.CANCELLED,
            }

            if status_choice not in status_map:
                print("Неверный пункт меню.")
            else:
                new_status = status_map[status_choice]
                order_db.update_order_status(order_id, new_status)
                print(f"Статус заказа изменён на: {Order.status_to_string(new_status)}")

        elif choice == 6:
            order_db.close_shift()
            print("Смена закрыта.")

        elif choice == 7:
            print("Выход из программы. Данные сохранены.")
            break

        else:
            print("Неверный пункт меню. Попробуйте снова.")


if __name__ == "__main__":
    main()