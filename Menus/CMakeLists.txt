set(MENU_SOURCES ../src/menu/menu.h ../src/menu/menuentry.h ../src/menu/menuelements.h ../src/menu/textrenderer.h ../src/menu/menu.c ../src/menu/menuentry.c ../src/menu/menuelements.c ../src/menu/textrenderer.c)
set(GAME_SOURCES ../src/control/random.h ../src/control/random.c
                 ../src/game.h ../src/game.c
                 ../src/weapon.h ../src/weapon.c
                 ../src/arrow.h ../src/arrow.c
                 ../src/bullet.h ../src/bullet.c
                 ../src/particle.h ../src/particle.c
                 ../src/dataStructures/BulletPasta.h ../src/dataStructures/BulletPasta.c
                 ../src/dataStructures/ParticlePasta.h ../src/dataStructures/ParticlePasta.c
                 ../src/math/vector.h ../src/math/vector.c
                 ../src/math/lerp.h ../src/math/lerp.c
        ../src/control/input.h ../src/control/input.c
                 ../src/graphics/graphics.h ../src/graphics/graphics.c)

add_library(MainMenu SHARED MainMenu.h MainMenu.c ../debugmalloc.h ${MENU_SOURCES} ${RANDOM_SOURCES} ${GAME_SOURCES})
