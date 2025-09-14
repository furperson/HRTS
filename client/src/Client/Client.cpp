#include "Client/Client.hpp"

#include <fstream>

void Client::initCli() {

    iOunit.addIStream(std::shared_ptr<std::istream>(&std::cin, [](std::istream*) {}));
    iOunit.addOStream(std::shared_ptr<std::ostream>(&std::cout, [](std::ostream*) {}));

    interpretator.addCMD("exit", [&](ParsedCMD& cmd) {
        this->iOunit.write("Программа завершилась...");
        std::exit(0);
        return 0;
    });

    interpretator.addCMD("do-script", [&](ParsedCMD& cmd) {
        auto ifs = std::make_shared<std::ifstream>(cmd.otherArgs[0]);
        if (!ifs->is_open()) {
            return 1;
        }
        iOunit.addIStream(ifs);
        return 0;
    });

    interpretator.addCMD("make-scenario", [&](ParsedCMD& cmd) {
        std::string scenarioName;
        int testDurationMs;
        int stopScenarioPin = -1;
        std::string fpgaFirmwareName;

        std::array<bool, 64> m_pinScanEnable;
        std::fill(std::begin(m_pinScanEnable), std::end(m_pinScanEnable), 0);
        std::vector<PinBusGroup> m_pinNaming;
        iOunit.write("Имя сценария: ");
        scenarioName = iOunit.readLine();
        iOunit.write("Длительность сценария в МС : ");
        testDurationMs = stoi(iOunit.readLine());
        iOunit.write("Имя прошивки: ");
        fpgaFirmwareName = iOunit.readLine();
        auto it =
            find_if(scenarioStore.begin(), scenarioStore.end(), [scenarioName](const Scenario& s) {
                return s.getScenarioName() == scenarioName;
            });

        if (it != scenarioStore.end()) {

            iOunit.write("Сценарий с таким названием уже существует!");
        } else {
            scenarioStore.push_back(Scenario(scenarioName, testDurationMs, stopScenarioPin,
                                             fpgaFirmwareName, m_pinScanEnable, m_pinNaming,
                                             username));
        }

        return 0;
    });

    interpretator.addCMD("make-task", [&](ParsedCMD& cmd) {
        auto it = find_if(scenarioStore.begin(), scenarioStore.end(), [cmd](const Scenario& s) {
            return s.getScenarioName() == cmd.otherArgs[0];
        });

        if (it == scenarioStore.end()) {
            iOunit.write("Сценарий с таким названием нет!!");
            return 1;
        } else {
            auto it2 = find_if(taskStore.begin(), taskStore.end(), [cmd](const Task& s) {
                return s.getTaskName() == cmd.otherArgs[1];
            });

            if (it2 == taskStore.end()) {
                taskStore.push_back(Task(*it, cmd.otherArgs[1],username));

            } else {
                iOunit.write("Задание с таким названием уже существует!");
                return 1;
            }
        }

        return 0;
    });

    interpretator.addCMD("show-scenarios", [&](ParsedCMD& cmd) {
        for (auto& scen : scenarioStore) {
            iOunit.write(scen.getScenarioName() + "\n");
        }

        return 0;
    });

    interpretator.addCMD("show-tasks", [&](ParsedCMD& cmd) {
        std::map<TaskState, std::string> stateToString = {{TaskState::IDLE, "IDLE"},
                                                          {TaskState::SUCCESS, "SUCCESS"},
                                                          {TaskState::IN_WORK, "IN_WORK"},
                                                          {TaskState::STOP_BY_USER, "STOP_BY_USER"},
                                                          {TaskState::FAILED, "FAILED"}};
        for (auto& task : taskStore) {
            iOunit.write("Task: " + task.getScenario().getScenarioName() + "\n");
            iOunit.write("\t Task_state: " + stateToString[task.getState()] + "\n");
            iOunit.write("\t Task_Scen_Name: " + task.getScenario().getScenarioName() + "\n");
        }

        return 0;
    });

    interpretator.addCMD("connect", [&](ParsedCMD& cmd) {

        remoteService.connect(cmd.otherArgs[0], std::stoi(cmd.otherArgs[1]));
        Message msg_to_send;

        msg_to_send.cmds = Commands::LOGGING;
        msg_to_send.data = json::object();
        msg_to_send.data["user"] = username;
        msg_to_send.data["passwd"] = cmd.otherArgs[2];
        json request_json = msg_to_send;
        json response_json = json::object();

        remoteService.send_request(request_json,response_json);
        std::cout<< response_json;

        return 0;
    });

    interpretator.addCMD("disconnect", [&](ParsedCMD& cmd) {
        remoteService.disconnect();

        return 0;
    });

    interpretator.addCMD("get-task-list", [&](ParsedCMD& cmd) {
        Message msg_to_send;

        msg_to_send.cmds = Commands::GET_TASK_LIST;
        msg_to_send.data = json::object();
        json request_json = msg_to_send;
        json response_json = json::object();

        if (remoteService.send_request(request_json, response_json)) {
            std::cout << "Полученный ответ: " << response_json.dump(2) << std::endl;

            try {
                Resp server_response = response_json.get<Resp>();

                if (server_response.code == 200) {
                    std::cout << "Успешно!\n" << std::endl;
                    iOunit.write(server_response.data);

                } else {
                    iOunit.write("Сервер вернул код возврата : " +
                                 std::to_string(server_response.code));
                }

            } catch (const json::exception& e) {
                std::cerr << "Failed to parse server response: " << e.what() << std::endl;
            }

        } else {
            std::cerr << "Failed to send/receive data. Check connection." << std::endl;
        }

        return 0;
    });

    interpretator.addCMD("get-scenario-list", [&](ParsedCMD& cmd) {
        Message msg_to_send;

        msg_to_send.cmds = Commands::GET_SCENARIO_LIST;
        msg_to_send.data = json::object();
        json request_json = msg_to_send;
        json response_json = json::object();

        if (remoteService.send_request(request_json, response_json)) {
            std::cout << "Полученный ответ: " << response_json.dump(2) << std::endl;

            try {
                Resp server_response = response_json.get<Resp>();

                if (server_response.code == 200) {
                    std::cout << "Успешно!\n" << std::endl;
                    iOunit.write(server_response.data);

                } else {
                    iOunit.write("Сервер вернул код возврата : " +
                                 std::to_string(server_response.code));
                }

            } catch (const json::exception& e) {
                std::cerr << "Failed to parse server response: " << e.what() << std::endl;
            }

        } else {
            std::cerr << "Failed to send/receive data. Check connection." << std::endl;
        }

        return 0;
    });

    interpretator.addCMD("get-task", [&](ParsedCMD& cmd) { return 0; });

    interpretator.addCMD("get-scenario", [&](ParsedCMD& cmd) { return 0; });

    interpretator.addCMD("run-task", [&](ParsedCMD& cmd) { return 0; });

    interpretator.addCMD("help", [&](ParsedCMD& cmd) {
        std::string st =
            "Доступные команды: \n"
            "help - помощь\n make-scenario - интерактивное создание сценария \n" // done
            "make-task <имя_сценария> <имя_задания> - создание задания \n"       // done
            "show-scenarios - показ всех сценариев \n"                           // done
            "show-tasks - показ всех заданий \n"                                 // done
            "get-task-list - получения списка заданий на сервере \n"             //
            "get-scenario-list - получения списка сценариев на сервере \n"       //
            "get-task <имя_задания> - получения  задания с сервера (если такое уже есть, "
            "перезаписывает) \n" //
            "get-scenario <имя_сценария> - получения  сценария с сервера (если такое уже есть, "
            "перезаписывает)\n"                                                              //
            "run-task <имя_локального_задания> - отправка и запуск на управление задания \n" //
            "connect <IP> <port> <passwd> - подключение к серверу \n"                                 // done
            "disconnect - отключиться от сервера \n";                                        // done
        iOunit.write(st);

        return 0;
    });
}

void Client::run() {
    for (;;) {
        try {
            auto tmpCMD = PreParse(iOunit.readLine());
            if (tmpCMD) {
                interpretator.processCMD(*tmpCMD);
            } else {
                iOunit.write("Ошибка в команде около: " + tmpCMD.error() + "\n");
            }
        } catch (const std::exception& e) {
            std::cerr << "Error while processing command: " << e.what() << std::endl;
        }
    }
};

Client::Client(std::string username)
    : username(username), interpretator(iOunit) {
}

Client::~Client() {
}
