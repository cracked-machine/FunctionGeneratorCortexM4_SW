

from createfile import write_to_header_file, write_to_source_file

x1 = []

def grey_fade():

    for i in range(0, 320):

        red = 0
        green = 0
        blue = 0

        red = int(i/10)
        red = red << 11
        green = int(i/5)
        green = green << 5
        blue = int(i/10)

        rgb = red + green + blue
        x1.append(rgb)
        print(rgb)


def red_fade():

    for i in range(0, 320):

        red = 0
        green = 0
        blue = 0

        red = int(i/10)
        red = red << 11
        green = int(i/10)
        green = green << 5
        blue = int(i/30)

        rgb = red + green + blue
        x1.append(rgb)
        print(rgb)





def yellow_fade():

    for i in range(0, 320):

        red = 0
        green = 0
        blue = 0

        red = int(i/10)
        red = red << 11
        green = int(i/5)
        green = green << 5
        blue = int(i/30)

        rgb = red + green + blue
        x1.append(rgb)
        print(rgb)


def magenta_fade():

    for i in range(0, 320):

        red = 0
        green = 0
        blue = 0

        red = int(i/10)
        red = red << 11
        green = int(i/10)
        green = green << 5
        blue = int(i/10)

        rgb = red + green + blue
        x1.append(rgb)
        print(rgb)


def purple_fade():

    for i in range(0, 320):

        red = 0
        green = 0
        blue = 0

        red = int(i/15)
        red = red << 11
        green = int(i/10)
        green = green << 5
        blue = int(i/10)

        rgb = red + green + blue
        x1.append(rgb)
        print(rgb)


def green_fade():

    for i in range(0, 320):

        red = 0
        green = 0
        blue = 0

        red = int(i/30)
        red = red << 11
        green = int(i/5)
        green = green << 5
        blue = int(i/30)

        rgb = red + green + blue
        x1.append(rgb)
        print(rgb)


def blue_fade():

    for i in range(0, 320):

        red = 0
        green = 0
        blue = 0

        red = int(i/30)
        red = red << 11
        green = int(i/30)
        green = green << 5
        blue = int(i/10)

        rgb = red + green + blue
        x1.append(rgb)
        print(rgb)


grey_fade()
# red_fade()
# yellow_fade()
# purple_fade()
# magenta_fade()
# green_fade()
# blue_fade()


write_to_header_file(x1, "fade_log_seq", "fade_log_seq.h")
write_to_source_file(x1, "fade_log_seq", "fade_log_seq.c", "fade_log_seq.h")
