#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <future>
#include <condition_variable>
#include <string>

#include "Instrument.hpp"
#include "Stock.hpp"
#include "MarketScenario.hpp"
#include "Portfolio.hpp"
#include "Task.hpp"
#include "JobQueue.hpp"


double worker(JobQueue& jq, Portfolio& portfolio) {
    while (true) {
        Task t = jq.pop_task();
        if (t.done) {
            return 0;
        }
        double result = portfolio.compute_future_profit(t.scenario);
        return result;
    }
}

int main() {

    // creating example instruments and adding them to the portfolio
    std::unordered_map<std::shared_ptr<Instrument>, int> instruments_map;
    std::shared_ptr<Instrument> stock_1 = std::make_shared<Stock>("Stock1", 100);
    std::shared_ptr<Instrument> stock_2 = std::make_shared<Stock>("Stock2", 200);
    std::shared_ptr<Instrument> stock_3 = std::make_shared<Stock>("Stock3", 300);
    instruments_map[stock_1] = 12;
    instruments_map[stock_2] = 24;
    instruments_map[stock_3] = 36;

    Portfolio portfolio(instruments_map);

    int tcount = std::thread::hardware_concurrency();
    std::vector<std::future<double>> workers;
    std::vector<double> results;
    JobQueue jobQ;
    std::random_device dev;
    std::mt19937 rng(dev());

    int number_of_scenarios = 8; // Number of market scenarios to simulate

    // Create tasks and add them to the job queue
    for (int i = 0; i < number_of_scenarios; i++) {
        Task t(rng, portfolio);
        jobQ.add_task(t);
    }
    
    // Create workers and assign them to process tasks from the job queue
    for (int i = 0; i < tcount; i++) {
        workers.emplace_back(std::async(std::launch::async, worker, std::ref(jobQ), std::ref(portfolio)));
    }

    // collect results from workers
    for (auto& w : workers) {
        results.push_back(w.get());
    }

    // terminate workers by adding done tasks to the job queue
    for (int i = 0; i < tcount; i++) {
        Task t(rng, portfolio);
        t.done = true;
        jobQ.add_task(t);
    }

    for (auto r : results) {
        std::cout << "Result: " << r << std::endl;
    }
    return 0;
}