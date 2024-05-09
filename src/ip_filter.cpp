#include "ip_filter.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

using vec_strings = std::vector<std::string>;

vec_strings split(const std::string &str, char d)
{
    vec_strings r;

    if (str.empty()) 
    {
        return r;
    }

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


void SortIp(std::vector<vec_strings>& ip_pool)
{
    for (int i = static_cast<int>(ip_pool.front().size()) - 1; i >= 0; i--)
    {
        std::stable_sort(ip_pool.begin(), ip_pool.end(),
            [i](const vec_strings& l, const vec_strings& r) {
                return std::stoi(l.at(i)) > std::stoi(r.at(i));
            });
    }
}

bool IsFirstEqualOne(const vec_strings& ip)
{
    return std::stoi(ip.at(0)) == 1;
}

bool IsFirstEqual46AndSecondEqual70(const vec_strings& ip)
{
    return (std::stoi(ip.at(0)) == 46 &&
        std::stoi(ip.at(1)) == 70);
}

bool IsAny46(const vec_strings& ip)
{
    return std::any_of(
        ip.cbegin(), 
        ip.cend(),
        [](const std::string& p) { return std::stoi(p) == 46; });
}

void Print(const vec_strings& ip)
{    
    for (auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part)
    {
        if (ip_part != ip.cbegin())
        {
            std::cout << ".";
        }
        std::cout << *ip_part;
    }
    std::cout << std::endl;     
}

static void FilterAndPrint(const std::vector<vec_strings>& ip_pool, bool (*funcPtr)(const vec_strings&))
{
    std::for_each(ip_pool.begin(), ip_pool.end(), [funcPtr](const vec_strings& ip)
        {
            if (funcPtr(ip))
            {
                Print(ip);
            }
        });
}

void IpFilter()
{
    try
    {
        std::vector<vec_strings > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            vec_strings v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort

        SortIp(ip_pool);

        std::for_each(ip_pool.begin(), ip_pool.end(), Print);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        FilterAndPrint(ip_pool, IsFirstEqualOne);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        FilterAndPrint(ip_pool, IsFirstEqual46AndSecondEqual70);

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        FilterAndPrint(ip_pool, IsAny46);

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
