# Version 0.2

# data      -   numpy.ndarray
# filename  -   string


def write_to_header_file(data, dataname, filename):

    fh = open(filename, "w")
    fh.write("/** \n"
             "* @file " + filename + "\n"
             "* @author chris sutton \n"
             "* @brief  \n"
             "* @version 0.1 \n"
             "* @date 18-Mar-2020 \n"
             "* @copyright Copyright (c) 2020 \n"
             "* Generated with Python!\n"
             "*/ \n\n")

    fh.write("#ifndef __" + dataname.upper() + "_H__\n")
    fh.write("#define __" + dataname.upper() + "_H__\n\n")

    fh.write("#include <stdint.h>\n\n")

    fh.write("#define " + dataname.upper() + "_DATA_SIZE " +
             str(len(data)) + "\n")
    fh.write("uint32_t " + dataname + "_data_table[" +
             dataname.upper() + "_DATA_SIZE];")

    fh.write("\n")
    fh.write("\n")
    fh.write("\n")

    fh.write("#endif //__SINE_H__\n\n\n")

    fh.close()


def write_to_source_file(data, dataname, filename, headerfile):

    fh = open(filename, "w")
    fh.write("/** \n"
             "* @file " + filename + "\n"
             "* @author chris sutton \n"
             "* @brief  \n"
             "* @version 0.1 \n"
             "* @date 18-Mar-2020 \n"
             "* @copyright Copyright (c) 2020 \n"
             "* Generated with Python!\n"
             "*/ \n\n")

    fh.write("#include <" + headerfile + ">\n\n")

    fh.write("uint32_t " + dataname + "_data_table[" +
             dataname.upper() + "_DATA_SIZE] = {\n\t")

    for i, item in enumerate(data):
        if i:  # print a separator if this isn't the first element
            fh.write(', ')
        if (i != 0) & (i % 10 == 0):
            fh.write("\n\t")
        fh.write(str((item)))
    fh.write("")  # last newline

    fh.write("\n};\n")


    fh.close()