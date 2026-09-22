// ECCS 2671 - Project 1 autograder.
//
// Runs 8 function-group tests (4 for Student 1, 4 for Student 2), each in
// its own forked process so a crash or infinite loop in one group can't
// take down the rest. Each group is graded pass/fail as a whole.
//
// Default (quiet) mode -- what runs in CI and what students see -- prints
// only aggregate pass/fail counts, no per-case detail.
//
// Run with --verbose to see which group failed and why (for grading use,
// not shown in the CI log).
//
// Memory-leak checking: when this file is compiled with
// -fsanitize=address (the `make memcheck` / `make memcheck-verbose`
// targets do this; plain `make test` does not), each group that passes
// functionally is additionally checked for leaks via LeakSanitizer's
// recoverable check, and the summary gains a "Memory:" line. This piggy-
// backs on the same fork-isolated groups above rather than a separate
// test file, so leak checking always exercises the exact same scenarios
// as the correctness checks.

#include "../MusicPlaylist.h"
#include <sstream>
#include <functional>
#include <vector>
#include <string>
#include <cstring>
#include <csignal>
#include <sys/wait.h>
#include <unistd.h>

#if defined(__SANITIZE_ADDRESS__)
#include <sanitizer/lsan_interface.h>
#define MEMCHECK_ENABLED 1
#endif

using namespace std;

struct AssertFail {
    string message;
};

static void expectEq(const string& actual, const string& expected, const string& label) {
    if (actual != expected) {
        throw AssertFail{label + ": expected [" + expected + "] got [" + actual + "]"};
    }
}
static void expectEqInt(int actual, int expected, const string& label) {
    if (actual != expected) {
        throw AssertFail{label + ": expected " + to_string(expected) + " got " + to_string(actual)};
    }
}

static string captured(MusicPlaylist& p) {
    ostringstream oss;
    oss << p;
    return oss.str();
}

// ---------------------------------------------------------------------
// STUDENT 1 test groups
// ---------------------------------------------------------------------
static void test_s1_addSong_head() {
    MusicPlaylist p;
    p.addSong("A");
    expectEq(captured(p), "1. A\n", "head insert into empty list");
    expectEqInt(p.getNumSongs(), 1, "count after 1 head insert");
    p.addSong("B");
    expectEq(captured(p), "1. B\n2. A\n", "head insert shifts existing song down");
    expectEqInt(p.getNumSongs(), 2, "count after 2 head inserts");
}

static void test_s1_addSong_order() {
    MusicPlaylist p;
    p.addSong("B", 1);
    p.addSong("A", 1);      // < 2 -> head
    p.addSong("C", 3);      // > numSongs -> tail
    p.addSong("M", 2);      // true middle
    expectEq(captured(p), "1. A\n2. M\n3. B\n4. C\n", "addSong(name, order) boundary + middle");
    expectEqInt(p.getNumSongs(), 4, "count after order inserts");
}

static void test_s1_deleteSong_byName() {
    MusicPlaylist p;
    p.addSong("C");
    p.addSong("B");
    p.addSong("A");  // list: A, B, C
    p.deleteSong("B");
    expectEq(captured(p), "1. A\n2. C\n", "delete middle by name");
    p.deleteSong("A");
    expectEq(captured(p), "1. C\n", "delete head by name");
    p.deleteSong("C");
    expectEq(captured(p), "Empty Play List\n", "delete only node by name");
    expectEqInt(p.getNumSongs(), 0, "count after deleting all");
    p.deleteSong("nope");  // no-op, should not crash
    expectEqInt(p.getNumSongs(), 0, "count unaffected by deleting missing song");
}

static void test_s1_getSongNum() {
    MusicPlaylist p;
    p.addSong("C");
    p.addSong("B");
    p.addSong("A");  // list: A, B, C
    expectEqInt(p.getSongNum("A"), 1, "getSongNum head");
    expectEqInt(p.getSongNum("C"), 3, "getSongNum tail");
    expectEqInt(p.getSongNum("nope"), -1, "getSongNum missing song");
}

// ---------------------------------------------------------------------
// STUDENT 2 test groups
// ---------------------------------------------------------------------
static void test_s2_addSong_orderArtist() {
    MusicPlaylist p;
    p.addSong("B", 1, "X");
    p.addSong("A", 1, "Y");   // < 2 -> head
    p.addSong("C", 3, "Z");   // > numSongs -> tail
    p.addSong("M", 2, "");    // true middle, empty artist
    expectEq(captured(p), "1. A - Y\n2. M\n3. B - X\n4. C - Z\n", "addSong(name, order, artist)");
    expectEqInt(p.getNumSongs(), 4, "count after order+artist inserts");
}

static void test_s2_deleteLastSong() {
    MusicPlaylist p;
    p.addSong("A", 1, "");
    p.addSong("B", 2, "");
    p.addSong("C", 3, "");
    p.deleteLastSong();
    expectEq(captured(p), "1. A\n2. B\n", "deleteLastSong once");
    p.deleteLastSong();
    expectEq(captured(p), "1. A\n", "deleteLastSong twice");
    p.deleteLastSong();
    expectEq(captured(p), "Empty Play List\n", "deleteLastSong to empty");
    p.deleteLastSong();  // no-op on empty, should not crash
    expectEqInt(p.getNumSongs(), 0, "count stays 0 after extra deleteLastSong");
}

static void test_s2_deleteSong_byPosition() {
    MusicPlaylist p;
    p.addSong("A", 1, "");
    p.addSong("B", 2, "");
    p.addSong("C", 3, "");
    p.addSong("D", 4, "");
    p.deleteSong(2);  // middle
    expectEq(captured(p), "1. A\n2. C\n3. D\n", "delete middle by position");
    p.deleteSong(1);  // head (< 2)
    expectEq(captured(p), "1. C\n2. D\n", "delete head by position < 2");
    p.deleteSong(5);  // tail (>= numSongs)
    expectEq(captured(p), "1. C\n", "delete tail by position >= numSongs");
    p.deleteSong(1);  // only node
    expectEq(captured(p), "Empty Play List\n", "delete only node by position");
}

static void test_s2_getSongName() {
    MusicPlaylist p;
    p.addSong("A", 1, "");
    p.addSong("B", 2, "");
    p.addSong("C", 3, "");
    expectEq(p.getSongName(1), "A", "getSongName exact position");
    expectEq(p.getSongName(2), "B", "getSongName exact position");
    expectEq(p.getSongName(0), "A", "getSongName position < 2 -> head");
    expectEq(p.getSongName(10), "C", "getSongName position >= numSongs -> tail");

    MusicPlaylist empty;
    expectEq(empty.getSongName(1), "Empty Play List", "getSongName on empty list");
}

// ---------------------------------------------------------------------
// Group registry + fork-isolated runner
// ---------------------------------------------------------------------
struct TestGroup {
    string owner;
    string name;
    function<void()> fn;
};

static vector<TestGroup> allGroups() {
    return {
        {"Student 1", "addSong(name) - head insert", test_s1_addSong_head},
        {"Student 1", "addSong(name, order) - boundary + middle", test_s1_addSong_order},
        {"Student 1", "deleteSong(string)", test_s1_deleteSong_byName},
        {"Student 1", "getSongNum(string)", test_s1_getSongNum},
        {"Student 2", "addSong(name, order, artist)", test_s2_addSong_orderArtist},
        {"Student 2", "deleteLastSong()", test_s2_deleteLastSong},
        {"Student 2", "deleteSong(int)", test_s2_deleteSong_byPosition},
        {"Student 2", "getSongName(int)", test_s2_getSongName},
    };
}

// Runs one group in a forked child (5-second timeout via alarm). Returns
// true if the child exited 0 (functionally correct), false otherwise
// (assertion failure, crash, or timeout). failMessage is filled only when
// verbose is needed. When built with ASan (MEMCHECK_ENABLED), a group that
// passes is additionally checked for leaks before the child exits; leaked
// is set to true if LeakSanitizer found any. leaked is left false (not
// "unknown") for a group that didn't pass, since we don't grade leaks on
// broken functionality.
static bool runIsolated(const TestGroup& g, string& failMessage, bool verbose, bool& leaked) {
    leaked = false;
    pid_t pid = fork();
    if (pid == 0) {
        // child
        alarm(5);
        try {
            g.fn();
#ifdef MEMCHECK_ENABLED
            // Recoverable leak check: reports (to stderr, via the
            // sanitizer runtime) and returns nonzero if leaks are found,
            // without aborting the process -- unlike the default
            // exit-time check, which we never reach anyway since we
            // _exit() below.
            int leakCode = __lsan_do_recoverable_leak_check();
            _exit(leakCode != 0 ? 4 : 0);
#else
            _exit(0);
#endif
        } catch (const AssertFail& f) {
            if (verbose) {
                fprintf(stderr, "%s\n", f.message.c_str());
            }
            _exit(1);
        } catch (...) {
            _exit(2);
        }
    }
    int status = 0;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return true;
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) == 4) {
        leaked = true;
        return true;  // functionally correct, just leaky
    }
    if (WIFSIGNALED(status)) {
        failMessage = string("crashed (signal ") + to_string(WTERMSIG(status)) + ")";
    } else if (WIFEXITED(status) && WEXITSTATUS(status) == 2) {
        failMessage = "threw an unexpected exception";
    } else {
        failMessage = "assertion failed";
    }
    return false;
}

int main(int argc, char** argv) {
    bool verbose = (argc > 1 && strcmp(argv[1], "--verbose") == 0);

    auto groups = allGroups();
    int s1Pass = 0, s1Total = 0, s2Pass = 0, s2Total = 0;
#ifdef MEMCHECK_ENABLED
    int leakFreeCount = 0, leakCheckedTotal = 0;
#endif

    for (auto& g : groups) {
        string failMsg;
        bool leaked = false;
        bool ok = runIsolated(g, failMsg, verbose, leaked);
        bool isS1 = (g.owner == "Student 1");
        if (isS1) { s1Total++; if (ok) s1Pass++; }
        else      { s2Total++; if (ok) s2Pass++; }

        if (ok) {
#ifdef MEMCHECK_ENABLED
            leakCheckedTotal++;
            if (!leaked) leakFreeCount++;
#endif
        }

        if (verbose) {
            string status = ok ? (leaked ? "PASS (leak detected)" : "PASS") : ("FAIL - " + failMsg);
            printf("[%s] %-45s %s\n", g.owner.c_str(), g.name.c_str(), status.c_str());
        }
    }

    printf("Student 1: %d/%d function groups passing\n", s1Pass, s1Total);
    printf("Student 2: %d/%d function groups passing\n", s2Pass, s2Total);
    printf("Total:     %d/%d function groups passing\n", s1Pass + s2Pass, s1Total + s2Total);
#ifdef MEMCHECK_ENABLED
    // Only groups that passed functionally are leak-checked, so the
    // denominator here is "of the groups that passed" -- a group that
    // fails functionally never gets to leak (nothing was correctly built
    // to leak in the first place).
    printf("Memory:    %d/%d passing groups leak-free (ASan build)\n", leakFreeCount, leakCheckedTotal);
#endif

    return 0;  // always exit 0 -- this is a report, not a pass/fail gate
}
