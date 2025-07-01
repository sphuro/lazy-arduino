#include "pages.h"
#include "sketches.h"
#include "logs.h"
#include "board.h"
#include "serial.h"
#include "status.h"

pagetype current_page = dashboard;

void switch_page(int delta){
    current_page= (pagetype)((current_page + delta + total) % total);

}

void draw_page(pagetype page){}
