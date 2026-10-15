#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>

using namespace std;

class ThreadPool {
private:
    vector<thread> threads;
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable cv;
    bool done;

    void worker_thread(int id);

public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();
    void add_task(function<void()> task);
};