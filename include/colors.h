#ifndef COLORS_H
#define COLORS_H

typedef struct {
    int r;
    int g;
    int b;
} rgb_color;

void hex_to_rgb(const char *hex_str, rgb_color *clr);
int rgb_to_256(rgb_color *clr);
void apply_theme(int color_index);
void apply_theme_hex(const char *hex_str);

#endif // COLORS_H
