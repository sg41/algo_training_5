import re
from sys import stdin


def place_images(w, h, c, document):
    def process_paragraph(paragraph, current_y, current_x):
        fragment_width = 0
        for element in paragraph:
            if element.startswith("(image"):
                image_params = parse_image_parameters(element)
                current_y, current_x = place_image(fragment_width,
                                                   image_params, current_y, current_x)
                fragment_width = 0  # Reset fragment width after placing an image
            else:
                words = element.split()
                for word in words:
                    if (word == "\n"):
                        current_y += h
                        current_x = 0
                        fragment_width = 0
                        continue
                    word_width = len(word) * c
                    if fragment_width + word_width > w:
                        # Word doesn't fit in the current fragment, move to the next line
                        current_y += h
                        current_x = 0
                        fragment_width = 0
                    if fragment_width > 0:
                        # Add space before the word (except for the first word in the fragment)
                        fragment_width += c
                    current_x += word_width
                    fragment_width += word_width

        return current_y, current_x

    def parse_image_parameters(paragraph):
        image_params = {}
        # Избавляемся от "(image" в начале и ")" в конце строки
        image_str = re.search(r"\(image(.+)\)", paragraph,
                              re.MULTILINE).group(1).strip()
        # Разбиваем строку на параметры
        params_list = re.split(" |\n", image_str)

        for param in params_list:
            key, value = param.split('=')
            image_params[key] = value

        return image_params

    def place_image(fragment_width, image_params, current_y, current_x):
        x, y = current_x, current_y
        layout = image_params["layout"]
        width, height = int(image_params["width"]), int(image_params["height"])

        if layout == "embedded":
            if fragment_width > 0:
                # Add space before the image (except for the first word in the fragment)
                current_x += c
            # Размещение рисунка с типом "embedded"
            if current_y + height > h:
                # Если высота рисунка больше текущей высоты строки, увеличиваем высоту строки
                current_y += height - h
            print(f"{current_x} {current_y}")
            return current_y, current_x + width  # Update current_x

        elif layout == "surrounded":
            # Размещение рисунка с типом "surrounded"
            print(f"{x} {y}")
            return current_y, current_x

        elif layout == "floating":
            # Размещение рисунка с типом "floating"
            dx, dy = int(image_params.get("dx", 0)), int(
                image_params.get("dy", 0))
            if x + dx < 0:
                # Если рисунок выходит за левую границу страницы, смещаем его вправо
                dx = -x
            elif x + width + dx > w:
                # Если рисунок выходит за правую границу страницы, смещаем его влево
                dx = w - x - width
            x += dx
            y += dy
            print(f"{x} {y}")
            return y + height, x + width + c  # Update current_x

    # Разбиваем документ на абзацы
    re.sub(r"\n\n+", "\n\n", document)
    re.sub(r"\n\s+\n", "\n\n", document)
    paragraphs = document.split("\n\n")
    current_y, current_x = 0, 0

    for paragraph in paragraphs:
        # # Пропускаем пустые абзацы
        # paragraph = paragraph.strip("\n")
        # if not paragraph:
        #     continue
        # Разбиваем абзац на элементы
        paragraph = re.findall(r"[^\(]+|\(image.+\)", paragraph, re.MULTILINE)
        current_y, current_x = process_paragraph(
            paragraph,  current_y, current_x)


if __name__ == "__main__":
    w, h, c = map(int, input().split())
    document = stdin.read()

    place_images(w, h, c, document)
