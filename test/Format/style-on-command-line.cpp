// RUN: grep -Ev "// *[A-Z0-9_]+:" %s > %t.cpp
// RUN: clang-format -style="{BasedOnStyle: Google, IndentWidth: 8}" %t.cpp | FileCheck -strict-whitespace -check-prefix=CHECK1 %s
// RUN: clang-format -style="{BasedOnStyle: LLVM, IndentWidth: 7}" %t.cpp | FileCheck -strict-whitespace -check-prefix=CHECK2 %s
// RUN: clang-format -style="{BasedOnStyle: invalid, IndentWidth: 7}" %t.cpp 2>&1 | FileCheck -strict-whitespace -check-prefix=CHECK3 %s
// RUN: clang-format -style="{lsjd}" %t.cpp 2>&1 | FileCheck -strict-whitespace -check-prefix=CHECK4 %s
// RUN: [ ! -e %T/.clang-format ] || rm %T/.clang-format
// RUN: printf "BasedOnStyle: google\nIndentWidth: 5\n" > %T/.clang-format
// RUN: clang-format -style=file %t.cpp 2>&1 | FileCheck -strict-whitespace -check-prefix=CHECK5 %s
// RUN: printf "\n" > %T/.clang-format
// RUN: clang-format -style=file %t.cpp 2>&1 | FileCheck -strict-whitespace -check-prefix=CHECK6 %s
// RUN: [ ! -e %T/.clang-format ] || rm %T/.clang-format
// RUN: [ ! -e %T/_clang-format ] || rm %T/_clang-format
// RUN: printf "BasedOnStyle: google\nIndentWidth: 6\n" > %T/_clang-format
// RUN: clang-format -style=file %t.cpp 2>&1 | FileCheck -strict-whitespace -check-prefix=CHECK7 %s
void f() {
// CHECK1: {{^        int\* i;$}}
// CHECK2: {{^       int \*i;$}}
// CHECK3: Unknown value for BasedOnStyle: invalid
// CHECK3: Error parsing -style: Invalid argument, using LLVM style
// CHECK3: {{^  int \*i;$}}
// CHECK4: Error parsing -style: Invalid argument, using LLVM style
// CHECK4: {{^  int \*i;$}}
// CHECK5: {{^     int\* i;$}}
// CHECK6: {{^Error reading .*\.clang-format: Invalid argument}}
// CHECK6: {{^  int \*i;$}}
// CHECK7: {{^      int\* i;$}}
int*i;
int j;
}
