from PIL import Image, ImageEnhance
from colorama import Style, init
import argparse
import os

init(autoreset=True)

ASCII_CHARS = "@%#*+=-:. "

def get_color(r, g, b):
    return f'\033[38;2;{r};{g};{b}m'

def enhance_image(image, sharpness=1.0):
    enhancer = ImageEnhance.Sharpness(image)
    return enhancer.enhance(sharpness)

def to_ascii(image_path, width=80, height=None, sharpness=1.0, output_path=None, use_color=True):
    image = Image.open(image_path).convert("RGB")
    image = enhance_image(image, sharpness)

    original_width, original_height = image.size
    aspect_ratio = original_height / original_width

    if height is None:
        height = int(width * aspect_ratio * 0.55)

    image = image.resize((width, height))
    pixels = list(image.getdata())

    lines = []
    for i in range(0, len(pixels), width):
        line = ""
        for j in range(width):
            if i + j < len(pixels):
                r, g, b = pixels[i + j]
                brightness = int((r + g + b) / 3)
                char = ASCII_CHARS[brightness * len(ASCII_CHARS) // 256]
                if use_color:
                    line += f"{get_color(r, g, b)}{char}{Style.RESET_ALL}"
                else:
                    line += char
        lines.append(line)

    if output_path:
        # Strip ANSI codes if writing non-colored output
        with open(output_path, "w", encoding="utf-8") as f:
            for line in lines:
                f.write(line + "\n")
        print(f"[+] ASCII art written to {output_path}")
    else:
        for line in lines:
            print(line)

# CLI Interface
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert image to colored ASCII.")
    parser.add_argument("image", help="Path to image file (PNG, JPG, etc.)")
    parser.add_argument("--width", type=int, default=80, help="Output width in characters")
    parser.add_argument("--height", type=int, help="Exact output height in characters")
    parser.add_argument("--sharpness", type=float, default=1.0, help="Sharpness enhancement")
    parser.add_argument("--output", type=str, help="Write ASCII art to this .txt file")
    parser.add_argument("--no-color", action="store_true", help="Output plain ASCII (no color)")

    args = parser.parse_args()

    to_ascii(
        image_path=args.image,
        width=args.width,
        height=args.height,
        sharpness=args.sharpness,
        output_path=args.output,
        use_color=not args.no_color
    )

