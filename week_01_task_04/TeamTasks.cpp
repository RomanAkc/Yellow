#include "TasksInfo.h"

#include <tuple>
#include <string>

class TeamTasks {
private:
	std::map<std::string, TasksInfo> personToTasks;

public:
	// ѕолучить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const std::string& person) const
	{
		return personToTasks.at(person);
	}

	// ƒобавить новую задачу (в статусе NEW) дл€ конкретного разработчитка
	void AddNewTask(const std::string& person)
	{
		if (personToTasks.find(person) == personToTasks.end())
		{
			TasksInfo ti{ {TaskStatus::NEW, 1} };
			personToTasks[person] = ti;
		}
		else
		{
			TasksInfo ti = personToTasks[person];
			if (ti.find(TaskStatus::NEW) == ti.end())
			{
				ti[TaskStatus::NEW] = 1;
				personToTasks[person] = ti;
			}
			else
				personToTasks[person].at(TaskStatus::NEW)++;
		}
			
	}

	// ќбновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const std::string& person, int task_count)
	{
		TasksInfo upd, untch;

		if (personToTasks.find(person) == personToTasks.end())
			return std::make_tuple(upd, untch);

		auto& ti = GetPersonTasksInfo(person);
		int task_not_in_done = 0;
		for (auto& obj : ti)
		{
			if (obj.first < TaskStatus::DONE)
				task_not_in_done += obj.second;
		}

		if (task_count > task_not_in_done)
			task_count = task_not_in_done;
		
		/*for (auto& obj : ti)
		{
			if (task_count == 0)
				break;

			if (obj.second <= task_count)
			{
				task_count -= obj.second;
				TaskStatus newStatus = static_cast<TaskStatus>(static_cast<int>(obj.first) + 1);
				if(obj.second > 0)
					upd[newStatus] = obj.second;
				newTi.erase(obj.first);
				newTi[newStatus] += obj.second;
			}
			else
			{
				TaskStatus newStatus = static_cast<TaskStatus>(static_cast<int>(obj.first) + 1);
				upd[newStatus] = task_count;
				newTi[obj.first] = obj.second - task_count;
				if(newTi[obj.first] == 0)
					newTi.erase(obj.first);
				newTi[newStatus] += task_count;
				task_count = 0;
			}
		}*/


		/*for (auto& obj : ti)
		{
			if (obj.first < TaskStatus::DONE)
			{
				TaskStatus newStatus = static_cast<TaskStatus>(static_cast<int>(obj.first) + 1);
				auto res = obj.second - (upd.count(newStatus) > 0 ? upd[newStatus] : 0);
				if(res > 0)
					untch[obj.first] = res;
			}
		}*/


		//auto newTi = ti;
		
		for (auto& obj : ti)
		{
			if(task_count >= obj.second)
			{
				task_count -= obj.second;
				auto newStatus = static_cast<TaskStatus>(static_cast<int>(obj.first) + 1);
				upd[newStatus] = obj.second;
			}
			else if(task_count > 0)
			{
				auto newStatus = static_cast<TaskStatus>(static_cast<int>(obj.first) + 1);
				upd[newStatus] = task_count;
				untch[obj.first] = obj.second - upd[newStatus];
				task_count = 0;
			}
			else
			{
				untch[obj.first] = obj.second;
			}
		}

		TasksInfo newTi;
		for (int i = 0; i < 4; ++i)
		{
			auto ts = static_cast<TaskStatus>(i);
			int nVal1 = upd.count(ts) > 0 ? upd[ts] : 0;
			int nVal2 = untch.count(ts) > 0 ? untch[ts] : 0;

			if ((nVal1 + nVal2) > 0)
				newTi[ts] = nVal1 + nVal2;
		}
		
		
		personToTasks[person] = newTi;
		untch.erase(TaskStatus::DONE);

		return std::make_tuple(upd, untch);
	}
};