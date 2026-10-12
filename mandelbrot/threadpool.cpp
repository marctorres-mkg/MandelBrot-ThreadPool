#include "threadpool.h"

ThreadPool::ThreadPool(size_t numThreads) {
    done = false;

    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(thread(&ThreadPool::worker_thread, this, i));
    }
}

ThreadPool::~ThreadPool() {
    {
        unique_lock<mutex> lock(mtx);
        done = true;
    }
    cv.notify_all();
    for (auto& t : threads) {
        t.join();
    }
}

void ThreadPool::add_task(function<void()> task) {
    {
        unique_lock<mutex> lock(mtx);
        tasks.push(task);
    }
    cv.notify_one();
}

void ThreadPool::worker_thread(int id) {
    while (true) {
        function<void()> task;
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this] { 
                return !tasks.empty() || done; 
            });
            if (done && tasks.empty()) {
                return;
            }
            task = move(tasks.front());
            tasks.pop();
        }
        task();
    }
}