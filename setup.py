import sys
import os
import sysconfig
from setuptools import setup, Extension, find_packages

from pathlib import Path

this_dir = Path(__file__).parent
long_description = (this_dir / "README.md").read_text()

module_sources = []

# Pick all .c files from main project folder
for filename in os.listdir(os.path.join(this_dir, 'src', 'compare_functions')):
    if filename.endswith(".c"):
        module_sources.append(
            f"src\\compare_functions\\{filename}"
        )

# Include the module file
module_sources.append("src\\strcompare_module.c")

def main():
    setup(
        name="strcompare",
        version="2.0.0",
        description="Methods to assess string similarity.",
        readme="README.md",
        ext_modules=[Extension(
            name="strcompare",
            sources=module_sources
        )],
        author="Slick Nick",
        author_email="nfeezor@gmail.com",
        url="https://github.com/The-Slick-Nick/string-compare",
        long_description=long_description,
        long_description_content_type='text/markdown'
    )


if __name__ == "__main__":
    main()
