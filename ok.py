from PIL import Image
from colorama import Fore, Back, Style, init
init()

ASCII_CHARS = "@%#*+=-:. "

def get_color(r, g, b):
    return f'\033[38;2;{r};{g};{b}m'

def to_ascii(image, width=80):
    image = image.convert("RGB")
    w, h = image.size
    aspect_ratio = h/w
    height = int(aspect_ratio * width * 0.55)
    image = image.resize((width, height))
    pixels = list(image.getdata())
    for i in range(0, len(pixels), width):
        line = ""
        for j in range(width):
            r, g, b = pixels[i + j]
            brightness = int((r + g + b) / 3)
            char = ASCII_CHARS[brightness * len(ASCII_CHARS) // 256]
            line += f"{get_color(r,g,b)}{char}{Style.RESET_ALL}"
        print(line)

to_ascii(Image.open("Group4.png"))

