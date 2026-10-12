#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>

using namespace std;

class ThreadPool {
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool done;

    void worker_thread(int id);

public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();
    void add_task(std::function<void()> task);
};