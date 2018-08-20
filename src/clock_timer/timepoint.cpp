#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>

std::string asString(const std::chrono::system_clock::time_point& tp)
{
	std::time_t t = std::chrono::system_clock::to_time_t(tp);
	std::string ts = std::ctime(&t); //convert to calendar time
	ts.resize(ts.size()-1);
	return ts;

}


int main()
{
	std::chrono::system_clock::time_point tp;
	std::cout<<"epoch : "<<asString(tp)<<std::endl;

	tp  = std::chrono::system_clock::now();
	std::cout<<"now : "<<asString(tp)<<std::endl;

	tp = std::chrono::system_clock::time_point::max();
	std::cout<<"max : "<<asString(tp)<<std::endl;

	tp = std::chrono::system_clock::time_point::min();
	std::cout<<"min : "<<asString(tp)<<std::endl;

	std::cout<<"ptr size : "<<sizeof(void*)<<std::endl;


	std::this_thread::sleep_for(std::chrono::seconds(10));

	return 0;

}
