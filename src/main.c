#include "ui.h"
#include "pages.h"
#include "sketches.h"
#include "board.h"

int main() {
    init_ui();

    // Load data BEFORE first draw
    load_sketches(".");        // Or correct path like "~/Arduino"
    board_count = get_boards(connected_boards, MAX_BOARDS);

    draw_curr_page();

    while (1) {
        draw_curr_page();
        int ch = getch();
        switch (ch) {
            case KEY_F(1): current_page = dashboard; break;
            case KEY_F(2): current_page = boards; break;
            case KEY_F(3): current_page = libraries; break;
            case KEY_F(4): current_page = cores; break;
            case KEY_F(5): current_page = examples; break;
            case 'q': case 27: // ESC or 'q' to quit
                end_ui();
                return 0;
        }
    }
    

    end_ui();
    return 0;
}

