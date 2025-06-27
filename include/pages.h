typedef enum {
	dashboard;
	boards;
	libraries;
	cores;
	examples;
} PageType;

extern PageType current_page;
void draw_page(PageType page);
