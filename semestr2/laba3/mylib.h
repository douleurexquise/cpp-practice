#ifndef MYLIB_H
#define MYLIB_H
using namespace std;
class Airplane {
    private:
    char type[30];      // Наименование типа
    char constructor[30];    // Фамилия конструктора
    int year;               // Год выпуска
    int seats;              // Количество кресел
    double capacity;     // Грузоподъёмность, т
    public:
    Airplane();
    Airplane(char*,char*,int,int,double);
    void set_type(char* _type){
        type = _type;
    }
    //TODO: ДОПИСАТЬ ГЕТТЕРЫ
    void set_constructor(char* _constructor){
        constructor = _constructor;
    }
    void
};


#endif
