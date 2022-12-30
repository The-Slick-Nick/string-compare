import ctypes
import time

from py_version.string_compare import string_compare as py_string_compare

c_lib = ctypes.CDLL("D:\Projects\string-compare\c_version\string_compare.so")
c_lib.string_compare.restype = ctypes.c_float
c_lib.string_compare.argtypes = [ctypes.c_char_p, ctypes.c_char_p]

def c_string_compare(str1: str, str2: str) -> float:
    """
    Wrap c's string compare function in a bytes conversion for easy calling
    """
    return c_lib.string_compare(
        bytes(str1, 'ascii'),
        bytes(str2, 'ascii')
    )



def main():
    string1 = "123 main street"
    string2 = "456 oak avenue apt 123"

    py_score = py_string_compare(string1, string2)
    c_score = c_string_compare(string1, string2)

    print(f"py score {py_score}")
    print(f"c score {c_score}")

    st = time.time()
    # 1000 py_string_compare results
    for i in range(100000):
        py_string_compare(string1, string2)

    et = time.time()
    print("py_string_compare time {}".format(et - st))

    st = time.time()
    # 1000 c_string_compare results
    for i in range(100000):
        c_string_compare(string1, string2)

    et = time.time()
    print("c_string_compare time {}".format(et - st))


    
if __name__ == "__main__":
    main()
