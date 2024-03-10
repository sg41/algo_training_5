import re
from sys import stdin


def place_images(w, h, c, document):
    image_list = []
    fragment = {"fragment_width": 0, "height": h,
                "start_x": 0,
                "start_y": 0}

    def get_possible_width(x, y):
        result = w-x
        min = w-x
        for i, image in enumerate(image_list):
            if image["y"]+image["height"] < y:
                image_list.pop(i)
                continue
            if x < image["x"] and y > image["y"] and y < image["y"]+image["height"]:
                result = image["x"]-x
                if result < min:
                    min = result
        return min

    def create_fragment(start_x, start_y):
        nonlocal fragment
        for i, image in enumerate(image_list):
            if image["y"]+image["height"] < start_y:
                image_list.pop(i)
                continue
            if start_x > image["x"] and start_x < image["x"]+image["width"] and image["y"] > start_y and image["y"] < start_y+fragment["height"]:
                x = image["x"]+image["width"]
                break
        x = start_x
        if x >= w:
            x = 0

        if x == 0:
            y = start_y+fragment["height"]
        else:
            y = start_y

        fragment = {"width": get_possible_width(x, y), "height": h,
                    "start_x": x,
                    "start_y": y}
        # new current_y, current_x
        return current_y+fragment["height"], 0

    def process_paragraph(paragraph, current_y, current_x):
        create_fragment(current_x, current_y)
        for element in paragraph:
            if element.startswith("(image"):
                image_params = parse_image_parameters(element)
                current_y, current_x = place_image(
                    image_params, current_y, current_x)
            else:
                words = element.split()
                for word in words:
                    fragment_width = fragment["width"]
                    word_width = len(word) * c
                    if word_width+current_x > fragment_width:
                        # Word doesn't fit in the current fragment, move to the next line
                        # TODO look for the next fragment o create new one
                        current_y, current_x = create_fragment(
                            word_width+current_x+fragment["start_x"], current_y)
                        pass

                    # place the word
                    if current_x != 0:
                        # Add space before the word (except for the first word in the fragment)
                        current_x += c
                    current_x += word_width

        return current_y, current_x

    def parse_image_parameters(paragraph):
        image_params = {}
        # Избавляемся от "(image" в начале и ")" в конце строки
        image_str = re.search(r"\(image(.+)\)", paragraph,
                              re.MULTILINE).group(1).strip()
        # Разбиваем строку на параметры
        params_list = re.split(" |\n", image_str)

        for param in params_list:
            if '=' in param:
                key, value = param.split('=')
                image_params[key] = value

        return image_params

    def place_image(image_params, current_y, current_x):
        layout = image_params["layout"]
        width, height = int(image_params["width"]), int(image_params["height"])
        # fragment_start_x = fragment["start_x"]
        # fragment_width = fragment["fragment_width"]
        x, y = fragment["start_x"]+current_x, current_y
        if layout == "embedded":
            if width+current_x > fragment["width"]:
                # Word doesn't fit in the current fragment, move to the next line
                # TODO look for the next fragment o create new one
                current_y, current_x = create_fragment(
                    width+current_x+fragment["start_x"], current_y)
                # fragment_start_x = fragment["start_x"]
                # fragment_width = fragment["fragment_width"]
                pass

            if current_x != fragment["start_x"]:
                # Add space before the image (except for the first word in the fragment)
                current_x += c
            # Размещение рисунка с типом "embedded"
            if height > h:
                # Если высота рисунка больше текущей высоты строки, увеличиваем высоту строки
                fragment["height"] = height
            print(f"{current_x} {current_y}")
            return current_y, current_x + width  # Update current_x

        elif layout == "surrounded":
            # Размещение рисунка с типом "surrounded"
            if width+current_x > fragment["width"]:
                # Word doesn't fit in the current fragment, move to the next line
                # TODO look for the next fragment o create new one
                current_y, current_x = create_fragment(0, current_y)
                x, y = fragment["start_x"]+current_x, current_y
                pass
            image_list.append(
                {"x": x, "y": y, "width": width, "height": height})
            print(f"{x} {y}")
            current_y, current_x = create_fragment(x+width, current_y)

            return current_y, 0

        elif layout == "floating":
            # Размещение рисунка с типом "floating"
            dx, dy = int(image_params.get("dx", 0)), int(
                image_params.get("dy", 0))
            if x + dx < 0:
                # Если рисунок выходит за левую границу страницы, смещаем его вправо
                x = 0
            elif x + width + dx > w:
                # Если рисунок выходит за правую границу страницы, смещаем его влево
                x = width-w
            y += dy
            x += dx
            print(f"{x} {y}")
            return current_y, current_x  # Update current_x

    document = re.sub(r"\n\n+", "\n\n", document)
    document = re.sub(r"\n\s+\n", "\n\n", document)
    paragraphs = document.split("\n\n")
    current_y, current_x = 0, 0

    for paragraph in paragraphs:
        # Разбиваем абзац на элементы
        paragraph = re.findall(r"[^\(]+|\(image.+\)", paragraph, re.MULTILINE)
        current_y, current_x = process_paragraph(
            paragraph,  current_y, current_x)


if __name__ == "__main__":
    w, h, c = map(int, input().split())
    document = stdin.read()

    place_images(w, h, c, document)
