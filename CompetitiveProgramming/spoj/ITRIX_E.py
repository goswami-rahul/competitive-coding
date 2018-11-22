from __future__ import division, print_function
import itertools
import sys
from atexit import register
if sys.version_info[0] < 3:
    from io import BytesIO as stream
else:
    from io import StringIO as stream
    from math import gcd

if sys.version_info[0] < 3:
    input = raw_input
    range = xrange
    map = itertools.imap

def sync_with_stdio(sync=True):
    global input, flush
    if sync:
        flush = sys.stdout.flush
    else:
        sys.stdin = stream(sys.stdin.read())
        input = lambda: sys.stdin.readline().rstrip('\r\n')
        sys.stdout = stream()
        register(lambda: sys.__stdout__.write(sys.stdout.getvalue()))

def main():
    for _ in range(int(input())):
        m, n = map(int, input().split())
        ans = n * (n - 1);
        ans -= (2 * n - 1);
        ans *= 3;
        ans += (2 * m - 1);
        print(ans * m * (m - 1) // 3);

if __name__ == '__main__':
    sync_with_stdio(False)
    if 'PyPy' in sys.version:
        from _continuation import continulet
        def bootstrap(c):
            callable, arg = c.switch()
            while True:
                to = continulet(lambda _, f, x: f(x), callable, arg)
                callable, arg = c.switch(to=to)
        c = continulet(bootstrap)
        c.switch()
        main()
    else:
        import threading
        sys.setrecursionlimit(2097152)
        threading.stack_size(134217728)
        main_thread = threading.Thread(target=main)
        main_thread.start()
        main_thread.join()
