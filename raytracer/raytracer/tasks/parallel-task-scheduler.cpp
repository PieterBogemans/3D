#include "tasks/parallel-task-scheduler.h"
#include <thread>
#include <mutex>

using namespace tasks;


namespace
{
	class ParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
	{

	public:
		void perform(std::vector<std::shared_ptr<Task>> tasks) const
		{
			static std::mutex lock;
			std::vector<std::thread> threads;
			for (unsigned i = 0; i < std::thread::hardware_concurrency(); i++)
			{
				threads.push_back(std::thread(&ParallelTaskScheduler::execute, &tasks, &lock));
			}

			for (auto &thread : threads)
			{
				thread.join();
			}
		}

		static void *execute(std::vector<std::shared_ptr<Task>>* tasks, std::mutex* lock)
		{
			if (tasks->size() > 0)
			{
				lock->lock();
				auto task = tasks->back();
				tasks->pop_back();
				lock->unlock();
				task->perform();
				execute(tasks, lock);
			}
			return 0;
		}
	};
}

TaskScheduler tasks::schedulers::parallel()
{
	return TaskScheduler(std::make_shared<ParallelTaskScheduler>());
}