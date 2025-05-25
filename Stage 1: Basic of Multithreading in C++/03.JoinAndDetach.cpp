//Stackoverflow link :https://stackoverflow.com/questions/37015775/what-is-different-between-join-and-detach-for-multi-threading-in-c


#include <iostream>
#include <thread>
#include <chrono>


void backgroundTask( const std::string & name , int seconds ){
	std::cout<< name <<" started ( thread id : "<< std::this_thread::get_id() <<" )\n";
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
	std::cout<<name <<" finished \n";

}


int main(){
	// Thread A : joined ( main thread will wait for it )
	std::thread t1(backgroundTask,"Joined thread ",2);
	// Thread B : detached ( runs independently )
	std::thread t2(backgroundTask,"Detached thread",1);
	
	t2.detach(); // let it run in a background 
	t1.join(); // waits for joined thread to finish 
	
	std::cout<<" Main thread finished . \n";

	
	return 0;
}

