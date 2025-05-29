#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>


class ThreadPool {
	public : 
		ThreadPool(size_t numThreads);
		~ThreadPool();
		void enqueue( std::function<void()> task);
	private:
		std::vector<std::thread> workers;
		std::queue<std::function<void()>> tasks;

		std::mutex queue_mutex;
		std::condition_variable condition;
		std::atomic<bool> stop;

		void workerThread();
};


ThreadPool::ThreadPool(size_t numThreads):stop(false){

	for(size_t i=0;i<numThreads;++i){
		workers.emplace_back(&ThreadPool::workerThread,this);
	}
}


void ThreadPool::enqueue(std::function<void()> task){
	{

		std::lock_guard<std::mutex> lock(queue_mutex);
		tasks.push(task);
	}
	condition.notify_one();
}


void ThreadPool::workerThread(){

	while(true){
		std::function<void()> task;

		{
			std::unique_lock<std::mutex> lock(queue_mutex);
			condition.wait(lock,[this]{return stop || !tasks.empty(); });
			if(stop && tasks.empty())
				return;
			task=tasks.front();
			tasks.pop();


		}
		task();


	}


}

ThreadPool::~ThreadPool() {
    stop = true;
    condition.notify_all();
    for (std::thread &worker : workers) {
        if (worker.joinable())
	    std::cout<<"Joining"<<std::endl;
            worker.join(); // ✅ Ensures threads finish
    }
}
int main(){

	ThreadPool pool(4);

	pool.enqueue([]{
			
			std::cout<<" Task1 running "<<std::endl;
		         std::this_thread::sleep_for(std::chrono::seconds(1));	
			});

     pool.enqueue([]{

                        std::cout<<" Task2 running "<<std::endl;
                         std::this_thread::sleep_for(std::chrono::seconds(2));
                        });  

    pool.enqueue([]{

                        std::cout<<" Task3 running "<<std::endl;
                         std::this_thread::sleep_for(std::chrono::seconds(10));
                        });
    	

    std::this_thread::sleep_for(std::chrono::seconds(2)); // Wait before main exits
    return 0;





}
