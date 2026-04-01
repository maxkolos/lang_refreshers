#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include <iostream>
#include <atomic>
#include <shared_mutex>
#include <map>
#include <barrier>
#include <latch>
#include <semaphore>
#include <queue>

// Can be accessed and modified by several threads.  
std::atomic<int> atomic_counter{0};

// Basic lock example.
class Counter {
    int value = 0;
    std::mutex mtx;

public:
    void increment() {
        std::lock_guard<std::mutex> lock(mtx);
        value++;
    }

    int get() {
        std::lock_guard<std::mutex> lock(mtx);
        return value;
    }
};

// Conditional variable example.
class Queue {
  std::queue<int> data_queue;
  std::mutex mtx;
  std::condition_variable cv;

  void push(int x) {
      {
          std::lock_guard<std::mutex> lock(mtx);
          data_queue.push(x);
      }
      cv.notify_one(); // The data is ready.
  }

  int pop() {
      std::unique_lock<std::mutex> lock(mtx);
      // Wait for any data appear.
      cv.wait(lock, [this] { 
        return !data_queue.empty(); // Check to avoid a spurious wakeups.
      });

      int val = data_queue.front();
      data_queue.pop();
      return val;
  }
};

// std::future/std::async example.
int calculate_heavy_logic() {
    return 7 * 6;
}
void future_async_example() {
    // Do heavy work in a separate thread.
    std::future<int> result = std::async(std::launch::async, calculate_heavy_logic);

    // Doing some work.

    // Waits until the heavy work is done.
    std::cout << "Result: " << result.get() << std::endl;
}


// Multiple readers-single writer example.
class Dictionary {
    std::map<std::string, std::string> data;
    mutable std::shared_mutex mtx;

public:
    std::string read(const std::string& key) const {
        std::shared_lock<std::shared_mutex> lock(mtx); // Shared lock for reading.
        return data.at(key);
    }

    void write(const std::string& key, const std::string& val) {
        std::unique_lock<std::shared_mutex> lock(mtx); // Exclusive lock for writing. 
        data[key] = val;
    }
};

void latch_example() {
    std::latch work_done(3); // Wait for three threads to complete.

    for (int i = 0; i < 3; ++i) {
        std::thread([&work_done, i] {
            // Do some work.
            work_done.count_down(); // Tells the work is done.
            std::cout << "Task " << i << " finished\n";
        }).detach();
    }

    work_done.wait(); // Wait until all three threads has finished.
    std::cout << "All tasks are done, moving on!\n";
}

void barrier_example() {
    // Callback for the phase completeness.
    auto on_completion = []() noexcept { std::cout << "--- Phase complete ---\n"; };
    
    std::barrier sync_point(3, on_completion); 

    auto worker = [&](int id) {
        for (int phase = 1; phase <= 2; ++phase) {
            std::cout << "Thread " << id << " working on phase " << phase << "\n";
            
            // My work for this phase is done, wait for other threads.
            sync_point.arrive_and_wait(); 
            
            // All threads has completeted the phase, move to the next phase.
        }
    };

    std::jthread t1(worker, 1), t2(worker, 2), t3(worker, 3);
}

// Binary semaphore example.
std::binary_semaphore signal_to_consumer(1); // 1 means open at start.
void work_with_resource() {
    signal_to_consumer.acquire(); 
    // Work with the resource.
    signal_to_consumer.release(); 
}

// Semaphore example.
std::counting_semaphore<3> pool_limit(3); // 3 threads are allowed.
void access_resource() {
    pool_limit.acquire(); 
    // Work with the resource.
    pool_limit.release(); 
}

// Locking several resources with scoped_lock.
std::mutex mtx1, mtx2;
void lock_two_mutexes() {
    // Locks both mutexes safely. If it can't get both, it won't hold either.
    std::scoped_lock lock(mtx1, mtx2); 
    // Critical section: both resources are protected.
} // Both released here automatically (RAII).

int main() {
}