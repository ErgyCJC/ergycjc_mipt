// Задача C 'Восьминашки'
// Contest link: https://contest.yandex.ru/contest/12173/problems/C/
//
// Во входном файле содержится начальная конфигурация головоломки – 3 строки по 3 числа в каждой.
// Если решение существует, то в первой строке выходного файла выведите минимальное число перемещений костяшек,
// которое нужно сделать, чтобы достичь выигрышной конфигурации,
// а во второй строке выведите соответствующую последовательность ходов: L означает, что в результате перемещения костяшки
// пустая ячейка сдвинулась влево, R – вправо, U – вверх, D – вниз. Если таких последовательностей несколько, то выведите любую из них.
// Если же выигрышная конфигурация недостижима, то выведите в выходной файл одно число −1.

#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <set>

//===================================//===================================//===================================//

typedef unsigned long long ull;

struct State {
    ull code;
    int zero_place;
    std::vector<char> path;

    State();

    ~State();
    State(const State& _state);
    State& operator=(const State& _state);

    // Is it possible to win with the board configuration
    bool Solvable() const;

    // Set chip value by index from 0 to 8
    void Set(int index, ull value);
    
    // Get chip value by index
    int Get(int index) const;

    // Sliding zero-chip
    State SlideZeroUp() const;
    State SlideZeroDown() const;
    State SlideZeroRight() const;
    State SlideZeroLeft() const;

    const ull masks[9] = {0x00000000F,
                        0x0000000F0,
                        0x000000F00,
                        0x00000F000,
                        0x0000F0000,
                        0x000F00000,
                        0x00F000000,
                        0x0F0000000,
                        0xF00000000};

    const ull inverse_masks[9] = {0xFFFFFFFF0,
                                0xFFFFFFF0F,
                                0xFFFFFF0FF,
                                0xFFFFF0FFF,
                                0xFFFF0FFFF,
                                0xFFF0FFFFF,
                                0xFF0FFFFFF,
                                0xF0FFFFFFF,
                                0x0FFFFFFFF};
};

class Solver {
public:
    Solver(const State& state);

    // BFS-based solving puzzle
    void Solve(std::ostream& out);

    // Add state into queue if it is correct operation
    void Use(const State& state);

private:
    State init_state;

    // Turns sequence for printing
    std::vector<char> turns;

    std::queue<State> states;
    std::set<ull> visited;
};

//===================================//===================================//===================================//

int main(int argc, char** argv) {
    std::ifstream fin("puzzle.in");
    std::ofstream fout("puzzle.out");
    
    State state;
    int chip;

    for (int i = 0; i < 9; ++i) {
        fin >> chip;
        state.Set(i, chip);

        if (chip == 0) {
            state.zero_place = i;
        }
    }

    Solver solver(state);
    solver.Solve(fout);

    fin.close();
    fout.close();
    return 0;
}

//===================================//===================================//===================================//

State::State() : code(0), zero_place(0) {}

State::~State() {}
    
State::State(const State& _state) : code(_state.code), zero_place(_state.zero_place), path(_state.path) {}

State& State::operator=(const State& _state) {
    zero_place = _state.zero_place;
    code = _state.code;
    path = _state.path;
    
    return *this;
}

void State::Set(int index, ull value) {
    code = (code & inverse_masks[index]) | (value << (index << 2));
}

int State::Get(int index) const {
    return static_cast<int>((code & masks[index]) >> (index << 2));
}

State State::SlideZeroUp() const {
    State new_state(*this);

    int chip_index = zero_place - 3;
    int chip = Get(chip_index);
    new_state.Set(zero_place, chip);

    new_state.Set(chip_index, 0);
    new_state.zero_place = chip_index;

    new_state.path.push_back('U');

    return new_state;
}

State State::SlideZeroDown() const {
    State new_state(*this);

    int chip_index = zero_place + 3;
    int chip = Get(chip_index);
    new_state.Set(zero_place, chip);

    new_state.Set(chip_index, 0);
    new_state.zero_place = chip_index;

    new_state.path.push_back('D');

    return new_state;
}

State State::SlideZeroRight() const {
    State new_state(*this);

    int chip_index = zero_place + 1;
    int chip = Get(chip_index);
    new_state.Set(zero_place, chip);

    new_state.Set(chip_index, 0);
    new_state.zero_place = chip_index;

    new_state.path.push_back('R');

    return new_state;
}

State State::SlideZeroLeft() const {
    State new_state(*this);

    int chip_index = zero_place - 1;
    int chip = Get(chip_index);
    new_state.Set(zero_place, chip);

    new_state.Set(chip_index, 0);
    new_state.zero_place = chip_index;

    new_state.path.push_back('L');

    return new_state;
}

bool State::Solvable() const {
    int N = 0;

    for (int i = 0; i < 9; ++i) {
        int i_chip = Get(i);
        if (i_chip == 0) {
            continue;
        }

        for (int j = i + 1; j < 9; ++j) {
            if (Get(j) != 0 && Get(j) < i_chip) {
                N += 1;
            }
        }
    }

    return N % 2 == 0;
}

Solver::Solver(const State& state) : init_state(state) {}

void Solver::Solve(std::ostream& out) {
    if (!init_state.Solvable()) {
        out << -1;
        return;
    }

    // Target state for comparing
    State cmp_state;
    cmp_state.Set(8, 0);
    cmp_state.zero_place = 8;
    for (int i = 0; i < 8; ++i) {
        cmp_state.Set(i, i+1);
    }

    // BFS initializing
    visited.clear();
    visited.insert(init_state.code);
    states.push(init_state);

    // BFS
    State curr_state;
    
    while (!states.empty()) {
        curr_state = states.front();
        states.pop();

        if (curr_state.code ==  cmp_state.code) {
            turns = curr_state.path;
            break;
        }

        // For possible next states
        if (curr_state.zero_place >= 3) {
            Use(curr_state.SlideZeroUp());
        }
        if (curr_state.zero_place <= 5) {
            Use(curr_state.SlideZeroDown());
        }
        if (curr_state.zero_place % 3 != 0) {
            Use(curr_state.SlideZeroLeft());
        }
        if (curr_state.zero_place % 3 != 2) {
            Use(curr_state.SlideZeroRight());
        }
    }

    out << turns.size() << "\n";
    for (auto chip : turns) {
        out << chip;
    }
}

void Solver::Use(const State& state) {
    if (visited.find(state.code) == visited.end()) {
        visited.insert(state.code);
        states.push(state);
    }
}