add_library(MainMenu MODULE MainMenu.h MainMenu.c)
add_library(OptionsMenu MODULE OptionsMenu.h OptionsMenu.c)
add_library(GraphicsMenu MODULE GraphicsMenu.h GraphicsMenu.c)
add_library(InputMenu MODULE InputMenu.h InputMenu.c)
add_library(IPlayerSelector MODULE IPlayerSelector.h IPlayerSelector.c)
add_library(GcfgMenu MODULE GcfgMenu.h GcfgMenu.c)
add_library(GConfMenu MODULE GConfMenu.h GConfMenu.c)
add_library(PauseMenu MODULE PauseMenu.h PauseMenu.c)
add_library(WinMenu MODULE WinMenu.h WinMenu.c)

target_link_libraries(MainMenu Game)
target_link_libraries(OptionsMenu Game)
target_link_libraries(GraphicsMenu Game)
target_link_libraries(InputMenu Game)
target_link_libraries(IPlayerSelector Game)
target_link_libraries(GcfgMenu Game)
target_link_libraries(GConfMenu Game)
target_link_libraries(PauseMenu Game)
target_link_libraries(WinMenu Game)
