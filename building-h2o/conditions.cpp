
#include <condition_variable>
#include <functional>
#include <thread>

class H2O {
    std::mutex mutex;  // protects all data members
    std::condition_variable hydrogens;  // queued hydrogen threads
    int numWaitingHydrogens;  // how many queued
    int numFreeHydrogens;  // how many can go to the output now
    std::condition_variable oxygens;  // queued oxygen threads
    int numWaitingOxygens;  // how many queued

public:
    H2O() 
    : numWaitingHydrogens()
    , numFreeHydrogens()
    , numWaitingOxygens()
    {}

    void oxygen(std::function<void()> releaseOxygen) {
        std::unique_lock<std::mutex> lock(mutex);

        while (numWaitingHydrogens < 2 || numFreeHydrogens > 0) {
            ++numWaitingOxygens;
            oxygens.wait(lock);
            --numWaitingOxygens;
        }

        numFreeHydrogens += 2;
        hydrogens.notify_one();
        hydrogens.notify_one();

        releaseOxygen();
    }

    void hydrogen(std::function<void()> releaseHydrogen) {
        std::unique_lock<std::mutex> lock(mutex);

        while (numWaitingOxygens < 1 && numFreeHydrogens == 0) {
    waiting:
            ++numWaitingHydrogens;
            hydrogens.wait(lock);
            --numWaitingHydrogens;
        }

        // TODO: might need to poke oxygen here (that could be the bug)

        if (numFreeHydrogens > 0) {
            --numFreeHydrogens;
            releaseHydrogen();
            return;
        }

        oxygens.notify_one();
        goto waiting;
    }
};

#ifdef TEST
#include <cassert>
#include <iostream>
#include <thread>
#include <vector>

std::mutex coutMutex;

void printOxygen() {
    std::lock_guard<std::mutex> guard(coutMutex);
    std::cout << "Oxygen" << std::endl;
}

void printHydrogen() {
    std::lock_guard<std::mutex> guard(coutMutex);
    std::cout << "Hydrogen" << std::endl;
}

int main() {
    H2O h2o;
    std::vector<std::thread> threads;
    char atom;
    while (std::cin >> atom) {
        if (atom == 'o' || atom == 'O') {
            threads.emplace_back([&h2o]() { h2o.oxygen(&printOxygen); });
        }
        else {
            assert(atom == 'h' || atom == 'H');
            threads.emplace_back([&h2o]() { h2o.hydrogen(&printHydrogen); });
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

#endif // defined(TEST)
