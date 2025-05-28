#include <string>
#include <iostream>


using std::string;


int main(int argc, char*argv[])
{
    string out = "Hello, ";

    if (argc > 1)
    {
      out += argv[1];
    }
    else
    {
      out += "world";
    }

    std::cout << out << "!\n";

    return 0;
}
