def count_sets_dp(arr, total):
    mem = {}
    return dp(arr, total, len(arr) - 1, mem)


def dp(arr, total, i, mem):
    key = str(total) + ':' + str(i)
    if key in mem:
        return mem[key]
    if total == 0:
        return 1
    if total < 0:
        return 0
    if i < 0:
        return 0
    if total < arr[i]:
        return_value = dp(arr, total, i - 1, mem)
    else:
        return_value = dp(arr, total - arr[i], i - 1, mem) + dp(arr, total, i - 1, mem)
    mem[key] = return_value
    return return_value
