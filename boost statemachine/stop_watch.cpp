#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <iostream>
#include <ctime>
#include<unistd.h>  


using namespace std;
namespace sc = boost::statechart;


struct active;
struct stopped;
struct running;
struct stop_watch;

struct event_start_stop :sc::event<event_start_stop>{};

struct event_reset : sc::event<event_reset>{};

struct reset : sc::event<reset>{};




struct IElapsed_time
{
public:
	virtual double Elapsed_Time () const = 0;

};



 
struct stop_watch : sc::state_machine<stop_watch,active>
{
	
	stop_watch()
	{
		std::cout<<"Entering stop_watch Machine\n";
		std::cout<<std::endl;
	}

	double ElapsedTime() const
	{
		return state_cast< const IElapsed_time & >().Elapsed_Time();
	}


	~stop_watch()
	{
		std::cout<<"Exiting stop_watch Machine\n";
		std::cout<<std::endl;
	}
	

};

struct active : sc::simple_state<active,stop_watch,stopped>
{
public:
	active():elapsed_time(0.0)
	{
		std::cout<<"Entering active state\n";
		std::cout<<std::endl;
	}
	
	 typedef sc::transition<event_reset,active> reactions;


	double elapsed_time_ref() const
	{
		return elapsed_time;
	}

	double& elapsed_time_ref()
	{
		return elapsed_time;
	}




	~active()
	{
		std::cout<<"Exiting active state\n";
		std::cout<<std::endl;
	}

	private:
		double elapsed_time;

};

struct stopped :IElapsed_time, sc::simple_state<stopped,active>
{
public:
	stopped()
	{
		std::cout<<"Entering stopped state\n";
		std::cout<<std::endl;
	}
	
	typedef sc::transition<event_start_stop,running> reactions;
	virtual double Elapsed_Time ()const 
	{
		return  context<active>().elapsed_time_ref();
	}
	~stopped()
	{
		std::cout<<"Exiting stopped state\n";
		std::cout<<std::endl;
	}
};

struct running :IElapsed_time, sc::simple_state<running,active> 
{
	public:
	running():start_time(std::time(0))
	{
		std::cout<<"Entering running state\n";
	 	std::cout<<std::endl;
	}
	
	typedef sc::transition<event_start_stop,stopped> reactions;
	virtual double Elapsed_Time () const
	{
		
		return context<active>().elapsed_time_ref() + difftime(std::time(0),start_time);
	}
	~running()
	{
		context<active>().elapsed_time_ref() = context<active>().elapsed_time_ref() + difftime(std::time(0),start_time);

		std::cout<<"Exiting running state\n";
		std::cout<<std::endl;
	}

private:
	time_t start_time;
	
};




int main()
{
	stop_watch s;
	s.initiate();
	
	string str;


	while(1)
	{
		cout<<"Please select start, stop, reset, time or exit "<<endl;

		cin>>str;

		if(str=="start")
		{
			s.process_event(event_start_stop());
		}
		else if(str=="stop")
		{

			s.process_event(event_start_stop());
		}
		else if(str=="reset")
		{
			s.process_event(event_reset());
		}
		else if(str=="time")
		{
			cout<<s.ElapsedTime()<<endl;
		}
		else if(str=="exit")
		{
			cout<<"Thanks for using"<<endl;
			break;
		}
		else
		{
			cout<<"Please type a valid input"<<endl;
		}

	}

	return 0;
}


