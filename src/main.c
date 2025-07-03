#include "ui.h"
#include "pages.h"
#include "sketches.h"
#include "board.h"

int main() {
    init_ui();
    load_sketches(".");
    board_count = get_boards(connected_boards, MAX_BOARDS);
    draw_curr_page();
    int ch;
    while ((ch = getch())) {
        /* draw_curr_page(); */
        /* int ch = getch(); */
        switch (ch) {
            case KEY_F(1): current_page = dashboard; break;
            case KEY_F(2): current_page = boards; break;
            case KEY_F(3): current_page = libraries; break;
            case KEY_F(4): current_page = cores; break;
            case KEY_F(5): current_page = examples; break;
            case 'q': case 27: // ESC or 'q' to quit
                end_ui();
                return 0;
        /* sleep(1); */
        }
        if(current_page == dashboard){
            handle_sketch(ch);
            draw_curr_page();
            continue;
        }
        draw_curr_page();
    }
    

    end_ui();
    return 0;
}

