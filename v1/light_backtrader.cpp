#include <iostream>
#include <vector>
#include <cmath>

// 单品种股票，移动平均策略

double Rf = 0.005;  // 假设无风险利率为0.5%

class Portfolio{
public:
    int get_current_funds(){ return _current_funds; }
    int get_position(){ return _position; }
    const std::vector<double>& get_daily_prices() const { return _daily_prices; }

    void add_daily_price(const double& price){ _daily_prices.push_back(price); }

    int set_current_funds(const int& funds){ _current_funds = funds; }
    int set_position(const int& position){ _position = position; }

    void on_day(const double& price){
        add_daily_price(price);
    }

private:
    int _current_funds = 10000;
    int _position = 0;
    std::vector<double> _daily_prices;
};

// 策略类
class Strategy{
public:
    Portfolio& portfolio;

    Strategy(Portfolio& portfolio): portfolio(portfolio){}
    ~Strategy(){}

    virtual void on_day(const double& price) = 0;

    void buy(int nums, double price){
        int current_funds = portfolio.get_current_funds();
        if(current_funds >= nums * price){
            current_funds -= nums * price;
            portfolio.set_current_funds(current_funds);
            portfolio.set_position(portfolio.get_position() + nums);
            std::cout << "buy " << nums << " at " << price << std::endl;
        }
        else{
            std::cout << "not enough funds" << std::endl;
        }
    }

    void sell(int nums, double price){
        if(portfolio.get_position() >= nums){
            portfolio.set_current_funds(portfolio.get_current_funds() + nums * price);
            portfolio.set_position(portfolio.get_position() - nums);
            std::cout << "sell " << nums << " at " << price << std::endl;
        }
        else{
            portfolio.set_current_funds(portfolio.get_current_funds() + portfolio.get_position() * price);
            
            int position = portfolio.get_position();
            std::cout << "not enough position, sell all position" << std::endl;
            if(position > 0){
                std::cout << "sell " << position << " at " << price << std::endl;
            }

            portfolio.set_position(0);
        }
    }
};

// 简单移动平均类
class MovingAvgStra : public Strategy{
public:
    std::vector<double> moving_avg_prices;
    int window_size;

    MovingAvgStra(Portfolio& portfolio, int size) : Strategy(portfolio){
        window_size = size;
    }

    ~MovingAvgStra(){}

    void cal_moving_avg_prices(const double& price){
        if(moving_avg_prices.size() < window_size){
            moving_avg_prices.push_back(price);
        }
        else{
            double sum = 0;
            const std::vector<double>& daily_prices = portfolio.get_daily_prices();
            for(int i = daily_prices.size() - window_size; i < daily_prices.size(); i++){
                sum += daily_prices[i];
            }
            moving_avg_prices.push_back(sum/window_size);
        }
        std::cout << "current price: " << price << std::endl;
        std::cout << "current moving avg price: " << moving_avg_prices.back() << std::endl;
    }

    void on_day(const double& price) override{
        cal_moving_avg_prices(price);
        if(price > moving_avg_prices.back()){
            buy(1, price);
        }
        else{
            sell(1, price);
        }


    }
};

// 统计模块
class Statistics{
public:
    Portfolio& portfolio;
    std::vector<double> daily_returns;
    std::vector<double> daily_sharpe;
    double stra_return;
    double stra_sharpe;

    Statistics(Portfolio& portfolio) : portfolio(portfolio){}
    ~Statistics(){}

    void cal_daily_returns(){
        if (daily_returns.size() == 0){
            daily_returns.push_back(0);
        }
        else{
            double today_prices = portfolio.get_daily_prices().back();
            double yesterday_prices = portfolio.get_daily_prices()[portfolio.get_daily_prices().size() - 2];
            daily_returns.push_back(today_prices / yesterday_prices - 1);
        }
    }

    void cal_stra_return(){
        if(daily_returns.size() == 0){
            stra_return = 0;
        }
        else{
            double sum = 0;
            for(int i = 0; i < daily_returns.size(); i++){
                sum += daily_returns[i];
            }
            stra_return = sum / daily_returns.size();
        }
    }

    void cal_daily_sharpe(){
        if(daily_returns.size() == 0){
            daily_sharpe.push_back(0);
        }
        else{
            double sum = 0;
            for(int i = 0; i < daily_returns.size(); i++){
                sum += daily_returns[i];
            }
            double mean = sum / daily_returns.size();

            double variance = 0;
            for(int i = 0; i < daily_returns.size(); i++){
                variance += (daily_returns[i] - mean) * (daily_returns[i] - mean);
            }
            double std = std::sqrt(variance / daily_returns.size()); // risk

            daily_sharpe.push_back((mean - Rf) / std);
        }
    }

    void cal_stra_sharpe(){
        stra_sharpe = daily_sharpe.back();
    }

    void on_day(const double price){
        cal_daily_returns();
        cal_daily_sharpe();
    }
};

int main(){
    Portfolio portfolio;
    MovingAvgStra moving_avg_stra(portfolio, 10);
    Statistics statistics(portfolio);

    std::vector<double> prices = {
        18.88, 18.95, 19.02, 19.10, 19.25,
        19.75, 17.82, 14.90, 15.00, 16.10,
        17.34, 18.26, 19.45, 18.60, 17.72, 
        16.36, 17.45, 18.52, 19.60, 18.68,
        17.50, 16.40, 17.50, 18.60, 19.70,
        18.50, 17.40, 18.50, 19.60, 20.70
    };

    for(int i = 0; i < prices.size(); i++){
        portfolio.on_day(prices[i]);
        moving_avg_stra.on_day(prices[i]);
        statistics.on_day(prices[i]);
    }

    std::cout << "current funds: " << portfolio.get_current_funds() << std::endl;
    std::cout << "current position: " << portfolio.get_position() << std::endl;
    std::cout << "current price: " << prices.back() << std::endl;
    std::cout << "current value: " << portfolio.get_current_funds() + portfolio.get_position() * prices.back() << std::endl;
    std::cout << "return: " << statistics.stra_return << std::endl;
    std::cout << "sharpe: " << statistics.stra_sharpe << std::endl;


    return 0;
}