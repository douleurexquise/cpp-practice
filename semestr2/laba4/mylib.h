#ifndef MYLIB_H
#define MYLIB_H
#include <cstring>
class Airplane {
    private:
    char type[30];      // Наименование типа
    char constructor[30];    // Фамилия конструктора
    int year;               // Год выпуска
    int seats;              // Количество кресел
    double capacity;     // Грузоподъёмность, т
    public:
    Airplane();
    Airplane(const char*,const char*,int,int,double);
    const char* get_type(){
        return type;
      }
    ~Airplane();
    const char* get_constructor(){
        return constructor;
    }
    int get_year(){
        return year;
    }
    int get_seats(){
        return seats;
    }
    double get_capacity(){
        return capacity;
    }
    void set_type(const char* _type){
        strncpy(type, _type, 29);
        type[29] = '\0';
    }
    void set_constructor(const char* _constructor){
        strncpy(constructor, _constructor, 29);
        constructor[29] = '\0';
    }
    void set_year(int _year){
        year = _year;
    }
    void set_seats(int _seats){
        seats = _seats;
    }
    void set_capacity(double _capacity){
        capacity = _capacity;
    }
};

#endif
