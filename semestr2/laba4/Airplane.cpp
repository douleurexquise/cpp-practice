#include "Airplane.h"
Airplane::Airplane(){
    year = 0;
    seats = 0;
    capacity = 0.0;
}
Airplane::Airplane(const char* _type, const char* _constructor, int _year, int _seats, double _capacity) {
    set_type(_type);
    set_constructor(_constructor);
    set_year(_year);
    set_seats(_seats);
    set_capacity(_capacity);
}
Airplane::~Airplane(){}
const char* Airplane::get_type() {
    return type.get();
}
const char* Airplane::get_constructor() {
    return constructor.get();
}
int Airplane::get_year() {
    return year;
}
int Airplane::get_seats() {
    return seats;
}
double Airplane::get_capacity() {
    return capacity;
}
void Airplane::set_type(const char* _type) {
    type.set(_type);
}
void Airplane::set_constructor(const char* _constructor) {
    constructor.set(_constructor);
}
void Airplane::set_year(int _year) {
    year = _year;
}
void Airplane::set_seats(int _seats) {
    seats = _seats;
}
void Airplane::set_capacity(double _capacity) {
    capacity = _capacity;
}
