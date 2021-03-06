#include "engine.h"

#ifdef ENGINE_C
#pragma once
#define CORE_C
#define FRAMEWORK_C
#define SERVER_C
#endif

#include "engine_config.c"
#include "engine_core.c"
#include "engine_framework.c"
#include "engine_server.c"

/// init() function
/// loop() function
/// quit() function

API int init();
API int loop();
API int quit();

static void os_exec_bg( void *cmdline ) {
    os_exec( (const char*)cmdline );
}

static int run( const char *name, const char *proc, bool threaded ) {
    char *dllname = va("%s.dll", name);
    if( file_exist(dllname) ) {
        puts(dllname);
        void (*dllfunc)(void *) = dllquick(dllname, proc);
        if( threaded ) {
            return (detach( dllfunc, 0 ), 0);
        } else {
            return (dllfunc( 0 ), 0);
        }
    }
    char *exename = va("%s.exe", name);
    if( file_exist(exename) ) {
        puts(exename);
        if( threaded ) {
            return (detach( os_exec_bg, (void *)exename ), 0);
        } else {
            return !!os_exec( exename );
        }
    }
    return -1;
}

int init() {
    static int ever = 0;
    if( ever ) return 0;
    ever = 1;

    // log early
    puts("; engine begin. last rebuilt: " __DATE__ " " __TIME__);

    // init sdl
    int sdl_init_flags = 0;
    if( SDL_Init(SDL_INIT_VIDEO | sdl_init_flags) ) {
        die_callback("Error: Cannot initalize application (SDL_Init)"); //, SDL_GetError());
    }

    // cwd
    // cwd base path
    // if( exist("../debug") && exist("../../games/") ) cwd("../../games/");
#ifdef _MSC_VER
    _chdir( SDL_GetBasePath() );
#else
    chdir( SDL_GetBasePath() );
#endif

    // icon

    // vfs
    vfs_import("**");

#if 1 // DEBUG
    // in case binary is present in any _debug/, _debugopt/, _release/ folder
    vfs_import("../games/**");
#endif

/*
    // optional game launch
    run("game", "main", 0);

    // optional game launch (ranges #0-128, #00-128, #000-128)
    for( int i = 0; i < 128; ++i ) {
        run(va("game%d", i), "main", 0);
        run(va("game%02d", i), "main", 0);
        run(va("game%03d", i), "main", 0);
    }
*/
    return 1;
}

int loop() {
    // editor launch
    run("editor", "main", 0);
    return 1;
}

int quit() {
    // teardown
    puts("; engine end");
    return 1;
}
