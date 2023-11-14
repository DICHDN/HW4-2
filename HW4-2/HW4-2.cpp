/*
# Задача 2. Сортируем адреса
В этом задании вы будете читать из файла адреса и выводить их в другой файл в другом формате, отсортированными по названию города.

Вам дан файл `in.txt`, в котором находится `N` адресов. Число `N` идёт первым в файле. После числа `N` располагаются `N` блоков по 4 строки в каждом. Каждый блок состоит из следующих строк: название города, название улицы, номер дома, номер квартиры.

Задача программы заключается в том, чтобы считать адреса из файла `in.txt`, отсортировать их по названию города и вывести отсортированный список адресов в файл `out.txt` в другом формате. Не забудьте вывести количество адресов в начале.

Города должны быть отсортированы в алфавитном порядке.

Формат вывода адреса: `<название города>, <название улицы>, <номер дома>, <номер квартиры>`.

### Пример работы программы
#### in.txt
```
5
Москва
Строителей
34
12
Новокузнецк
Науки
5
16
Омск
Пушкина
2
13
Москва
Арбат
4
1
Новосибирск
Мира
85
64
```

#### out.txt
```
5
Москва, Строителей, 34, 12
Москва, Арбат, 4, 1
Новокузнецк, Науки, 5, 16
Новосибирск, Мира, 85, 64
Омск, Пушкина, 2, 13
```

*/

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>


class adress_book
{
private:
    std::string town;
    std::string street;
    int num_house;
    int num_flat;
public:
    adress_book(std::string town, std::string street, int num_house, int num_flat)
    {
        this->town = town;
        this->street = street;
        this->num_house = num_house;
        this->num_flat = num_flat;
    }
    adress_book() {};

    std::string out_adres()
    {
        std::string numHouse, numFlat;
        numHouse = std::to_string(num_house);
        numFlat = std::to_string(num_flat);
        std::string adres_out = town + ", " + street + ", " + numHouse + ", " + numFlat;
        return adres_out;
    }
    std::string show_town()
    {
        return town;
    }
    std::string show_street()
    {
        return street;
    }
};

adress_book* arr_adres(int number)
{
    adress_book* arr = new adress_book[number];
    return arr;
}

void sort_town(adress_book* arr, int size)
{
    for (int i = 0; i+1 < size; ++i)
    {
        for (int j = 0; j+1 < size - i; ++j)
        {
            adress_book adres1 = arr[j], adres2 = arr[j + 1];
            std::string town1 = adres1.show_town(), town2 = adres2.show_town();
            if (town1 > town2) std::swap(arr[j], arr[j + 1]);
        }
    }
}


void sort_street(adress_book* arr, int size)
{
    for (int i = 0; i + 1 < size; ++i)
    {
        for (int j = 0; j + 1 < size - i; ++j)
        {
            adress_book adres1 = arr[j], adres2 = arr[j + 1];
            std::string town1 = adres1.show_town(), town2 = adres2.show_town();
            if (town1 == town2)
            {
                adress_book adres1 = arr[j], adres2 = arr[j + 1];
                std::string street1 = adres1.show_street(), street2 = adres2.show_street();
                if (street1 > street2) std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::ifstream file("in.txt");
    if (file.is_open())
    {
        int number, house, flat;
        std::string size_ar1, field1, field2, field3, field4;
        file >> size_ar1;
        number = std::stoi(size_ar1);
        adress_book* arr_adresses = arr_adres(number);
        for (int i = 0; i < number; ++i)
        {
            file >> field1;
            file >> field2;
            file >> field3;
            file >> field4;
            house = std::stoi(field3);
            flat = std::stoi(field4);
            adress_book adress(field1, field2, house, flat);
            arr_adresses[i] = adress;
        }

        file.close();
        std::ofstream fout("out.txt");
        fout << number;
        fout << std::endl;
        sort_town(arr_adresses, number); //сортируем города
        sort_street(arr_adresses, number); // сортируем улицы

        for (int i = 0; i < number; ++i)
        {
            adress_book adress = arr_adresses[i];
            fout << adress.out_adres();
            fout << std::endl;
        }
        fout.close();
        delete[] arr_adresses;
    }
    else
    {
        std::cout << "Ошибка! Фаил начальных условий не найден! Код ошибки: -1" << std::endl;
        return 0;
    }
    return 0;
}