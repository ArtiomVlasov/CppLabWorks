#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <tuple>
#include <iostream>
#include <stdexcept>

// Функция для разбора строки с учётом экранирования
void split(const std::string &str, std::vector<std::string> &cont, char delimiter = ',', char escapeChar = '"')
{
    std::stringstream ss;
    bool inQuotes = false;
    cont.clear(); // Очищаем контейнер
    for (char c : str)
    {
        if (c == escapeChar)
        {
            inQuotes = !inQuotes;
        }
        else if (c == delimiter && !inQuotes)
        {
            cont.push_back(ss.str());
            ss.str("");
            ss.clear();
        }
        else
        {
            ss << c;
        }
    }
    cont.push_back(ss.str()); // Добавляем последний токен
    // Отладочный вывод
    std::cout << "Parsed line: " << str << "\nTokens: ";
    for (const auto &token : cont)
    {
        std::cout << "[" << token << "] ";
    }
    std::cout << std::endl;
}

// Чтение элемента из строки в кортеж
template <std::size_t idx, typename... fields>
typename std::enable_if<idx >= std::tuple_size<std::tuple<fields...>>::value>::type
read_elem(std::tuple<fields...> &, const std::vector<std::string> &) {}

template <std::size_t idx, typename... fields>
    typename std::enable_if < idx<std::tuple_size<std::tuple<fields...>>::value>::type
                              read_elem(std::tuple<fields...> &tuple, const std::vector<std::string> &items)
{
    std::stringstream ss(items[idx]);
    ss >> std::get<idx>(tuple);
    if (ss.fail())
    {
        throw std::runtime_error("Failed to parse field at index " + std::to_string(idx));
    }
    read_elem<idx + 1>(tuple, items);
}

template <typename... fields>
void make_tuple(std::tuple<fields...> &tuple, const std::vector<std::string> &items)
{
    if (items.size() != sizeof...(fields))
    {
        throw std::runtime_error("Number of fields does not match tuple size");
    }
    read_elem<0>(tuple, items);
    // Отладочный вывод
    std::cout << "Tuple created: ";
    print_tuple(std::cout, tuple);
    std::cout << std::endl;
}

// CSVParser
template <typename... Args>
class CSVParser
{
private:
    const std::string fname;
    size_t skipLines;
    char delimiter;
    char escapeChar;

public:
    CSVParser(const std::string &f, size_t skip = 0, char delim = ',', char escape = '"')
        : fname(f), skipLines(skip), delimiter(delim), escapeChar(escape) {}

    class iterator
    {
    private:
        std::ifstream ifs;
        size_t index;
        std::tuple<Args...> tuple;
        bool atEnd;
        char delimiter;
        char escapeChar;

    public:
        iterator(const std::string &f, size_t skip, char delim, char escape)
            : index(0), atEnd(false), delimiter(delim), escapeChar(escape)
        {
            ifs.open(f);
            if (!ifs)
            {
                throw std::runtime_error("Unable to open file: " + f);
            }

            // Пропускаем заданное количество строк
            std::string dummy;
            for (size_t i = 0; i < skip; ++i)
            {
                if (!std::getline(ifs, dummy))
                {
                    atEnd = true;
                    return;
                }
            }

            // Читаем первую строку
            ++(*this);
        }

        // Дефолтный конструктор для итератора end()
        iterator() : atEnd(true) {}

        iterator &operator++()
        {
            if (atEnd)
                return *this;

            std::string line;
            if (std::getline(ifs, line))
            {
                std::cout << "Processing line: " << line << std::endl;
                std::vector<std::string> items;
                split(line, items, delimiter, escapeChar);
                make_tuple(tuple, items);
            }
            else
            {
                atEnd = true;
                ifs.close();
            }

            return *this;
        }

        const std::tuple<Args...> &operator*() const
        {
            return tuple;
        }

        bool operator==(const iterator &other) const
        {
            return atEnd == other.atEnd;
        }

        bool operator!=(const iterator &other) const
        {
            return !(*this == other);
        }
    };
    iterator begin() const
    {
        return iterator(fname, skipLines, delimiter, escapeChar);
    }

    iterator end() const
    {
        return iterator(); // Возвращает завершённый итератор
    }
};

// Печать кортежа
template <typename Tuple, size_t... Is>
void print_tuple_impl(std::ostream &os, const Tuple &t, std::index_sequence<Is...>)
{
    ((os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), ...);
}

template <typename... Args>
std::ostream &operator<<(std::ostream &os, const std::tuple<Args...> &t)
{
    os << "(";
    print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
    os << ")";
    return os;
}

int main()
{
    try
    {
        CSVParser<int, std::string, int> parser("/home/archi/coding/CppLabWorks/cpp-template/lab5/testing.csv", 1, ',', '"');
        for (const auto &row : parser)
        {
            std::cout << row << std::endl;
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    return 0;
}
