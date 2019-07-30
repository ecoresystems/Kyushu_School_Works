from utilities import collection_generator
from algorithms import dynamic_programming, brutal_force
import time
import numpy as np
import csv

if __name__ == "__main__":
    res_list = []
    for collection_size in range(1, 20):
        dict = {}
        subset_count = 0
        print("Collection size now is %d" % collection_size)
        number_range = collection_size * 4
        sub_sum = np.random.randint((1 + collection_size * 4) * collection_size * 4 / 2)
        collection = collection_generator.generate(number_range, collection_size)
        DP_toc = time.time()
        subset_count = dynamic_programming.count_sets_dp(collection, sub_sum)
        print("%d subsets found by dynamic programming" % subset_count)
        DP_tic = time.time()
        DP_time = DP_tic - DP_toc
        print("Execution time is %f seconds" % DP_time)

        BT_toc = time.time()
        print("%d subsets found by brutal force" % brutal_force.count_sets(collection, sub_sum))
        BT_tic = time.time()
        BT_time = BT_tic - BT_toc
        print("Execution time is %f seconds" % BT_time)
        dict['collection_size'] = collection_size
        dict['value_range'] = number_range
        dict['sub_sum'] = sub_sum
        dict['subset_count'] = subset_count
        dict['dp_time'] = DP_time
        dict['brutal_time'] = BT_time
        res_list.append(dict)
    print(res_list)
    keys = res_list[0].keys()
    with open('testfilex.csv', 'w', newline='') as f:
        writer = csv.DictWriter(f, keys)
        writer.writeheader()
        writer.writerows(res_list)
