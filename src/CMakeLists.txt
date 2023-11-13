target_sources(Game PRIVATE
    game.h game.c 
    particle.h particle.c 
    arrow.h arrow.c 
    bullet.h bullet.c 
    weapon.h weapon.c 
    gcfg.h gcfg.c)
add_subdirectory(graphics)
add_subdirectory(control)
add_subdirectory(math)
add_subdirectory(dataStructures)
add_subdirectory(menu)
