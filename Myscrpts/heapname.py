from colorama import Fore, Style

def shell_sort(s):
    s = list(s)
    n = len(s)
    h = [2, 1]

    for k in h:
        print(f"{Fore.YELLOW}{k}-сортировка{Style.RESET_ALL}")
        for i in range(k, n):
            c = []
            m = []
            s_copy = s.copy()

            t = s[i]
            j = i - k
            while j >= 0:
                c.append(j)
                if t >= s[j]:
                    break

                m.append(j)
                s[j + k] = s[j]
                j -= k
            s[j + k] = t

            for idx in range(n):
                if idx == i:
                    print(Fore.BLUE, end="")
                if idx in c:
                    print("\033[4m", end="")
                if idx in m:
                    print(Fore.GREEN, end="")
                print(f"{s_copy[idx]}{Style.RESET_ALL}", end=" ")
            print()

            if m and k == 2:
                tag = False
                for j in range(n):
                    if j not in m:
                        print(" " if not tag else f"{Fore.GREEN}_{Style.RESET_ALL}", end=" ")
                        if tag: tag = False
                    else:
                        print(f" ", end=f"{Fore.GREEN}\\{Style.RESET_ALL}")
                        tag = True
                print()
                print(" " * 2, end="")
                for j in range(n):
                    if j not in m:
                        print(" ", end=" ")
                    else:
                        print(f" ", end=f"{Fore.GREEN}\\{Style.RESET_ALL}")
                print()
            if m and k == 1:
                for j in range(n):
                    if j not in m:
                        print(" ", end=" ")
                    else:
                        print(" ", end=f"{Fore.GREEN}\\{Style.RESET_ALL}")
                print()

            if i == n - 1 and m:
                print(*s)
        print()

shell_sort("КУРАПОВА")