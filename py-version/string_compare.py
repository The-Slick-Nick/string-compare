

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


print(letter_score("hello", "good day"))