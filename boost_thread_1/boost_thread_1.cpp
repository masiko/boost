#include <boost/thread.hpp>
#include <iostream>
 
void
thread_1 () {
        std::cout << "__PRETTY_FUNCTION__" << std::endl;
}
 
int
main(int argc, char const* argv[])
{
        boost::thread th1(thread_1);
 
        th1.join ();

		std::cout << "Success!!" << std::endl;
 
        return 0;
}
