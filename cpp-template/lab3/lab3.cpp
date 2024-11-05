class cell
{
private:
    bool state;
public:
    cell():state(false){};
    void killCell();
    void beginLife();
    ~cell();
};

class table
{
private:
    cell **map;
public:
    table();
    ~table();
};

table::table(/* args */)
{
}

table::~table()
{
}


cell::cell(/* args */)
{
}

cell::~cell()
{
}


int main(int argc, char const *argv[])
{
    
    return 0;
}