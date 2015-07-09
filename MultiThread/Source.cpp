#include <iostream>
using namespace std;


#include <thread>							// class thread
#include <future>							// provide results for function called asynchronously
#include <mutex>							// critical section
#include <atomic>							// atomic variables
#include <condition_variable>				// 


void Example1()
{
	// <thread>
	cout<<"Example1:"<<endl;

	auto func1 = [](void) -> void
	{
		cout<<"func1"<<endl;
	};

	thread a;				// create an empty "thread" object
	a = thread(func1);		// call "func1()" through thread a
	a.join();				// join(waif for) thread a;

	thread b(func1);		// call "func1()" through just created "thread" b
	b.join();
	b = thread(func1);		// call "func1()" through b again
	b.join();


	auto func2 = [](int a) -> void
	{
		cout<<"func2("<<a<<")"<<endl;
	};

	thread c;
	c = thread(func2,5);	// call "func2()" through thread c, with agrument 5
	c.join();

	thread d(func2,10);		// call "func2()" through just created "thread" d, with argument 10
	d.join();
}
void Example2()
{
	// <thread> + <future> (future class)
	cout<<"Example2:"<<endl;

	auto func1 = [](void) -> int
	{
		_sleep(3000);
		return 5;
	};

	future<int> a = async(func1);			// call "func2", through "async" (asynchronously)
	a.wait();								// wait until a is complete
	cout<<a.get()<<endl;					// get a return value

	future<int> b;
	b = async(func1);						// call "func2" through b
	while(b.wait_for(chrono::milliseconds(1000)) == future_status::timeout)
	{										// wait 1000ms(1 second) for completing b, if timeout print "wait for b"
		cout<<"wait for b"<<endl;
	}
	cout<<b.get()<<endl;					// get b return value

	future<int> c = async(func1);
	cout<<c.get()<<endl;					// just wait & get c return value
}
void Example3()
{
	// <thread> + <future> (promise class)
	cout<<"Example3:"<<endl;

	auto func1 = [](future<int> &f) -> void
	{
		while(f.wait_for(chrono::seconds(1)) == future_status::timeout)
		{									// wait for "f" complete
			cout<<"waiting..."<<endl;
		}
		cout<<f.get()<<endl;				// get f return value
	};

	promise<int>	pa;						// create "promise" object
	future<int>		fa = pa.get_future();	// engagement with future

	thread ta(func1, ref(fa));				// call func1, use "ref", to get reference for future object(it's deleted function)

	_sleep(4000);

	pa.set_value(4);						// set pa value, now fa can get it

	ta.join();
}
void Example4()
{
	// <thread> + <future> (mutex class)
	cout<<"Example4:"<<endl;

	auto func1 = [](mutex& m) -> void
	{
		m.lock();
		cout<<"critical section"<<endl;
		_sleep(2000);
		m.unlock();
	};

	mutex m;

	thread a(func1,ref(m));
	thread b(func1,ref(m));
	a.join();
	b.join();
}
void Example5()
{
	// <thread> + <atomic>
	cout<<"Example5:"<<endl;

	auto func1 = [](atomic<bool> &trigger) -> void
	{
		cout<<"Enter func"<<endl;
		_sleep(5000);
		trigger = true;
		cout<<"Leave func"<<endl;
	};

	atomic<bool> a = false;
	thread t(func1,ref(a));

	while(!a)
	{
		_sleep(1000);
		cout<<"waiting..."<<endl;
	}
	t.join();
}


void main()
{
	//Example1();
	//Example2();
	//Example3();
	//Example4();
	Example5();

	system("pause");
}