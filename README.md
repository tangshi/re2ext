This is an extension of [google::re2](https://github.com/google/re2) library which provides some convenient pythonic API


**Features:**

- `MatchObject` class to store the match result similar in python re module
- Some convenient pythonic APIs (including: `match`, `search`, `findall`, `sub`), see [header file](re2ext.h) for detail.


**Usage:**

- install [google::re2](https://github.com/google/re2) library
- compile this library, you can compile by cmake or raw g++ command:

        # Use cmake style
        cmake . && make

        # Or use raw g++ command
        g++ *.cc -std=c++11 -fPIC -shared -pthread -lre2 -o libre2ext.so
- demo:

        # you can run demo by this
        g++ demo.cpp -std=c++11 -L. -lre2 -lre2ext -o demo.exe
        ./demo.exe
