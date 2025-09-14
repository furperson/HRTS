#include "InnerFunction/Func/Functions.hpp"

#include "DataBaseUnit/DataBaseUnit.hpp"
#include "HwUnit/HwUnit.hpp"
#include "IOunit/IOunit.hpp"
#include "PersistenceManager/PersistenceManager.hpp"
#include "Scenario.hpp"
#include "Task.hpp"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <nlohmann/json.hpp>

// namespace inner_ {

using json = nlohmann::json;
inner_::AddTask::AddTask(std::mutex& TaskMut, std::mutex& ScenMut, std::vector<Task>& taskStore,
                         std::vector<Scenario>& scenarioStore)
    : TaskMut(TaskMut), ScenMut(ScenMut), taskStore(taskStore), scenarioStore(scenarioStore) {};

int inner_::AddTask::operator()(const Task task) {
    std::scoped_lock lock(TaskMut);
    taskStore.push_back(task);
    return 0;
};
int inner_::AddTask::operator()(const std::string& scenario_name, const std::string& task_name,
                                const std::string& Owner_name_) {
    std::scoped_lock lock(TaskMut, ScenMut);
    auto it = std::find_if(scenarioStore.begin(), scenarioStore.end(),
                           [&scenario_name](const Scenario& element) {
                               return element.getScenarioName() == scenario_name;
                           });
    if (it != scenarioStore.end()) {
        std::string taskName = task_name;
        Task tmp(*it, taskName, Owner_name_);
        taskStore.push_back(tmp);
        return 0;

    } else {
        return 1;
    }
};

int inner_::AddTask::operator()(const std::string& scenario_name, const std::string& Owner_name_) {
    std::scoped_lock lock(TaskMut, ScenMut);
    auto it = std::find_if(scenarioStore.begin(), scenarioStore.end(),
                           [&scenario_name](const Scenario& element) {
                               return element.getScenarioName() == scenario_name;
                           });
    if (it != scenarioStore.end()) {
        std::string taskName = scenario_name;
        Task tmp(*it, taskName, Owner_name_);
        taskStore.push_back(tmp);
        return 0;

    } else {
        return 1;
    }
};

inner_::LoadServData::LoadServData(PersistenceManager& persistenceManager)
    : persistenceManager(persistenceManager) {};

int inner_::LoadServData::operator()(const std::string& str) {
    persistenceManager.Load(str);
    return 0;
};

inner_::OffloadServData::OffloadServData(PersistenceManager& persistenceManager)
    : persistenceManager(persistenceManager) {};

int inner_::OffloadServData::operator()(const std::string& str) {
    persistenceManager.Offload(str);
    return 0;
};

inner_::ExecTask::ExecTask(std::mutex& TaskMut, HwUnit& hwunit, std::vector<Task>& taskStore)
    : TaskMut(TaskMut), hwunit(hwunit), taskStore(taskStore) {};

int inner_::ExecTask::operator()(const std::string& str, const std::string& Owner_name_) {
    const std::lock_guard<std::mutex> lock(TaskMut);
    auto it = std::find_if(taskStore.begin(), taskStore.end(), [&str](const Task& element) {
        return element.getScenario().getScenarioName() == str;
    });
    if (it != taskStore.end() and (Owner_name_ == "admin" or it->getOwnername() == Owner_name_)) {
        hwunit.putTask(*it);
        return 0;
    } else {
        return 1;
    }
};

inner_::ExitServ::ExitServ(PersistenceManager& persistenceManager)
    : persistenceManager(persistenceManager) {};

int inner_::ExitServ::operator()(const int& code) {
    if (code == 1) {
        persistenceManager.Offload("backup");
    }
    std::exit(0);
};

inner_::ShowTask::ShowTask(std::mutex& TaskMut, std::vector<Task>& taskStore)
    : TaskMut(TaskMut), taskStore(taskStore) {
    stateToString = {{TaskState::IDLE, "IDLE"},
                     {TaskState::SUCCESS, "SUCCESS"},
                     {TaskState::IN_WORK, "IN_WORK"},
                     {TaskState::STOP_BY_USER, "STOP_BY_USER"},
                     {TaskState::FAILED, "FAILED"}};
};

std::string inner_::ShowTask::operator()(const std::string& Owner_name_) {
    const std::lock_guard<std::mutex> lock(TaskMut);
    std::string st = "";
    for (auto& task : taskStore) {
        if (Owner_name_ != "admin" and task.getOwnername() != Owner_name_)
            continue;
        st.append("Task: " + task.getScenario().getScenarioName() + "\n");
        st.append("\t Task_state: " + stateToString[task.getState()] + "\n");
        st.append("\t Task_Scen_Name: " + task.getScenario().getScenarioName() + "\n");
        st.append("\t Owner: " + task.getScenario().getOwnername() + "\n");
    }
    return st;
};

std::string inner_::ShowTask::operator()(const std::string& str, const std::string& Owner_name_) {
    const std::lock_guard<std::mutex> lock(TaskMut);
    return "";
};

inner_::ShowScenario::ShowScenario(std::mutex& ScenMut, std::vector<Scenario>& scenarioStore)
    : ScenMut(ScenMut), scenarioStore(scenarioStore) {};

std::string inner_::ShowScenario::operator()(const std::string& Owner_name_) {
    const std::lock_guard<std::mutex> lock(ScenMut);
    std::string st = "";
    for (auto& scen : scenarioStore) {
        if (Owner_name_ != "admin" and scen.getOwnername() != Owner_name_)
            continue;
        st.append(scen.getScenarioName() + "\n");
    }
    return st;
};

std::string inner_::ShowScenario::operator()(const std::string& str,
                                             const std::string& Owner_name_) {
    const std::lock_guard<std::mutex> lock(ScenMut);
    std::string st = "";
    auto it =
        std::find_if(scenarioStore.begin(), scenarioStore.end(),
                     [&str](const Scenario& element) { return element.getScenarioName() == str; });
    if (it != scenarioStore.end() and
        (Owner_name_ == "admin" or it->getOwnername() == Owner_name_)) {
        st.append(it->getScenarioName());
    }
    return st;
};

inner_::DoScript::DoScript(IOunit& iounit) : iounit(iounit) {};

int inner_::DoScript::operator()(const std::string& str) {
    const std::lock_guard<std::mutex> lock(mut);
    auto ifs = std::make_shared<std::ifstream>(str);
    if (!ifs->is_open()) {
        return 1;
    }
    iounit.addIStream(ifs);
    return 0;
};

inner_::AddScenario::AddScenario(std::mutex& ScenMut, std::vector<Scenario>& scenarioStore)
    : ScenMut(ScenMut), scenarioStore(scenarioStore) {};

int inner_::AddScenario::operator()(const Scenario& scen) {
    const std::lock_guard<std::mutex> lock(ScenMut);
    scenarioStore.push_back(scen);
    return 0;
};

inner_::DBloadTask::DBloadTask(DataBaseUnit& dbunit) : dbunit(dbunit) {};

std::optional<Task> inner_::DBloadTask::operator()(std::string user, std::string Taskname) {
    try {
        auto ts = dbunit.loadTask(user, Taskname);
        return ts;
    } catch (const std::exception& e) {
        throw e;
    }
};

inner_::DBoffloadTask::DBoffloadTask(DataBaseUnit& dbunit) : dbunit(dbunit) {};

bool inner_::DBoffloadTask::operator()(std::string user, Task& task) {
    try {
        return dbunit.saveTask(user, task);
    } catch (const std::exception& e) {
        return 0;
    }
    return 1;
};

inner_::DBloadScenario::DBloadScenario(DataBaseUnit& dbunit) : dbunit(dbunit) {};

std::optional<Scenario> inner_::DBloadScenario::operator()(std::string user,
                                                           std::string Scenarioname) {
    try {
        auto sc = dbunit.loadScenario(user, Scenarioname);
        return sc;
    } catch (const std::exception& e) {
        throw e;
    }
};

inner_::DBoffloadScenario::DBoffloadScenario(DataBaseUnit& dbunit) : dbunit(dbunit) {};

bool inner_::DBoffloadScenario::operator()(std::string user, Scenario& scen) {
    try {
        return dbunit.saveScenario(user, scen);
    } catch (const std::exception& e) {
        return 0;
    }
    return 1;
};

inner_::DBverifyUser::DBverifyUser(DataBaseUnit& dbunit)
    : dbunit(dbunit) {

      };

bool inner_::DBverifyUser::operator()(std::string user, std::string hash_passwd) {
    try {
        std::string realps = dbunit.getUserPasswordHash(user);
        if (crypto_pwhash_str_verify(realps.c_str(), hash_passwd.c_str(),
                                     hash_passwd.length()) == 0) {
            return 1;
        } else {
            return 0;
        }
    } catch (const std::exception& e) {
        return 0;
    }
    return 1;
};

inner_::GetTask::GetTask(std::mutex& TaskMut, std::mutex& ScenMut, std::vector<Task>& taskStore,
    std::vector<Scenario>& scenarioStore)
: TaskMut(TaskMut), ScenMut(ScenMut), taskStore(taskStore), scenarioStore(scenarioStore) {};

std::optional<Task> inner_::GetTask::operator()(const std::string& Owner_name_,
                           const std::string& task_name) {
std::scoped_lock lock(TaskMut);

auto it = std::find_if(taskStore.begin(), taskStore.end(),
      [&task_name, &Owner_name_](const Task& element) {
          return (element.getTaskName() == task_name) && (element.getOwnername() == Owner_name_);
      });
if (it != taskStore.end()) {
return *it;
} else {
return std::nullopt;
}
};


inner_::GetScen::GetScen(std::mutex& TaskMut, std::mutex& ScenMut, std::vector<Task>& taskStore,
    std::vector<Scenario>& scenarioStore)
: TaskMut(TaskMut), ScenMut(ScenMut), taskStore(taskStore), scenarioStore(scenarioStore) {};

std::optional<Scenario> inner_::GetScen::operator()(const std::string& Owner_name_,
                           const std::string& scenario_name) {
std::scoped_lock lock(TaskMut);

auto it = std::find_if(scenarioStore.begin(), scenarioStore.end(),
      [&scenario_name, &Owner_name_](const Scenario& element) {
        // std::cout << element.getOwnername()  << std::endl << element.getScenarioName() << std::endl << ((element.getScenarioName() == scenario_name) && (element.getOwnername() == Owner_name_)) ; 
          return (element.getScenarioName() == scenario_name) && (element.getOwnername() == Owner_name_);
      });
if (it != scenarioStore.end()) {
return *it;
} else {
return std::nullopt;
}
};
