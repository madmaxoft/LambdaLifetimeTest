
// main.cpp

// Implements the entire test program

#include <iostream>
#include <vector>
#include <functional>




using namespace std;





class Scheduler
{
public:
	std::vector<std::pair<int, std::function<void(Scheduler &)>>> m_Tasks;

	void schedule(std::function<void(Scheduler &)> a_Task)
	{
		cout << "Emplacing the task" << endl;
		static int idx = 0;
		m_Tasks.emplace_back(idx++, std::move(a_Task));
	}

	void run(void)
	{
		for (const auto & t: m_Tasks)
		{
			cout << "Calling stored task." << endl;
			t.second(*this);
		}
	}
} ;





class Task
{
public:
	Task(void)
	{
		cout << "Creating a Task instance at " << this << endl;
	}

	Task(const Task & a_SrcTask)
	{
		cout << "Creating a copy of task " << &a_SrcTask << " at " << this << endl;
	}

	Task(Task && a_SrcTask)
	{
		cout << "Moving task " << &a_SrcTask << " to " << this << endl;
	}

	~Task()
	{
		cout << "Deleting task at " << this << endl;
	}

	void operator()(Scheduler & a_Scheduler)
	{
		cout << "** Executing task at " << this << endl;
	}
};





void testLambda(Scheduler & a_Scheduler)
{
	cout << "==== Lambda test ====" << endl;
	{
		int data = 1;
		cout << "Creating lambda" << endl;
		a_Scheduler.schedule([&data](Scheduler & a_Sched)
			{
				cout << "** Executing lambda, data is " << data << endl;
			}
		);
		data = 2;

		cout << "Lambda & data going out of scope" << endl;
		data = 3;
	}

	int data2 = -1;

	cout << "Calling scheduler with potentially invalid lambda, data2 is " << data2 << endl;
	a_Scheduler.run();
	cout << "==== Lambda test done ====" << endl;
}




void testInstance(Scheduler & a_Scheduler)
{
	cout << "==== Instance test ====" << endl;
	{
		cout << "Creating task instance" << endl;
		Task task;
		cout << "Task instance is at " << &task << endl;
		cout << "Scheduling task" << endl;
		a_Scheduler.schedule(task);

		cout << "Task going out of scope" << endl;
	}

	cout << "Calling scheduler with potentially invalid task" << endl;
	a_Scheduler.run();
	cout << "==== Instance test done ====" << endl;
}





int main(int, char *[])
{
	cout << "Starting the test" << endl;

	cout << "Creating scheduler" << endl;
	Scheduler sched;

	testLambda(sched);
	testInstance(sched);

	cout << "Running scheduler in the outer function" << endl;
	sched.run();

	cout << "---- All tests done ----" << endl;
	return 0;
}





