#include <random>
#include <iostream>
#include <sstream>
 
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "---->> First Run <<----" << std::endl;

    for(int n=0; n<3; ++n) 
    {
        std::cout << std::generate_canonical<double, 36>(gen) << ' ';
    }

    std::cout << std::endl;
    std::cout << "---->> Second Run <<----" << std::endl;

    for (int i = 0; i < 3; ++i)
    {
        int digit = rand() % 10;
        std::cout << digit << ' ';
    }

    std::cout << std::endl;
    std::cout << "---->> Third Run <<----" << std::endl;

    std::random_device r;
    std::uniform_int_distribution<long long> idgen(0LL, 99999999999LL);

    std::ostringstream o;
    o << "-WW1000-";
    o.fill('0');    
    o.width(12);
    o << idgen(gen);

    std::string id = o.str();

    std::cout << id << std::endl;

    std::cout << std::endl;
    std::cout << "---->> Fourth Run <<----" << std::endl;

    for (int i = 0; i < 3; ++i)
    {
        std::cout << idgen(gen) << ' ';
    }

}
