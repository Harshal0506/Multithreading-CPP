/*
 * std::async is a function in c++ ( introduced in c++11 )  that runs a function asynchronously, meaning it can run potentially in a seperate thread . It returns a std::future object , which can be later used to access the result of the function once its finished executing.
 *
 *
 *
 *
 * #include <future>

 *  std::future<ReturnType> result = std::async(std::launch::policy, function, args...);


 *
 *
 *
 *
 * ReturnType is the return type of function.

    std::launch::policy can be:

    1. std::launch::async — always runs in a new thread.

    2. std::launch::deferred — runs only when you call .get() or .wait() on the future (runs in the calling thread).

Omit the policy to let the implementation decide (async or deferred).
 *
 */
 

#include <iostream>
#include <future>
#include <chrono>
#include <thread>
int slow_add(int a , int b ){

	std::cout<<"async work thread id "<<std::this_thread::get_id()<<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return a+b;


}


int main(){
	//std::future<int> result=std::async(std::launch::async, slow_add, 1 ,2 ); // mandatory in new thread . 
	
	
	std::future<int> result=std::async(std::launch::deferred,slow_add,1,2); // lazyly in same thread 
	std::cout<<"doing my work"<<std::endl;
	std::cout<<"main thread id "<<std::this_thread::get_id()<<std::endl;
	
	std::this_thread::sleep_for(std::chrono::seconds(5));
	//wait for the result 
	//
	
	std::cout<<" Result "<< result.get() <<"\n";

	return 0;
}


/*
 *	key Concepts :
 *	1. non-blocking : std::async starts the function call and return imediately 
 *	2. Thread-management : you dont nead to explicitly create or join thread 
 *	3. result retriaval : .get() blocks until the function completes and give the result value 
 *      4. you can deceide to defer or async in launch 
 *
 *       when to use :
 *       1. when you want simple parallelism without manually managing threads 
 *       2. when a task can be delayed until its result is needed 
 *       3. when doing task which can be done concurrently.
 *
 */
