import sys
import os
from setuptools import setup, Extension


def main():
    setup(
        name="strcompare",
        version="1.2.1",
        description="Methods to assess string similarity.",
        ext_modules=[Extension("strcompare", ['..\\src\\strcompare_module.c'])]
    )


if __name__ == "__main__":
    main()
