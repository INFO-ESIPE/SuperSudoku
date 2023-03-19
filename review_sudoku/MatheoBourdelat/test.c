#include <MLV/MLV_all.h>
#include <stdio.h>

int main (int argc, char* argv[]){
        
        MLV_create_window( "beginner - 1 - hello world", "hello world", 640, 480 );
        MLV_draw_text(
                10, 120, 
                "Bonjour !",
                MLV_COLOR_MAGENTA
        );
        MLV_draw_line( 120, 50, 160, 90 , MLV_COLOR_WHITE );
        MLV_actualise_window();
        MLV_wait_seconds( 10 );
        MLV_free_window();

        return 0;
}