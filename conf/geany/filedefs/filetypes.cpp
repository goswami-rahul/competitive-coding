[build-menu]
FT_00_LB=_Compile
FT_00_CM=g++ -std=c++14 -O2  "%f"  -DRahul 
FT_00_WD=
FT_01_LB=_Build
FT_01_CM=g++ -DRahul  -Wall -Wextra  -std=c++17  -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-misleading-indentation -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector "%f"
FT_01_WD=
EX_00_LB=_Execute
EX_00_CM="./a.out"
EX_00_WD=
FT_02_LB=_Lint
FT_02_CM=cppcheck --language=c++ --enable=warning,style --template=gcc "%f"
FT_02_WD=
