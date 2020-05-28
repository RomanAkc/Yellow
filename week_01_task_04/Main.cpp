#include "TeamTasks.cpp"
#include <iostream>

// ѕринимаем словарь по значению, чтобы иметь возможность
// обращатьс€ к отсутствующим ключам с помощью [] и получать 0,
// не мен€€ при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
	std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
}

int main() {
	TeamTasks tasks;
	for (int i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	TasksInfo updated_tasks, untouched_tasks;

	std::tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(updated_tasks);
	PrintTasksInfo(untouched_tasks);

	std::tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(updated_tasks);
	PrintTasksInfo(untouched_tasks);

	std::tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Alice", 1);
	PrintTasksInfo(updated_tasks);
	PrintTasksInfo(untouched_tasks);

	for (int i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}

	std::tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Alice", 2);
	PrintTasksInfo(updated_tasks);
	PrintTasksInfo(untouched_tasks);

	std::tie(updated_tasks, untouched_tasks) =
		tasks.PerformPersonTasks("Alice", 4);
	PrintTasksInfo(updated_tasks);
	PrintTasksInfo(untouched_tasks);

	return 0;
}