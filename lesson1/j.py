import re
from sys import stdin


def place_images(w, h, c, document):
    image_list = []
    last_floating = False
    floating_x, floating_y = 0, 0
    fragment = {"fragment_width": 0, "height": h,
                "start_x": 0,
                "start_y": 0}

    def get_possible_width(x, y):
        result = w-x
        min = w-x
        for i, image in enumerate(image_list):
            if image["y"]+image["height"] <= y:
                continue
            if x < image["x"] and y > image["y"] and y <= image["y"]+image["height"]:
                result = image["x"]-x
                if result < min:
                    min = result
        return min

    def create_fragment(start_x, start_y):
        nonlocal fragment
        current_height = fragment["height"]
        x = start_x
        y = start_y
        if x >= w or (x == 0):
            y += current_height
            current_height = h
            x = 0
        width = 0
        while x < w:
            for i, image in enumerate(image_list):
                if image["y"]+image["height"] <= y:
                    continue
                if (x >= image["x"] and x <= image["x"]+image["width"]) and (
                        y >= image["y"] and y < image["y"]+image["height"]):
                    x = image["x"]+image["width"]
            if x >= w:
                x = 0
                y += current_height
                current_height = h
            else:
                break
        width = get_possible_width(x, y)
        fragment = {"width": width, "height": current_height,
                    "start_x": x,
                    "start_y": y}
        # new current_y, current_x
        return y, 0

    def process_paragraph(paragraph, current_y, current_x):
        nonlocal last_floating
        last_floating = False
        current_y, current_x = create_fragment(
            current_x, current_y)
        for element in paragraph:
            if element.startswith("(image"):
                image_params = parse_image_parameters(element)
                current_y, current_x = place_image(
                    image_params, current_y, current_x)
            else:
                words = element.split()
                for word in words:
                    word_width = len(word) * c
                    space = 0 if current_x == 0 else c
                    while word_width+current_x+space > fragment["width"]:
                        # TODO Word doesn't fit in the current fragment, move to the next line
                        current_y, current_x = create_fragment(
                            fragment["start_x"]+fragment["width"], current_y)
                        space = 0 if current_x == 0 else c
                        pass

                    if current_x != 0:
                        # Add space before the word (except for the first word in the fragment)
                        current_x += c
                    # place the word
                    current_x += word_width
                    last_floating = False

        return current_y, 0

    def parse_image_parameters(paragraph):
        image_params = {}
        # Избавляемся от "(image" в начале и ")" в конце строки
        image_str = re.search(r"\(image([^\(\)]+)\)", paragraph,
                              re.MULTILINE).group(1).strip()
        # Разбиваем строку на параметры
        params_list = re.split(" |\n", image_str)

        for param in params_list:
            if '=' in param:
                key, value = param.split('=')
                image_params[key] = value

        return image_params

    def place_image(image_params, current_y, current_x):
        nonlocal last_floating
        nonlocal floating_x, floating_y
        layout = image_params["layout"]
        if layout != "floating":
            last_floating = False
        width, height = int(image_params["width"]), int(image_params["height"])
        x, y = fragment["start_x"]+current_x, current_y
        if layout == "embedded":
            # Размещение рисунка с типом "embedded"
            space = 0 if current_x == 0 else c
            while width+current_x + space > fragment["width"]:
                # TODO Word doesn't fit in the current fragment, move to the next line
                current_y, current_x = create_fragment(
                    fragment["start_x"]+fragment["width"], current_y)
                x, y = fragment["start_x"]+current_x, current_y
                space = 0 if current_x == 0 else c
            x += space
            current_x += space
            if height > fragment["height"]:
                fragment["height"] = height
            print(f"{x} {current_y}")
            return current_y, current_x + width  # Update current_x

        elif layout == "surrounded":
            # Размещение рисунка с типом "surrounded"
            while width+current_x > fragment["width"]:
                # TODO Word doesn't fit in the current fragment, move to the next line
                current_y, current_x = create_fragment(
                    fragment["start_x"]+fragment["width"], current_y)
                x, y = fragment["start_x"]+current_x, current_y
                pass
            image_list.append(
                {"x": x, "y": y, "width": width, "height": height})
            print(f"{x} {y}")
            current_y, current_x = create_fragment(x+width, y)

            return current_y, 0

        elif layout == "floating":
            # Размещение рисунка с типом "floating"
            if last_floating:
                x = floating_x
                y = floating_y
            dx, dy = int(image_params.get("dx", 0)), int(
                image_params.get("dy", 0))
            if x + dx < 0:
                # Если рисунок выходит за левую границу страницы, смещаем его вправо
                x = 0
            elif x + width + dx > w:
                # Если рисунок выходит за правую границу страницы, смещаем его влево
                x = w - width
            else:
                x += dx
            y += dy
            print(f"{x} {y}")
            last_floating = True
            floating_x = x+width
            floating_y = y
            return current_y, current_x

    document = re.sub(r"\n\n+", "\n\n", document)
    document = re.sub(r"\n\s+\n", "\n\n", document)
    paragraphs = document.split("\n\n")
    current_y, current_x = -h, 0

    for paragraph in paragraphs:
        # Разбиваем абзац на элементы
        paragraph = re.findall(
            r"\(image[^\(\)]+\)|[^\(\)]+", paragraph, re.MULTILINE)
        current_y, current_x = process_paragraph(
            paragraph,  current_y, current_x)


if __name__ == "__main__":
    w, h, c = map(int, input().split())
    document = stdin.read()

    place_images(w, h, c, document)
