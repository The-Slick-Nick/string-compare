import time

def letter_score(str1: str, str2: str) -> float:
    """
    Compares two provided strings and provides a floating point assessment
    (0-1) of how similar the character distributions of the two strings are.
    """
    c_dist = [0] * 255

    max_diff = 0  # Maximum possible difference between the two
    actual_diff = 0  # Calculated difference between the two

    # Increment for str1
    for chr1 in str1:
        max_diff += 1
        c_dist[ord(chr1)] += 1

    # Decrement for str2
    for chr2 in str2:
        max_diff += 1
        c_dist[ord(chr2)] -= 1

    for diff_val in c_dist:
        actual_diff += abs(diff_val)

    return (max_diff - actual_diff)/max_diff

def order_score(str1: str, str2: str) -> float:
    str1_dist = dict()
    str2_dist = dict()
    num_common = 0

    for chr1 in str1:
        try:
            str1_dist[chr1] += 1
        except KeyError:
            str1_dist[chr1] = 1

    for chr2 in str2:
        try:
            str2_dist[chr2] += 1
        except KeyError:
            str2_dist[chr2] = 1

    str1_common = []
    for chr1 in str1:
        try:
            if str2_dist[chr1] > 0:
                str1_common.append(chr1)
                str2_dist[chr1] -= 1
                num_common += 1
        except KeyError:
            pass

    str2_common = []
    for chr2 in str2:
        try:
            if str1_dist[chr2] > 0:
                str2_common.append(chr2)
                str1_dist[chr2] -= 1
        except KeyError:
            pass

    num_segments = 0
    i2_min = -1
    i1 = 0
    i2 = 0

    while i1 < len(str1_common):
        i2 = 0
        num_segments += 1
        while i2 < len(str2_common) and i1 < len(str1_common):
            if str1_common[i1] == str2_common[i2]:
                str2_common[i2] = chr(0)
                i1 += 1
            i2 += 1


    return ((num_common - 1) - (num_segments - 1)) / (num_common - 1)


def string_compare(str1: str, str2: str) -> float:
    return (letter_score(str1, str2) * order_score(str1, str2)) ** 0.5



def time_test(str1, str2):
    # 100k lscore
    st = time.time()
    for i in range(100000):
        letter_score(str1, str2)
    et = time.time()
    print("letter score time {}".format(et - st))

    # 100k oscore
    st = time.time()
    for i in range(100000):
        order_score(str1, str2)
    et = time.time()
    print("order score time {}".format(et - st))

    # 100k sc
    st - time.time()
    for i in range(100000):
        string_compare(str1, str2)
    et = time.time()
    print("string compare time {}".format(et - st))



if __name__ == "__main__":
    time_test("123 main street", "123 oak avenue")