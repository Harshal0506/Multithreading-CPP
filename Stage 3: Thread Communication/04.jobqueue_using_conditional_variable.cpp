#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>



class JobQueue{
	public:
		using Job=std::function<void()>;

		void push(Job job){
			{
				std::unique_lock<std::mutex> lock(mutex_);
				jobs_.push(std::move(job));

			}
			cond_var_.notify_one(); // wait up one waiting consumer 
			
		}

		bool pop(Job& job){
			std::unique_lock<std::mutex> lock(mutex_);
			cond_var_.wait(lock,[this]{
					
						return !jobs_.empty() || shutdown_;
					});
			if(shutdown_ && jobs_.empty()){
				return false;
			}
			job=std::move(jobs_.front());
			jobs_.pop();
			return true;


		}
		void shutdown(){
		{	
			std::unique_lock<std::mutex>  lock(mutex_);
			shutdown_=true;
			
		}
		cond_var_.notify_all();
		}

private:
		std::queue<Job> jobs_;
		std::mutex mutex_;
		std::condition_variable cond_var_;
		bool shutdown_=false;
		
};



void consumer(JobQueue & queue , int id ){
	
	JobQueue::Job job;
	while(queue.pop(job)){

		std::cout<<" consumer "<<id <<" processing job \n";
		job();
	}
	std::cout<<" Consumer "<<id <<"exiting \n"<<std::endl;


}


int main(){

	
     JobQueue queue;
     std::vector<std::thread> threads;

    // Start consumer threads
    int num_consumers=4;
    for (int i = 0; i < num_consumers; ++i) {
        threads.emplace_back(consumer,std::ref(queue), i);
    }

    // Submit jobs
    for (int i = 0; i < 10; ++i) {
        queue.push([i]() {
            std::cout << "  Job " << i << " is running.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        });
    }

    // Shut down the queue and join threads
    queue.shutdown();
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
