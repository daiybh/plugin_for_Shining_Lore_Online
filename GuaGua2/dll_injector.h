#include "actions.h"
namespace Dll_injector {
#define INVALID_PID (-1)


    bool action_load(int pid, const wchar_t* dll_path)
    {
        std::cout << "Selected Action: LOAD\n";
        size_t injected = 0;

        if (inject_into_process(pid,dll_path)) {
            if (is_module_in_process(pid, dll_path)) {
               // paramkit::print_in_color(MAKE_COLOR(BLACK, LIME), "Injection OK!");

                return true;
            }
        }
        std::cout << "Injection failed\n";
        return false;
    }

    bool action_check(int pid, const wchar_t* dll_path)
    {
        std::cout << "Selected Action: CHECK\n";
        if (is_module_in_process(pid, dll_path)) {
            //paramkit::print_in_color(MAKE_COLOR(BLACK, WHITE), "Module found!");
            return true;
        }
        //paramkit::print_in_color(MAKE_COLOR(BLACK, WHITE), "Module not present in the process!");
        return false;
    }

    bool action_unload(int pid, const wchar_t* dll_path)
    {
        std::cout << "Selected Action: UNLOAD\n";

        bool isFound = false;
        if (!is_module_in_process(pid, dll_path)) {
            std::cout << "Module not present in the process!\n";
            return false;
        }
        if (unload_module(pid, dll_path)) {
            isFound = true;
           // paramkit::print_in_color(MAKE_COLOR(BLACK, YELLOW), "Module unloaded!");
        }
        return isFound;
    }

    /*bool Injector(int action, int pid, const wchar_t* dll_path)
    {
        bool res;
        switch (action) {
        case 1:
            res = action_load(pid, dll_path); break;
        case 2:
            res = action_unload(pid, dll_path); break;
        case 3:
            res = action_check(pid, dll_path); break;
        }
        return res;
    }*/

};