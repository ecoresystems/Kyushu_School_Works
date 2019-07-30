def count_sets(arr, total):
    return rec(arr, total, len(arr) - 1)


def rec(arr, total, i):
    if total == 0:
        return 1
    if total < 0:
        return 0
    if i < 0:
        return 0
    if total < arr[i]:
        return rec(arr, total, i - 1)
    else:
        return rec(arr, total - arr[i], i - 1) + rec(arr, total, i - 1)
