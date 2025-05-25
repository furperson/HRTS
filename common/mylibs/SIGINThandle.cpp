#include <iostream>
#include <string>
#include <csignal> // Для signal
#include <atomic>  // Для std::atomic_bool (потокобезопасный флаг)
#include <limits>  // Для std::numeric_limits

// Глобальный флаг, который будет установлен обработчиком сигнала
// std::atomic_bool гарантирует безопасное изменение из обработчика сигнала
// и безопасное чтение из основного потока.
// volatile sig_atomic_t g_signal_flag = 0; // Более C-шный вариант
std::atomic<bool> g_sigint_received(false);

// Обработчик сигнала
void handle_sigint(int signal_num) {
    if (signal_num == SIGINT) {
        // Внутри обработчика сигнала можно делать очень мало безопасных вещей!
        // Нельзя использовать std::cout, malloc, free, и большинство функций stdlib.
        // Самое безопасное - установить флаг.
        g_sigint_received.store(true); // Устанавливаем флаг

        // Можно попытаться перерегистрировать обработчик (некоторые системы сбрасывают его)
        // signal(SIGINT, handle_sigint);
        // Но лучше использовать sigaction для более предсказуемого поведения.
    }
}

// int main() {
//     // Устанавливаем обработчик для SIGINT
//     // signal(SIGINT, handle_sigint);
//     // Для более надежной обработки сигналов (особенно на POSIX-системах)
//     // лучше использовать sigaction, т.к. поведение signal может отличаться.
//     // struct sigaction sa;
//     // sa.sa_handler = handle_sigint;
//     // sigemptyset(&sa.sa_mask); // Не блокировать другие сигналы во время выполнения этого
//     // sa.sa_flags = 0; // Можно SA_RESTART для автоматического перезапуска некоторых системных вызовов
//     // if (sigaction(SIGINT, &sa, NULL) == -1) {
//     //     perror("sigaction");
//     //     return 1;
//     // }


//     std::string line;
//     std::cout << "Программа запущена. Нажмите Ctrl+C для проверки или введите 'exit' для выхода." << std::endl;

//     while (true) {
//         std::cout << "> ";
//         if (!std::getline(std::cin, line)) {
//             if (g_sigint_received.load()) {
//                 // getline был прерван сигналом
//                 std::cout << "\nSIGINT получен во время ожидания ввода!" << std::endl;
//                 // Сбрасываем флаг сигнала
//                 g_sigint_received.store(false);
//                 // Сбрасываем состояние ошибки std::cin
//                 std::cin.clear();
//                 // Очищаем буфер, если что-то некорректное осталось (хотя при EINTR обычно нет)
//                 // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//                 // Здесь можно спросить, хочет ли пользователь выйти
//                 std::cout << "Вы действительно хотите выйти? (y/n): ";
//                 if (std::getline(std::cin, line) && (line == "y" || line == "Y")) {
//                     std::cout << "Завершение программы по запросу пользователя после SIGINT." << std::endl;
//                     break;
//                 } else {
//                     std::cin.clear(); // На случай, если и этот getline был прерван или неудачен
//                     std::cout << "Продолжаем работу..." << std::endl;
//                     continue; // Начать новую итерацию цикла ввода
//                 }
//             } else if (std::cin.eof()) {
//                 std::cout << "\nEOF получен (Ctrl+D или Ctrl+Z). Завершение программы." << std::endl;
//                 break;
//             } else {
//                 // Другая ошибка ввода
//                 std::cout << "\nОшибка ввода. Попробуйте еще раз." << std::endl;
//                 std::cin.clear();
//                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                 continue;
//             }
//         } else {
//             // Успешный ввод строки
//             if (line == "exit") {
//                 std::cout << "Завершение программы по команде 'exit'." << std::endl;
//                 break;
//             }
//             std::cout << "Вы ввели: " << line << std::endl;
//         }

//         // Проверяем флаг и вне операции ввода (если SIGINT пришел во время обработки)
//         if (g_sigint_received.load()) {
//             std::cout << "\nSIGINT получен!" << std::endl;
//             g_sigint_received.store(false); // Сброс флага
//             // Здесь можно решить, что делать: выйти, спросить и т.д.
//             std::cout << "Вы действительно хотите выйти? (y/n): ";
//             // Повторный ввод может быть снова прерван.
//             // В сложных приложениях может потребоваться более хитрая логика,
//             // например, временное игнорирование SIGINT на время этого запроса.
//             if (std::getline(std::cin, line) && (line == "y" || line == "Y")) {
//                 std::cout << "Завершение программы по запросу пользователя после SIGINT." << std::endl;
//                 break;
//             } else {
//                 std::cin.clear();
//                 std::cout << "Продолжаем работу..." << std::endl;
//             }
//         }
//     }

//     std::cout << "Программа завершена." << std::endl;
//     // Здесь могут выполняться деструкторы глобальных/статических объектов,
//     // если выход был корректным (не аварийное завершение из-за необработанного сигнала)
//     return 0;
// }