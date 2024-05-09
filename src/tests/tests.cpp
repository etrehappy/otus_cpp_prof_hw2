#include <gtest/gtest.h>
#include "../ip_filter.h"

using vec_strings = std::vector<std::string>;

struct SplitTestF : public testing::Test
{
    //arrange
    vec_strings vector{};
    std::string ip_first_part{"151"};
    std::string ip_second_part{"111"};
    std::string benchmark_ip{ip_first_part+ "." + ip_second_part + ".11.1"};
    std::string full_string{benchmark_ip+"\t222\t3\n"};
    std::vector<vec_strings> ip_pool{};
};

TEST_F(SplitTestF, splite_string)
{
    //arrange       

    //act
    vector = split(full_string, '\t');    

    //assert    
    ASSERT_EQ(vector.at(0), benchmark_ip);
}

TEST_F(SplitTestF, splite_ip)
{
    //arrange       

    //act
    vector = split(full_string, '\t');
    ip_pool.push_back(split(vector.at(0), '.'));

    //assert    
    EXPECT_EQ(ip_pool.at(0).at(0), ip_first_part);
    EXPECT_EQ(ip_pool.at(0).at(1), ip_second_part);
}

TEST_F(SplitTestF, splite_empty_string)
{
    //arrange       
    std::string empty_string{""};
    const size_t expected_size = vector.size();
    //act
    vector = split(empty_string, '\t');

    //assert    
    EXPECT_EQ(vector.size(), expected_size);
}


////////////////////////////////////////////////////////////////////////////////
struct SortTestF : public testing::Test
{
    //arrange      
    const vec_strings vector1{"1", "1", "234", "8"};
    const vec_strings vector2{"222","82","198","61"};
    const vec_strings vector3{"222","173","235","246"};

    std::vector<vec_strings> ip_pool{vector1, vector2, vector3};
};

TEST_F(SortTestF, reverse_lexicographically_sort)
{
    //arrange
    size_t second_part_first_ip{1}, second_part_second_ip{1}, last_part_last_ip{3};

    const auto expected_first_ip = vector3.at(second_part_first_ip);
    const auto expected_second_ip = vector2.at(second_part_second_ip);
    const auto expected_end_ip = vector1.at(last_part_last_ip);

    //act
    SortIp(ip_pool);
    //222.173.235.246   vector3
    //222.82.198.61     vector2
    //1.1.234.8         vector1
    
    //assert    
    EXPECT_EQ(ip_pool.at(0).at(second_part_first_ip), expected_first_ip);
    EXPECT_EQ(ip_pool.at(1).at(second_part_second_ip), expected_second_ip);
    EXPECT_EQ(ip_pool.at(2).at(last_part_last_ip), expected_end_ip);
}

TEST_F(SortTestF, first_filter)
{
    //arrange
    const vec_strings& expected_vector{vector1};
    std::vector<vec_strings>  filtered_vector{};

    //act
    SortIp(ip_pool);    

    std::for_each(ip_pool.begin(), ip_pool.end(), [&filtered_vector](const vec_strings& ip)
        {
            if (IsFirstEqualOne(ip))
            {
                filtered_vector.push_back(ip);
            }

            return;
        });    
    //1.1.234.8         vector1

    const bool result = [&filtered_vector, &expected_vector]() ->bool
        {
            for (size_t i = 0; i < expected_vector.size(); i++)
            {
                if (filtered_vector.back().at(i) != expected_vector.at(i))
                {
                    return false;
                }
            }

            return true;
        }();

    //assert    
    EXPECT_EQ(result, true);
}


int main(int argc, char** argv) 
{      
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
