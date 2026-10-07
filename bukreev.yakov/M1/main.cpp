#include <iostream>

namespace bukreev
{
    void parseArgs(int argc, char* argv[], size_t& threads, size_t& tries, size_t& seed);
}

int main(int argc, char* argv[])
{
    size_t threads, tries, seed;
    try
    {
        bukreev::parseArgs(argc, argv, threads, tries, seed);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

void bukreev::parseArgs(int argc, char* argv[], size_t& threads, size_t& tries, size_t& seed)
{
    if (argc != 3 && argc != 4)
    {
        throw std::logic_error("Invalid number of arguments");
    }

    int ithreads = std::atoi(argv[1]);
    if (ithreads < 0)
    {
        throw std::logic_error("Negative threads number");
    }

    int itries = std::atoi(argv[2]);
    if (itries <= 0)
    {
        throw std::logic_error("Negative tries number");
    }

    int iseed = 0;
    if (argc == 4)
    {
        iseed = std::atoi(argv[3]);
        if (iseed < 0)
        {
            throw std::logic_error("Negative generator seed");
        }
    }

    threads = ithreads;
    tries = itries;
    seed = iseed;
}
