#include <vector>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <cmath>

typedef unsigned long long ull;

template <class T>
class BinHeap {
public:
    BinHeap();

    ~BinHeap();

    BinHeap(const BinHeap& heap_obj);

    BinHeap& operator=(const BinHeap& heap_obj);

    void Add(T key);

    T PopTop();

    T& GetTop();

    bool Empty() const;

private:
    T *buffer;
    int buffer_size;
    int size;

    void SiftUp(int index);

    void SiftDown(int index);
};

// Puzzle State
struct State {

    ull code; // Board encoding : 'board' --> ull
    int zero_place;
    ull turns;
    ull heuristic; // Heuristic potential for the state
    std::vector<char> path;

    State();

    ~State();
    State(const State& state);
    State& operator=(const State& state);

    bool operator>(const State& state);

    bool Solvable() const;

    void Set(int index, ull value);

    int Get(int index) const;

    // Move gap (yeah, turns' letters are inversed)
    State SlideUp() const;

    State SlideDown() const;

    State SlideRight() const;

    State SlideLeft() const;

    // Count Heuristic
    int Heuristic() const;

    const ull masks[16] = {0x000000000000000F,
                           0x00000000000000F0,
                           0x0000000000000F00,
                           0x000000000000F000,
                           0x00000000000F0000,
                           0x0000000000F00000,
                           0x000000000F000000,
                           0x00000000F0000000,
                           0x0000000F00000000,
                           0x000000F000000000,
                           0x00000F0000000000,
                           0x0000F00000000000,
                           0x000F000000000000,
                           0x00F0000000000000,
                           0x0F00000000000000,
                           0xF000000000000000};

    const ull inverse_masks[16] = {0xFFFFFFFFFFFFFFF0,
                                   0xFFFFFFFFFFFFFF0F,
                                   0xFFFFFFFFFFFFF0FF,
                                   0xFFFFFFFFFFFF0FFF,
                                   0xFFFFFFFFFFF0FFFF,
                                   0xFFFFFFFFFF0FFFFF,
                                   0xFFFFFFFFF0FFFFFF,
                                   0xFFFFFFFF0FFFFFFF,
                                   0xFFFFFFF0FFFFFFFF,
                                   0xFFFFFF0FFFFFFFFF,
                                   0xFFFFF0FFFFFFFFFF,
                                   0xFFFF0FFFFFFFFFFF,
                                   0xFFF0FFFFFFFFFFFF,
                                   0xFF0FFFFFFFFFFFFF,
                                   0xF0FFFFFFFFFFFFFF,
                                   0x0FFFFFFFFFFFFFFF};
};

// State comparator for priority_queue
struct StateCmp {
    bool operator()(const State& first, const State& second) {
        return first.heuristic > second.heuristic;
    }
};

// Puzzle solver
class Solver {
public:

    Solver(const State& state);

    void Solve();

private:
    State init_state;
    State final_state;
    std::vector<char> turns_seq;

    std::priority_queue<State, std::vector<State>, StateCmp> states;
    std::unordered_set<ull> used;

    // Processing and adding state into the priority_queue in A*
    bool Use(const State& state);
};

//===============================//===============================//===============================//

int main(int argc, char** argv) {
    State state;
    int chip;

    // Initializing start state
    for (int i = 0; i < 16; i++) {
        std::cin >> chip;
        if (chip == 0) {
            state.zero_place = i;
        }
        state.Set(i, chip);
    }
    state.heuristic = state.Heuristic();

    if (!state.Solvable()) {
        std::cout << -1;
    }
    else {
        Solver solver(state);
        solver.Solve();
    }

    return 0;
}

//===============================//===============================//===============================//


State::State() : code(0), turns(0) {}

State::~State() {}

State::State(const State& state) : code(state.code),
                                    turns(state.turns),
                                    heuristic(state.heuristic),
                                    path(state.path),
                                    zero_place(state.zero_place) {}

State& State::operator=(const State& state) {
    code = state.code;
    turns = state.turns;
    heuristic = state.heuristic;
    path = state.path;
    zero_place = state.zero_place;

    return *this;
}

bool State::operator>(const State& state) {
    return code > state.code;
}

void State::Set(int index, ull value) {
    code = (code & inverse_masks[index]) | (value << (index << 2));
}

int State::Get(int index) const {
    return (code & masks[index]) >> (index << 2);
}

bool State::Solvable() const {
    int N = 0;

    for (int i = 0; i < 16; i++) {
        int i_chip = Get(i);
        if (i_chip == 0) {
            continue;
        }

        for (int j = i + 1; j < 16; j++) {
            int j_chip = Get(j);
            if (j_chip != 0 && i_chip > j_chip) {
                ++N;
            }
        }
    }

    return (N % 2 == 0) == (zero_place / 4 % 2 == 1);
}

State State::SlideUp() const {
    State new_state(*this);

    int chip_index = zero_place - 4;
    int chip = Get(chip_index);

    new_state.Set(zero_place, chip);
    new_state.Set(chip_index, 0);

    new_state.zero_place = chip_index;
    new_state.heuristic = new_state.Heuristic();
    ++new_state.turns;
    new_state.path.push_back('D');

    return new_state;
}

State State::SlideDown() const {
    State new_state(*this);

    int chip_index = zero_place + 4;
    int chip = Get(chip_index);

    new_state.Set(zero_place, chip);
    new_state.Set(chip_index, 0);

    new_state.zero_place = chip_index;
    new_state.heuristic = new_state.Heuristic();
    ++new_state.turns;
    new_state.path.push_back('U');

    return new_state;
}

State State::SlideRight() const {
    State new_state(*this);

    int chip_index = zero_place + 1;
    int chip = Get(chip_index);

    new_state.Set(zero_place, chip);
    new_state.Set(chip_index, 0);

    new_state.zero_place = chip_index;
    new_state.heuristic = new_state.Heuristic();
    ++new_state.turns;
    new_state.path.push_back('L');

    return new_state;
}

State State::SlideLeft() const {
    State new_state(*this);

    int chip_index = zero_place - 1;
    int chip = Get(chip_index);

    new_state.Set(zero_place, chip);
    new_state.Set(chip_index, 0);

    new_state.zero_place = chip_index;
    new_state.heuristic = new_state.Heuristic();
    ++new_state.turns;
    new_state.path.push_back('R');

    return new_state;
}

int State::Heuristic() const {
    //  Manhattan distances
    int distance = 0;
    for (int i = 0; i < 16; i++) {
        int i_chip = Get(i);

        if (i_chip == 0) {
            continue;
        }

        distance += std::abs((i_chip - 1) % 4 - i % 4) + std::abs((i_chip - 1) / 4 - i / 4);
    }

    return distance * 17 + turns * 10;
}

Solver::Solver(const State& state) : init_state(state) {
    for (int i = 0; i < 16; i++) {
        final_state.Set(i, (i == 15 ? 0 : i + 1));
    }
}

void Solver::Solve() {
    // A* algorithm
    used.clear();

    states.push(init_state);
    used.insert(init_state.code);

    while (!states.empty()) {
        State curr_state = states.top();
        states.pop();

        if (curr_state.zero_place >= 4) {
            if (Use(curr_state.SlideUp())) {
                break;
            }
        }
        if (curr_state.zero_place <= 11) {
            if (Use(curr_state.SlideDown())) {
                break;
            }
        }
        if (curr_state.zero_place % 4 != 3) {
            if (Use(curr_state.SlideRight())) {
                break;
            }
        }
        if (curr_state.zero_place % 4 != 0) {
            if (Use(curr_state.SlideLeft())) {
                break;
            }
        }
    }

    std::cout << turns_seq.size() << "\n";
    for (auto turn : turns_seq) {
        std::cout << turn;
    }
}

bool Solver::Use(const State& state) {
    if (used.find(state.code) == used.end()) {
        if (state.code == final_state.code) {
            turns_seq = state.path;
            return true;
        }

        used.insert(state.code);
        states.push(state);
    }

    return false;
}

//===============================//===============================//===============================//

template <class T>
BinHeap<T>::BinHeap() : buffer_size(1), size(0) {
    buffer = new T[buffer_size];
}

template <class T>
BinHeap<T>::~BinHeap() {
    delete[] buffer;
}

template <class T>
BinHeap<T>::BinHeap(const BinHeap& heap_obj) {
    size = heap_obj.size;
    buffer_size = heap_obj.buffer_size;

    buffer = new T[buffer_size];
    for (int i = 0; i < size; ++i) {
        buffer[i] = heap_obj.buffer[i];
    }
}

template <class T>
BinHeap<T>& BinHeap<T>::operator=(const BinHeap& heap_obj) {
    size = heap_obj.size;
    buffer_size = heap_obj.buffer_size;

    buffer = new T[buffer_size];
    for (int i = 0; i < size; ++i) {
        buffer[i] = heap_obj.buffer[i];
    }

    return *this;
}

template <class T>
void BinHeap<T>::Add(T key){
    if (size == buffer_size) {
        T *tmp_buffer = new T[buffer_size * 2];
        
        for (int i = 0; i < size; ++i) {
            tmp_buffer[i] = buffer[i];
        }

        buffer_size *= 2;
        delete[] buffer;
        buffer = tmp_buffer;
    }

    buffer[size] = key;
    ++size;
    SiftUp(size - 1);
}

template <class T>
T BinHeap<T>::PopTop() {
    T result = buffer[0];
    buffer[0] = buffer[size - 1];
    --size;

    if (size * 2 == buffer_size) {
        T *tmp_buffer = new T[size];
        
        for (int i = 0; i < size; ++i) {
            tmp_buffer[i] = buffer[i];
        }

        buffer_size = size;
        delete[] buffer;
        buffer = tmp_buffer;
    }
    
    SiftDown(0);
    return result;
}

template <class T>
T& BinHeap<T>::GetTop() {
    return buffer[0];
}

template <class T>
bool BinHeap<T>::Empty() const {
    return size == 0;
}

template <class T>
void BinHeap<T>::SiftUp(int index) {
    while (index != 0 && buffer[index] > buffer[(index - 1) / 2]) {
        std::swap(buffer[index], buffer[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

template <class T>
void BinHeap<T>::SiftDown(int index) {
    while (index < size) {
        int largest = index;

        if (index * 2 + 1 < size && buffer[index * 2 + 1] > buffer[largest]) {
            largest = index * 2 + 1;
        }
        if (index * 2 + 2 < size && buffer[index * 2 + 2] > buffer[largest]) {
            largest = index * 2 + 2;
        }

        if (largest != index) {
            std::swap(buffer[index], buffer[largest]);
        }
        else {
            break;
        }

        index = largest;
    }
}