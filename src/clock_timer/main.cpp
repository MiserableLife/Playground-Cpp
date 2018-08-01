#include <iostream>
#include <iomanip>//for std::setfill
#include <chrono>
/* the time libraries provided by C and POSIX was based on seconds. 
 * As time passes, it changes to miliseconds, microseconds, and finally nanoseconds. 
 * So, C++11 provides precision-netural time library */
int main()
{
/*duration*/
	// second is the unit
	// user defined 
	std::chrono::duration<int> twentySec(20);
	std::chrono::duration<double, std::ratio<60>> halfMin(0.5);//0.5*60 seconds 
	std::chrono::duration<long, std::ratio<1,1000>> oneMilliSec(1);//1*1/1000 seconds


	//c++11 provided
	std::chrono::seconds c11twentySec(20);
	std::chrono::hours aDay(24);
	std::chrono::milliseconds c11oneMilliSec(1);

// canoot be compiled because int type chrono and double type chrono are not converted...
//	std::chrono::milliseconds ms =    halfMin - twentySec;
	
	std::chrono::milliseconds tmp =   std::chrono::duration_cast<std::chrono::seconds>(halfMin) - twentySec;
	//can be compiled because both are integral type
	std::chrono::milliseconds ms =    oneMilliSec + twentySec;
//	std::chrono::milliseconds ms ;	//0 ms
//	ms	+= halfMin - twentySec;
	std::cout<< "oneMilliSec + twentySec : " << ms.count()<<" ms"<<std::endl;
	std::cout<< "oneMilliSec + twentySec : " << std::chrono::nanoseconds(ms).count()<<" ns"<<std::endl;
	if(halfMin < twentySec)
		std::cout<<"halfMin is shorter than twentySec"<<std::endl;
	else
		std::cout<<"halfMin is eqaul to or longer than twentySec"<<std::endl;

	/* duraton methods 
	 * count() : ticks of the duration ; With 25ms by std::chrono::milliseconds => 25, with 25ms by std::chrono::nanoseconds => 25000000
	 * zero() : clear 
	 * max() : maximum possible duration of this type
	 * min() : minimum "" 
	 * duration 
	 * rep : yields the type of the ticks
	 * period : yields the unit type */

	std::chrono::milliseconds msms(12789810889);
	/* duration_cast acts as divide (/)  */
	std::chrono::hours hh = std::chrono::duration_cast<std::chrono::hours>(msms);
	std::chrono::minutes mm = std::chrono::duration_cast<std::chrono::minutes>(msms % std::chrono::hours(1));
	std::chrono::seconds ss = std::chrono::duration_cast<std::chrono::seconds>(msms % std::chrono::minutes(1));
	std::chrono::milliseconds msec = std::chrono::duration_cast<std::chrono::milliseconds>(msms % std::chrono::seconds(1));
	
	std::cout<<"raw : "<< hh.count() <<"::"<<mm.count()<<"::"<<ss.count()<<"::"<<msec.count()<<std::endl;
	std::cout<<"      "<<std::setfill('0')<<std::setw(2)<< hh.count() <<"::"<<
std::setw(2)<< mm.count() <<"::"<<
std::setw(2)<< ss.count() <<"::"<<
std::setw(3)<< msec.count() <<std::endl;




/*timepoint : combination of a duration and a epoch(beginning of a time) */


	return 0;
}
