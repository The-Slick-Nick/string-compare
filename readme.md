# strcompare
A library of string similarity assessment functions.

## Properties
Each string assessment score judges the similarity of two strings as a floating point number. Lower numbers indicate dissimilarity, and higher numbers indicate similarity. As such, 0.0 would indicate completely different strings, while 1.0 would indicate exactly equal strings.

Every string assessment score adheres to the following rules/properties, given comparison function $func$ and strings $x$ and $y$.
* $0.0 <= func(x, y) <= 1.0$ for all valid $x$ and $y$
* $func(x, y) = 1.0$ if $x = y$
* $func(x, y) = func(y, x)$ for all valid $x$ and $y$
* $func(x, y) = 0$ if $x$ and $y$ share no common characters.
    * As a corollary, $func(x, y) = 0$ if exactly one of $x$ and $y$ are empty.

Additionally, several different scoring methodologies come with "major" and "minor" variants. Minor variants additionally exhibit the following property:
* $func(x, y) = 1$ if $x \subseteq y$, or $y \subseteq x$

<br />
<br />

## Scoring Functions
Each scoring method derives it score by calculating some metric, then scaling that metric by the length of one or both of the strings. 
Note that "major" variants will scale the metric by the longer string's length, and "minor" variants by the shorter string's length.

#### **Character Distribution**
`Metric` Number of individually matching characters between the two strings<br />
##### Scoring methods
`cdist_score(x, y)` Scales metric the the sum of both lengths
```
Example:
HELLO vs HELP

H E L O
1 1 2 1

H E L P
1 1 1 1

The number of matching characters is 3 (H, E, and L). Since they appear in both, the resulting metric is 2 * 3 = 6. 
As len(HELLO) = 5 and len(HELP) = 4, the scale factor here is 5 + 4 = 9.

cdist_score = 6 / 9 ~= 0.667
```

#### **Longest Substring**
`Metric` The length of the longest sequence of characters appearing in the same order in both strings.<br />
##### Scoring methods
`lss_major(x, y)` Scales metric by the length of the longer string.<br />
`lss_minor(x, y)` Scales metric by the length of the shorter string.
```
Example:
STRESSED | DESSERT
___ESSE_ | _ESSE__
--------------------
The scoring metric here is `4`, as the longest common substring is "ESSE"
lss_major = 4 / 8  = 0.5
lss_minor = 4 / 7 ~= 0.5714
```

#### **Fragmented Substring**
`Metric` The length of the longest sequence of characters appearing in the same relative order in both strings<br />
`Adjusted Metric - Minor` Calculates a metric based on the length of the longer string, assessing "point" penalties for differences in distances between relative character matches between the two strings<br />
`Adjusted Metric - Major` Calculates a metric based on the length of the shorter string, assessing "point" penalties for differences in distances between relative character matches between the two strings<br />
##### Scoring methods
`fss_major(x, y)` Scales $metric$ by the length of the longer string<br />
`fss_minor(x, y)` Scales $metric$ by the length of the shorter string<br />
`adjusted_fss_major(x, y)` Scales major adjusted metric by the product of the lengths of the two strings<br />
`adjusted_fss_minor(x, y)` Scales minor adjusted metric by the product of the lengths of the two strings<br >
```
Example:
BRAKE | BERATE
BRA_E | B_RA_E
----------------
The scoring metric here is 4, as the longest fragmentd substring is "BRAE"
fss_major = 4 / 6 ~= 0.667
fss_minor = 4 / 5  = 0.8
----------------
The adjusted major metric here is 19, as characters BRAE match, but R is 1 character away from B in BRAKE, but 2 characters away from B in BERATE
Thus, adjusted major metric = 5 + (5 - 1) + 5 + 5 = 19  ( 5 is the length of the shorter string BRAKE )
adjusted_fss_major = 19 / (5 * 6) = 19 / 30 ~= 0.633

The adjusted minor metric here is 23, as character BRAE match, but R is 1 character away from B in BRAKE, but 2 characters away from B in BERATE
Thus, adjusted minor metric = 6 + (6 - 1) + 6 + 6 = 23  ( 6 is the length of the longer string BERATE )
adjusted_fss_minor = 23 / (5 * 6) = 23 / 30 ~= 0.767
```

#### **Levenshtein**
`Metric` The levenshtein distance between the two strings subtracted from the longer of the two strings (thus representing the number of already matching characers $i.e.$ non-edits needed).
  * The levenshtein distance is defined as the number of single character edits (removal, addition, replacement) needed to convert one string into the other.
##### Scoring methods
`levenshtein_major(x, y)` Scales $metric$ by the length of the longer string<br />
`levenshtein_minor(x, y)` Scales $metric$ by the length of the shorter string
```
Example
GUMBO vs GAMBOL
_______________
GUMBO  | GAMBOL | 0 - start
GAMBO  | GAMBOL | 1 - modify U to A
GAMBOL | GAMBOL | 2 - add L to right side
------------------------------------------
The scoring metric here is 4
2 is the levenshtein distance, as two character edits will convert GAMBO to GAMBOL. The longer string is GAMBOL, whose length is 6
Thus, metric = 6 - 2 = 4
levenshtein_major = 4 / 6 ~= 0.667
levenshtein_minor = 4 / 5  = 0.8

```

## Extra Utilities
A few extra utilities relating to the above scoring functions are also provided

`substring_length(x, y)` Returns the integer length of the longest common substring between strings $x$ and $y$<br />
`longest_substring(x, y)` Returns a string equal to the longest common substring between strings $x$ and $y$, returning an empty string if there are no common substrings.<br />
`levenshtein_distance(x, y)` Returns an integer representing the levenshtein distance (as defined above) between strings $x$ and $y$.<br />