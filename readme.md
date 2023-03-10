# strcompare
## A library of string similarity assessment functions.

### Properties
Each string assessment score judges the similarity of two strings as a floating point number. Lower numbers indicate dissimilarity, and higher numbers indicate similarity. As such, 0.0 would indicate completely different strings, while 1.0 would indicate exactly equal strings.

Every string assessment score adheres to the following rules/properties, given comparison function $func$ and strings $x$ and $y$.
* $0.0 <= func(x, y) <= 1.0$ for all valid $x$ and $y$
* $func(x, y) = 1.0$ if $x = y$
* $func(x, y) = func(y, x)$ for all valid $x$ and $y$
* $func(x, y) = 0$ if $x$ and $y$ share no common characters.
    * As a corollary, $func(x, y) = 0$ if exactly one of $x$ and $y$ are empty.

<br />
<br />

### Scoring Functions
#### **cdist_score**
`Character Distribution Score`. Generates a score by comparing the difference in distribution of characters between the two strings.
#### **lcs_score**
`Longest Common Substring` score. Returns the ratio of the longest substring common to both strings to the length of the shorter string.
```
Example:
STRESSED | DESSERT
STR____D | D____RT => ESSE
---------------------------
Substring length = 4
Short string length = 7
lcs_score = 4/7 ~= 0.57
```
#### **naive_lcs_score**
`Naive Longest Common Substring Score` Calculates the same as above using a naive algorithm. 
#### **fss_score**
`Fractured Substring Score` Assesses similarity by comparing groups of characters in the same relative order between the two strings. The greater the number of relative order character matches, the higher the score.
```
Example:
STRESSED | DESSERT
__RESSED | DE_SER_ => ST
___ESSED | DE_SE__ => R
_____S_D | D______ => ESE
_____S__ | _______ => D 
```
#### **naive_fss_score**
`Naive Fractured Substring Score` Performs the above assessment using a naive algorithm.
#### **adjusted_fss_score**
`Adjusted Fractured Substring Score` Identifies "fractured substrings" between the two strings, assessing a penalty for characters with different offsets between the first two strings.
*In the example above, the substring ST would assess a penalty due to ST being in indices 0 and 1 in the first string, but 2 and 6 in the second. (Offset of 1 vs offset of 4)* 
#### **naive_adjusted_fss_score**
`Naive Adjusted Fractured Substring Score` Performs the above assessment using a naive algorithm.
#### **levenshtein_score**
`Levenshtein Score` Assigns a score based on the levenshtein distance between the two strings. Final score is calculated by comparing the calculated levenshtein distance to the maximum possible levenshtein distance based on the string lengths.

Let $m$ be the maximum possible levenshtein distance and $s$ be the calculated distance. Final score is calculated as ${(m - s) \over m}$




