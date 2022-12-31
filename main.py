import ctypes
import time

from strcompare import string_compare as c_string_compare
from py_version.string_compare import string_compare as py_string_compare


# c_lib = ctypes.CDLL("D:\Projects\string-compare\c_version\string_compare.so")
# c_lib.string_compare.restype = ctypes.c_float
# c_lib.string_compare.argtypes = [ctypes.c_char_p, ctypes.c_char_p]

# def c_string_compare(str1: str, str2: str) -> float:
#     """
#     Wrap c's string compare function in a bytes conversion for easy calling
#     """
#     return c_lib.string_compare(
#         bytes(str1, 'ascii'),
#         bytes(str2, 'ascii')
#     )



def main():
    string1 = "Since C is a structured language, it has some fixed rules for programming. One of them includes "
    string2 = "As it can be seen that the length (size) of the array above made is 9. But what if there is a requirement"

    py_score = py_string_compare(string1, string2)
    c_score = c_string_compare(string1, string2)

    print(f"py score {py_score}")
    print(f"c score {c_score}")

    # Number of string_compare executions per lang
    num_py = 0
    num_c = 0

    st = time.time()
    while time.time() - st < 10:
        py_string_compare(string1, string2)
        num_py += 1

    print(f"{num_py} pytyhon comparisons made in 10 seconds")

    st = time.time()
    while time.time() - st < 10:
        c_string_compare(string1, string2)
        num_c += 1

    print(f"{num_c} c comparisons made in 10 seconds")


    
if __name__ == "__main__":
    main()
