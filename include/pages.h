#ifndef PAGES_H
#define PAGES_H

typedef enum {
	dashboard =0,
	boards,
	libraries,
	cores,
	examples,
	color_picker,
	total
} pagetype;

extern pagetype current_page;

void draw_page(pagetype page);
void switch_page(int delta);
void draw_curr_page(void);

#endif
