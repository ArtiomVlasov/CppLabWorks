#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <tuple>
#include <iostream>
#include <stdexcept>

template <typename T>
T convert(const std::string &str)
{
  T t;
  std::istringstream ss(str);
  ss >> t;
  return t;
}

template <>
std::string convert<std::string>(const std::string &str)
{
  return str;
}

void split(const std::string &str, std::vector<std::string> &cont, char delimiter = ',', char escapeChar = '"')
{
    std::stringstream ss;
    bool saveNext = false;
    cont.clear();
    for (char c : str)
    {
        if (c == escapeChar && !saveNext)
        {
            continue;
        }
        else if (c != escapeChar && saveNext)
        {
            saveNext = false;
            ss << c;
        }
        else if (c == delimiter)
        {
            cont.push_back(ss.str());
            ss.str("");
            ss.clear();
        }
        else if(c == '\\'){
            saveNext = true;
        }
        else
        {
            ss << c;
        }
    }
    cont.push_back(ss.str());
    std::cout;
}

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

            std::string dummy;
            for (size_t i = 0; i < skip; ++i)
            {
                if (!std::getline(ifs, dummy))
                {
                    atEnd = true;
                    return;
                }
            }

            ++(*this);
        }

        iterator() : atEnd(true) {}

        iterator &operator++()
        {
            if (atEnd)
                return *this;

            std::string line;
            if (std::getline(ifs, line))
            {
                std::vector<std::string> items;
                split(line, items, delimiter, escapeChar);
                tuple = createTuple(items, std::index_sequence_for<Args...>());
            }
            else
            {
                atEnd = true;
                ifs.close();
            }

            return *this;
        }

        template <std::size_t... Is>
        std::tuple<Args...> createTuple(const std::vector<std::string> &fields, std::index_sequence<Is...>)
        {
            return std::make_tuple(convert<Args>(fields[Is])...);
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
        return iterator(); 
    }
};


template <typename Tuple, size_t... Is>
void printTupleImpl(std::ostream &os, const Tuple &t, std::index_sequence<Is...>)
{
    ((os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), ...);
}

template <typename... Args>
std::ostream &operator<<(std::ostream &os, const std::tuple<Args...> &t)
{
    os << "(";
    printTupleImpl(os, t, std::index_sequence_for<Args...>{});
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
