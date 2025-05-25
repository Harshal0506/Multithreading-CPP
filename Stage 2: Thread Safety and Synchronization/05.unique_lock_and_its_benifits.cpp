
// basic lock/unlock
// manual lock/unlock
// defered locking
// can be moved between scopes
// works with conditional variable 
//1. Basic locking ( like lock_guard )
// std::unique_lock<std::mutex> lock(mutex)
//
// 2. Deferred locking ( lock later )
//
// std::unique_lock<std::mutex> lock(mutex,std::defer_lock);
// 
// // Do something
// lock.lock(); // manually lock later 
//
// 3. manual unlocking 
//
// lock.unlock(); //manually unlock 
// lock.lock();	// lock again 
//
// 4. Movable ( can be returned from function or passed around )
//
//  std::unique_lock<std::mutex> foo(){
//	return std::unique_lock<std::mutex>(m); // move 
//
//  }
// 5. used with conditional variable 
//
//
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
bool ready=false;


void worker(){

	std::unique_lock<std::mutex> lock(m);
	cv.wait(lock,[]{ return ready; });  // wait until ready is true 
	std::cout<<" Worked thread running "<<std::endl;


}


int main(){

	std::thread t( worker);
	std::this_thread::sleep_for(std::chrono::seconds(10));
	{

		std::unique_lock<std::mutex>(m);
		ready=true;
		

	}
	cv.notify_one();

	t.join();

	return 0;
}
