# ECCS 2671 — Project 1: Doubly Linked List Implementation (Music Playlist)

## Setup

1. One teammate goes to the starter repo — **[ONU-ECCS2671-FA2026/Project1-DLL](https://github.com/ONU-ECCS2671-FA2026/Project1-DLL)** — and clicks **Use this template → Create a new repository**. This copies all the starter files (including the hidden `.github/workflows` folder) into your own new repo automatically — no manual file uploads needed.
2. Name the new repository following the standard below, set its visibility to **Private**, then add the other teammate as a **collaborator**.
3. **Both** teammates add the instructor as a collaborator: GitHub username `f-jahan` (or email `f-jahan@onu.edu`).
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

### Doing this in VS Code

You don't need the command line for any of this — VS Code's built-in Git support and Source Control panel handle it all.

**Clone the repo:**
1. `Ctrl+Shift+P` → **Git: Clone** → paste your repo's HTTPS URL (from the green **Code** button on GitHub) → pick a folder → click **Open** when prompted.
2. If `Git: Clone` doesn't show up in the command palette, Git itself likely isn't installed — get it from [git-scm.com](https://git-scm.com/download/win), then restart VS Code.

**Create your branch:**
- Click the branch name in the bottom-left status bar → **Create new branch...** → name it with `Student-1` or `Student-2` in it (e.g. `student-1-functions`).

**Commit and push as you go:**
1. Edit `MusicPlaylist.cpp`, then open the **Source Control** panel (left sidebar).
2. Type a commit message, click the checkmark (✓) to commit.
3. Click **Sync Changes** (or the `...` menu → **Push**) to push your branch to GitHub — the first push may ask you to confirm publishing the branch.

**Open a pull request when your functions are done:**
- After pushing, VS Code (with the GitHub Pull Requests extension) or GitHub's website will show a prompt to open a PR comparing your branch into `main`. Your teammate reviews it there, then merges it.

**Merging into `main`:**
- Once the PR is approved, merge it using the **Merge pull request** button on GitHub (or VS Code's GitHub Pull Requests extension) — not a local merge. This way your teammate's review is actually recorded as part of the PR.

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

### Running & debugging in VS Code

The starter repo includes a `.vscode` folder with a build task and a debug configuration already set up, so you don't need to type g++ commands by hand.

**⚠️ Don't use the plain ▶ "Run" button** that appears at the top-right of an open `.cpp` file (or via Code Runner). That button only compiles the *single file you have open* — since this project is split across `main.cpp` and `MusicPlaylist.cpp`, it will fail with "undefined reference" errors because it never sees the other file.

**To build (compile both files together):**
- Press **Ctrl+Shift+B**. This runs the "build" task defined in `.vscode/tasks.json`, which compiles `main.cpp` and `MusicPlaylist.cpp` together into a `playlist` program.

**To run and debug (with breakpoints):**
1. Open the **Run and Debug** panel (left sidebar — the ▶ icon with a bug).
2. Make sure the dropdown at the top says **"Debug Playlist"**.
3. Click the green ▶ (or press **F5**). This builds automatically first, then launches the program under the debugger — set breakpoints by clicking in the left margin next to a line number.

**If debugging won't start:**
- *"Could not find the task 'build'"* → `.vscode/tasks.json` is missing, or wasn't pulled locally yet. Pull the latest from GitHub (or re-clone) and check the file is there.
- *Debugger requires `gdb`* (Windows) → if you installed Git for Windows / MinGW, `gdb` is usually included; if debugging (not building) fails specifically, you can still build with Ctrl+Shift+B and run `.\playlist.exe` from the terminal as a fallback.
- If `Ctrl+Shift+B` still fails with a linker error, double-check `.vscode/tasks.json`'s `args` list includes **both** `main.cpp` and `MusicPlaylist.cpp` — a copy-paste when creating the file can sometimes drop a line.

### Example output (starter code, before any functions are implemented)

Running `./playlist` fresh from the starter files — before Student 1 or Student 2 have implemented anything — produces this. If your output looks like this, your build is working correctly; it just has nothing implemented yet:

```
--- Building the playlist ---
Empty Play List

--- Searching ---
Song number of "Yellow": -1
Song name at position 2: Empty Play List

--- Deleting ---
Empty Play List

Total songs remaining: 0
```


