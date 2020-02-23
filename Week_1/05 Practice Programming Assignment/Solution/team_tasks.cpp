//#include <iostream>
//#include <tuple>
//#include <map>

//-------------------------------------------------------------------------------------------------
//enum class TaskStatus
//{
//    NEW,         
//    IN_PROGRESS,
//    TESTING,      
//    DONE          
//};
//-------------------------------------------------------------------------------------------------
//using TasksInfo = std::map<TaskStatus, int>;
//-------------------------------------------------------------------------------------------------
class TeamTasks
{
private:
    std::map<std::string, TasksInfo> person_tasks;
public:
    const TasksInfo& GetPersonTasksInfo(const std::string& person) const
    {
        return person_tasks.at(person);
    }

    void AddNewTask(const std::string& person)
    {
        ++person_tasks[person][TaskStatus::NEW];
    }

    std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string& person, int task_count)
    {
        TasksInfo updated_tasks;
        TasksInfo upgrade_tasks;
        TasksInfo untouched_tasks;

        auto& task_status = person_tasks[person];
        for (auto& item : task_status)
        {
            switch (item.first)
            {
            case TaskStatus::NEW:
            {
                if (item.second > 0)
                {
                    size_t status_count_new = item.second;
                    for (size_t i = 0; i < static_cast<size_t>(task_count) && status_count_new > 0; --task_count, --status_count_new)
                    {
                        ++upgrade_tasks[TaskStatus::IN_PROGRESS];
                        ++updated_tasks[TaskStatus::IN_PROGRESS];
                    }

                    if (status_count_new > 0)
                    {
                        untouched_tasks[TaskStatus::NEW] += status_count_new;
                        upgrade_tasks[TaskStatus::NEW] += status_count_new;
                    }
                }
                break;
            }
            case TaskStatus::IN_PROGRESS:
            {
                if (item.second > 0)
                {
                    size_t status_count_progress = item.second;
                    for (size_t i = 0; i < static_cast<size_t>(task_count) && status_count_progress > 0; --task_count, --status_count_progress)
                    {
                        ++upgrade_tasks[TaskStatus::TESTING];
                        ++updated_tasks[TaskStatus::TESTING];
                    }

                    if (status_count_progress > 0)
                    {
                        untouched_tasks[TaskStatus::IN_PROGRESS] += status_count_progress;
                        upgrade_tasks[TaskStatus::IN_PROGRESS] += status_count_progress;
                    }
                }
                break;
            }
            case TaskStatus::TESTING:
            {
                if (item.second > 0)
                {
                    size_t status_count_done = item.second;
                    for (size_t i = 0; i < static_cast<size_t>(task_count) && status_count_done > 0; --task_count, --status_count_done)
                    {
                        ++upgrade_tasks[TaskStatus::DONE];
                        ++updated_tasks[TaskStatus::DONE];
                    }
                    if (status_count_done > 0)
                    {
                        untouched_tasks[TaskStatus::TESTING] += status_count_done;
                        upgrade_tasks[TaskStatus::TESTING] += status_count_done;
                    }
                }
                break;
            }
            default:
                if (item.second > 0)
                {
                    upgrade_tasks[TaskStatus::DONE] += item.second;
                }
                break;
            }
        }
        person_tasks[person] = upgrade_tasks;
        return std::make_tuple(updated_tasks, untouched_tasks);
    }
};
//-------------------------------------------------------------------------------------------------
//void PrintTasksInfo(TasksInfo tasks_info) 
//{
//    std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
//    ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
//    ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
//    ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
//}
//-------------------------------------------------------------------------------------------------
//int main()
//{
//    TeamTasks tasks;
//    tasks.AddNewTask("Ilia");

//    for (int i = 0; i < 3; ++i) 
//    {
//        tasks.AddNewTask("Ivan");
//    }

//    std::cout << "Ilia's tasks: ";
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
//    std::cout << "Ivan's tasks: ";
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
//
//    TasksInfo updated_tasks, untouched_tasks;
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
//    std::cout << "Updated Ivan's tasks: ";
//    PrintTasksInfo(updated_tasks);
//    std::cout << "Untouched Ivan's tasks: ";
//    PrintTasksInfo(untouched_tasks);
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
//    std::cout << "Updated Ivan's tasks: ";
//    PrintTasksInfo(updated_tasks);
//    std::cout << "Untouched Ivan's tasks: ";
//    PrintTasksInfo(untouched_tasks);
//
//    return 0;
//}
//-------------------------------------------------------------------------------------------------