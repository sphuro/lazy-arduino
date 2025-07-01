#include "ui.h"
#include <stdio.h>


int main(){
	init_ui();
	/* main_menu(); */
	while (1) {
		draw_current_page();
		int ch = getchar();
		if(ch == 0)break;
		//continue	
	}
	end_ui();
	return 0;
}
