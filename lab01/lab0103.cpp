#include <iostream>
#include <random>
#include <omp.h>
#include <cstdio>
#include <locale>

using namespace std;

constexpr double SIMULATION_TIME = 5.0 * 365.0 * 24.0;
constexpr double ARRIVAL_MIN = 15.0;
constexpr double ARRIVAL_MAX = 45.0;
constexpr double SERVICE_MIN = 4.0;
constexpr double SERVICE_MAX = 44.0;
constexpr double WAIT_COST_PER_HOUR = 1000.0;
constexpr double EXPANSION_COST = 13'500'000.0;
constexpr int SIMULATION_COUNT = 10000;

double simulateOneRun();

int main() {
    setlocale(LC_ALL, "");

    double totalSumWaitingCost = 0.0;
    long totalCountExceed = 0;
#pragma omp parallel for reduction(+:totalSumWaitingCost) reduction(+:totalCountExceed)
    for (int i = 0; i < SIMULATION_COUNT; ++i) {
        double cost = simulateOneRun();
        totalSumWaitingCost += cost;
        if (cost > EXPANSION_COST) {
            totalCountExceed++;
        }
    }

    double avgWaitingCost = totalSumWaitingCost / SIMULATION_COUNT;
    double probabilityExceed = static_cast<double>(totalCountExceed) / SIMULATION_COUNT;

    printf("基于模拟的码头运营结果：\n");
    printf("在未来5年内，平均等待成本为：%.2f 元\n", avgWaitingCost);
    printf("等待成本超过扩建费用 (%.0f 元) 的概率为：%.2f%%\n", EXPANSION_COST, probabilityExceed * 100.0);
    printf("\n");

    if (avgWaitingCost > EXPANSION_COST) {
        printf("建议——扩建码头：预计未来5年的等待成本超过扩建费用。\n");
    } else {
        printf("建议——不扩建码头：预计未来5年的等待成本低于扩建费用。\n");
    }

    if (probabilityExceed > 0.5) {
        printf("另外，超过50%%的模拟结果显示等待成本超过扩建费用，可以考虑扩建。\n");
    } else {
        printf("另外，超过50%%的模拟结果显示等待成本低于扩建费用，不建议扩建。\n");
    }

    return 0;
}

double simulateOneRun() {
    random_device rd;
    seed_seq ss{rd(), rd(), rd(), rd(), static_cast<unsigned int>(omp_get_thread_num()), static_cast<unsigned int>(omp_get_wtime()*1000)};
    mt19937 rand_engine(ss);
    uniform_real_distribution<double> arrival_dist(ARRIVAL_MIN, ARRIVAL_MAX);
    uniform_real_distribution<double> service_dist(SERVICE_MIN, SERVICE_MAX);

    double lastDepartureTime = 0.0;
    double totalWaitingCost = 0.0;
    double currentArrivalTime = 0.0;
    while (currentArrivalTime < SIMULATION_TIME) {
        double serviceStartTime = max(currentArrivalTime, lastDepartureTime);
        double waitingTime = serviceStartTime - currentArrivalTime;
        totalWaitingCost += waitingTime * WAIT_COST_PER_HOUR;
        double serviceTime = service_dist(rand_engine);
        double departureTime = serviceStartTime + serviceTime;
        lastDepartureTime = departureTime;
        double interArrivalTime = arrival_dist(rand_engine);
        currentArrivalTime += interArrivalTime;
    }

    return totalWaitingCost;
}