from PIL import Image, ImageEnhance
from colorama import Style, init
import argparse

init(autoreset=True)

ASCII_CHARS = "@%#*+=-:. "

def get_color(r, g, b):
    return f'\033[38;2;{r};{g};{b}m'  # Truecolor ANSI escape

def enhance_image(image, sharpness=1.0):
    enhancer = ImageEnhance.Sharpness(image)
    return enhancer.enhance(sharpness)

def to_ascii(image_path, width=80, sharpness=1.0, height_scale=0.55):
    image = Image.open(image_path).convert("RGB")
    image = enhance_image(image, sharpness)

    w, h = image.size
    aspect_ratio = h / w
    new_height = int(width * aspect_ratio * height_scale)
    image = image.resize((width, new_height))

    pixels = list(image.getdata())

    for i in range(0, len(pixels), width):
        line = ""
        for j in range(width):
            r, g, b = pixels[i + j]
            brightness = int((r + g + b) / 3)
            char = ASCII_CHARS[brightness * len(ASCII_CHARS) // 256]
            line += f"{get_color(r, g, b)}{char}{Style.RESET_ALL}"
        print(line)

# Optional CLI interface
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert image to colored ASCII.")
    parser.add_argument("image", help="Path to image file (PNG, JPG, etc.)")
    parser.add_argument("--width", type=int, default=80, help="Output width in characters")
    parser.add_argument("--sharpness", type=float, default=1.0, help="Sharpness level (e.g., 1.5 for sharper)")
    parser.add_argument("--scale", type=float, default=0.55, help="Height scale factor for aspect ratio")
    
    args = parser.parse_args()
    to_ascii(args.image, width=args.width, sharpness=args.sharpness, height_scale=args.scale)

