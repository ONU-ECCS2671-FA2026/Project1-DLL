# ECCS 2671 — Project 1: Doubly Linked List Implementation (Music Playlist)

## Setup

1. One teammate creates a **new GitHub repository** for this project, named following the standard below, and adds the other teammate as a **collaborator**.
2. **Both** teammates add the instructor as a collaborator: `f-jahan@onu.edu`.
3. Add all of the starter files to the repo and push them to `main`, keeping this folder structure:
   ```
   MusicPlaylist.h
   MusicPlaylist.cpp
   main.cpp
   Makefile
   tests/test_main.cpp
   .github/workflows/grade.yml
   ```
4. Each teammate clones the repo locally.

### Repo naming standard

Name your repository:

```
eccs2671-project1-<lastname1>-<lastname2>
```

using both teammates' last names, all lowercase, alphabetized so there's one canonical name for your pair. Example: `eccs2671-project1-patel-smith`.

## Workflow

- Decide who is **Student 1** and who is **Student 2** (see `MusicPlaylist.h` — each function is labeled). Record both names in the header comment at the top of the file.
- Each of you creates your own branch, named with `Student-1` or `Student-2` in it (e.g. `student-1-functions`).
- Implement only the functions labeled for you, in `MusicPlaylist.cpp`. Commit as you go — multiple commits across your working session are encouraged.
- When your functions are done and tested, open a **pull request** for your teammate to review before merging into `main`.
- Both branches must be merged into `main` before your final push — that final push to `main` **is** your submission. This project is submitted through GitHub only.

## Grading

90% individual member-function correctness, 10% for following the branching/pull-request workflow and overall class functionality (see the rubric document for the full point breakdown).

### Automatic checks (GitHub Actions)

Every push and pull request in your repo automatically builds your code and runs a test suite (see the **Actions** tab on GitHub, or the check that appears on your pull request). It reports only pass/fail counts per function group, plus an aggregate memory-leak count — no details about which case failed, why, or where a leak came from:

```
Student 1: X/4 function groups passing
Student 2: Y/4 function groups passing
Total:     N/8 function groups passing

Memory:    M/N passing groups leak-free (ASan build)
```

This is a self-check, not your final grade — it only covers whether your functions produce correct output and whether they leak memory. It does **not** check other things the rubric also grades, like unnecessary code or using the wrong kind of loop, so a full "8/8" with a clean memory line does not guarantee full credit. Use it to catch bugs early, then re-read the rubric before you submit.

You can run the same checks locally at any time:

```
make test        # functional correctness
make memcheck    # same tests, built with AddressSanitizer, leak counts only
```

Add `--verbose` for details on which test failed and why, or (for `memcheck`) the full leak report with the exact allocation site — this only prints locally, it never shows up in the GitHub Actions log:

```
g++ -std=c++17 -Wall -o test_runner tests/test_main.cpp MusicPlaylist.cpp
./test_runner --verbose

make memcheck-verbose   # same, but built with ASan and showing full leak stack traces
```

## Compiling

```
make
./playlist
```

or directly:

```
g++ -std=c++17 -Wall -c main.cpp
g++ -std=c++17 -Wall -c MusicPlaylist.cpp
g++ -std=c++17 -Wall -o playlist main.o MusicPlaylist.o
./playlist
```

The provided `main()` (in `main.cpp` — do not modify it) exercises both students' functions. You can comment out individual calls while you debug your own functions.
