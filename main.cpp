
#include "UI/Menu.h"
#include "Utility/Handlers.h"
#include "Utility/Actions.h"
#include "Tests/Tests.h"
#include "UI/Preset.h"

int main() {
    int var_prog = 0;
    print_choose_prog();
    handlerInput(&var_prog, 1, 3);
    if (var_prog == 1)
        program_work();
    else if (var_prog == 2)
        tests();
    else if (var_prog == 3)
        presets();


    return 0;
}


