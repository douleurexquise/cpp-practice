#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
private:
    int id;
    std::string name;
    std::string email;
public:
    Client();
    Client(int id, const std::string& name, const std::string& email);

    int getId() const;
    std::string getName() const;
    std::string getEmail() const;
    void setId(int id);
    void setName(const std::string& name);
    void setEmail(const std::string& email);

    std::string toString() const; // переводит данные в формат строки для записи в файл
    static Client fromString(const std::string& line); // распаковывает данные из файла для создания объекта
};

#endif
