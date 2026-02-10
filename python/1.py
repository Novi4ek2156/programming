def f(x, l=[]):
    l.append(x)

    return l


print(f(3))

print(f(4, [5]))