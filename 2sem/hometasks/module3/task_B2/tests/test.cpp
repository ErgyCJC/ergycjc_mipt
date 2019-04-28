#include "test.h"

double GetNormDistributionDouble(std::mt19937& gen, std::normal_distribution<double> distribution) {
    double result = -1.0;
    
    do {
        result = distribution(gen);
    } while(result < 0.000001 || result > 2.0);

    return result;
}

void test_salesman(int vertices_count) {
    Graph graph(vertices_count);

    std::random_device randomDevice;
    std::mt19937 randomGen(randomDevice());
    std::normal_distribution<double> distribution(1, 1);

    std::ofstream fout;
    fout.open("results.log", std::ios::app);

    for (int i = 0; i < vertices_count; ++i) {
        for (int j = 0; j < vertices_count; ++j) {
            if (i == j) {
                continue;
            }
            else {
                graph.InsertEdge(i, j, GetNormDistributionDouble(randomGen, distribution));
            }
        }
    }
    
    auto t_start = std::chrono::high_resolution_clock::now();

    SalesmanSolver solver(graph);
    double salesman_cost = solver.FindPathCost();

    auto t_middle = std::chrono::high_resolution_clock::now();
    double solving_time = std::chrono::duration<double, std::milli>(t_middle - t_start).count();

    ExhaustiveSolver exhaustive_solver(graph);
    double exhaustive_salesman_cost = exhaustive_solver.FindPathCost();

    auto t_end = std::chrono::high_resolution_clock::now();
    double accurate_solving_time = std::chrono::duration<double, std::milli>(t_end - t_middle).count();

    fout << "Vertices count: " << graph.VCount() << "\n";
    fout << "Approximated path cost: " << salesman_cost << "\n" <<
        "Estimated time: " << solving_time << " ms\n";
    fout << "Accurate path cost: " << exhaustive_salesman_cost << "\n" <<
        "Estimated time: " << accurate_solving_time << " ms\n";
    fout << "\n";

    fout.close();
}

void test_range(int lower_border, int upper_border) {
    for (int vertices_count = lower_border; vertices_count <= upper_border; ++vertices_count) {
        test_salesman(vertices_count);
    }
}