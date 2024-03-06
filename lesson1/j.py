import re
from sys import stdin


def place_images(w, h, c, document):
    def process_paragraph(paragraph, current_y):
        for element in paragraph:
            if element.startswith("(image"):
                image_params = parse_image_parameters(element)
                current_y = place_image(image_params, current_y)
            else:
                current_y += h
        return current_y

    def parse_image_parameters(image_str):
        image_params = {}
        # Избавляемся от "(image" в начале и ")" в конце строки
        image_str = image_str.replace("(image", "").replace(")", "")
        # Разбиваем строку на параметры
        params_list = image_str.split()

        for param in params_list:
            key, value = param.split('=')
            image_params[key] = value

        return image_params

    def place_image(image_params, current_y):
        x, y = 0, current_y
        layout = image_params["layout"]
        width, height = int(image_params["width"]), int(image_params["height"])

        if layout == "embedded":
            # Размещение рисунка с типом "embedded"
            if current_y + height > h:
                # Если высота рисунка больше текущей высоты строки, увеличиваем высоту строки
                current_y += height - h
            print(f"{x} {y}")
            return current_y

        elif layout == "surrounded":
            # Размещение рисунка с типом "surrounded"
            print(f"{x} {y}")
            return current_y

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
            return y + height

    # Разбиваем документ на абзацы
    re.sub("\n\n+", "\n\n", document)
    re.sub("\n\s+\n", "\n\n", document)
    paragraphs = document.split("\n\n")
    current_y = 0

    for paragraph in paragraphs:
        current_y = process_paragraph(paragraph.split(), current_y)


if __name__ == "__main__":
    w, h, c = map(int, input().split())
    document = stdin.read()

    place_images(w, h, c, document)
