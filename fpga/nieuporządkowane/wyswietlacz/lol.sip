set_global_assignment -entity "lol" -library "lib_lol" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "lol" -library "lib_lol" -name IP_TOOL_VERSION "17.1"
set_global_assignment -entity "lol" -library "lib_lol" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_lol" -name SPD_FILE [file join $::quartus(sip_path) "lol.spd"]

set_global_assignment -library "lib_lol" -name MISC_FILE [file join $::quartus(sip_path) "lol_sim/lol.vho"]
