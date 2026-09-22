CXX := g++
CXXFLAGS := -std=c++17 -Wall

playlist: main.o MusicPlaylist.o
	$(CXX) $(CXXFLAGS) -o playlist main.o MusicPlaylist.o

main.o: main.cpp MusicPlaylist.h
	$(CXX) $(CXXFLAGS) -c main.cpp

MusicPlaylist.o: MusicPlaylist.cpp MusicPlaylist.h
	$(CXX) $(CXXFLAGS) -c MusicPlaylist.cpp

test: MusicPlaylist.cpp MusicPlaylist.h tests/test_main.cpp
	$(CXX) $(CXXFLAGS) -o test_runner tests/test_main.cpp MusicPlaylist.cpp
	./test_runner

# Same test groups as `test`, built with AddressSanitizer/LeakSanitizer.
# Quiet: ASan's own leak reports (which include stack traces) go to
# /dev/null, so only our own aggregate summary lines print -- matching
# `test`'s quiet-by-default behavior.
memcheck: MusicPlaylist.cpp MusicPlaylist.h tests/test_main.cpp
	$(CXX) $(CXXFLAGS) -g -O0 -fsanitize=address -o test_runner_asan tests/test_main.cpp MusicPlaylist.cpp
	./test_runner_asan 2>/dev/null

# Same as `memcheck`, but shows ASan's full leak reports (allocation
# stack traces) and per-group PASS/FAIL detail -- for grading use, not
# CI output.
memcheck-verbose: MusicPlaylist.cpp MusicPlaylist.h tests/test_main.cpp
	$(CXX) $(CXXFLAGS) -g -O0 -fsanitize=address -o test_runner_asan tests/test_main.cpp MusicPlaylist.cpp
	./test_runner_asan --verbose

clean:
	rm -f *.o playlist test_runner test_runner_asan

.PHONY: clean test memcheck memcheck-verbose
