#include <gtest/gtest.h>
#include <market.h>

TEST(MarketTest, ReadCsvTest)
{
    std::string path = "./data/test.csv";
    std::vector<TickInfo> expectedTicks = {
        {"2022-01-01", "ABC", 10.0, 12.0, 9.0, 11.0},
        {"2022-01-02", "DEF", 20.0, 22.0, 18.0, 21.0},
        {"2022-01-03", "GHI", 30.0, 32.0, 28.0, 31.0}
    };

    std::vector<TickInfo> actualTicks = read_csv(path);

    ASSERT_EQ(actualTicks.size(), expectedTicks.size());
    for (size_t i = 0; i < actualTicks.size(); ++i)
    {
        ASSERT_EQ(actualTicks[i].date, expectedTicks[i].date);
        ASSERT_EQ(actualTicks[i].code, expectedTicks[i].code);
        ASSERT_EQ(actualTicks[i].open, expectedTicks[i].open);
        ASSERT_EQ(actualTicks[i].high, expectedTicks[i].high);
        ASSERT_EQ(actualTicks[i].low, expectedTicks[i].low);
        ASSERT_EQ(actualTicks[i].close, expectedTicks[i].close);
    }
}

TEST(MarketTest, LoadDataTest)
{
    Market market;
    market.add_code("ABC");
    market.add_code("DEF");
    market.load_data();

    ASSERT_EQ(market.get_pending_ticks("ABC").size(), 3);
    ASSERT_EQ(market.get_pending_ticks("DEF").size(), 3);
    // Add more assertions if needed
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}#include <gtest/gtest.h>
#include <market.h>

TEST(MarketTest, ReadCsvTest)
{
    std::string path = "./data/test.csv";
    std::vector<TickInfo> expectedTicks = {
        {"2022-01-01", "ABC", 10.0, 12.0, 9.0, 11.0},
        {"2022-01-02", "DEF", 20.0, 22.0, 18.0, 21.0},
        {"2022-01-03", "GHI", 30.0, 32.0, 28.0, 31.0}
    };

    std::vector<TickInfo> actualTicks = read_csv(path);

    ASSERT_EQ(actualTicks.size(), expectedTicks.size());
    for (size_t i = 0; i < actualTicks.size(); ++i)
    {
        ASSERT_EQ(actualTicks[i].date, expectedTicks[i].date);
        ASSERT_EQ(actualTicks[i].code, expectedTicks[i].code);
        ASSERT_EQ(actualTicks[i].open, expectedTicks[i].open);
        ASSERT_EQ(actualTicks[i].high, expectedTicks[i].high);
        ASSERT_EQ(actualTicks[i].low, expectedTicks[i].low);
        ASSERT_EQ(actualTicks[i].close, expectedTicks[i].close);
    }
}

TEST(MarketTest, LoadDataTest)
{
    Market market;
    market.add_code("ABC");
    market.add_code("DEF");
    market.load_data();

    ASSERT_EQ(market.get_pending_ticks("ABC").size(), 3);
    ASSERT_EQ(market.get_pending_ticks("DEF").size(), 3);
    // Add more assertions if needed
}

TEST(MarketTest, LoadDataTestWithInvalidCode)
{
    Market market;
    market.add_code("XYZ"); // Invalid code
    market.load_data();

    ASSERT_EQ(market.get_pending_ticks("XYZ").size(), 0);
    // Add more assertions if needed
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}