import numpy as np
import random
import time
import pandas as pd
import matplotlib as plt


def job_gen(time_len, max_weight, job_size):
    job_array = np.empty((0, 3), int)
    for x in range(job_size):
        start_time = random.randint(2, time_len - 1)
        end_time = random.randint(start_time + 1, time_len)
        weight = random.randint(1, max_weight)
        temp_array = np.array([[start_time, end_time, weight]])
        job_array = np.append(job_array, temp_array, axis=0)
    return job_array


def interval_scheduler(job_sequence):
    job_sequence = job_sequence[job_sequence[:, 0].argsort()]
    weight_sequence = np.zeros(len(job_sequence))
    component_sequence = np.zeros(len(job_sequence))
    index = 0

    for item in job_sequence:
        weight_sequence[index] = job_sequence[index][2]
        index += 1
    # print("The sorted task array is:")
    # print(job_sequence)
    for i in range(1, len(job_sequence)):
        for j in range(1, i):
            if job_sequence[j][1] <= job_sequence[i][0]:
                if weight_sequence[j] + job_sequence[i][2] >= weight_sequence[i]:
                    weight_sequence[i] = weight_sequence[j] + job_sequence[i][2]
                    component_sequence[i] = j + 1

    print("The max value is " + str(weight_sequence[np.argmax(weight_sequence)]))
    print("The best solution is: ", end="")

    while True:
        print(job_sequence[index - 1], end=" ")
        if component_sequence[index - 1] != 0:
            index = int(component_sequence[index - 1])
        else:
            break


if __name__ == "__main__":
    df = pd.DataFrame()
    for i in range(100, 2000):
        job = job_gen(2 * i, i, i)
        tic = time.time()
        interval_scheduler(job)
        toc = time.time()
        twb = toc - tic
        print("\nThe time is: " + str(twb))
        aux_array = pd.DataFrame([[i, twb]])
        df = df.append(aux_array)
        print("i range :"+str(i))
    print(df)
    df.to_csv("test.csv")
    # df = pd.read_csv("test.csv",index_col=False)
    # print(df)
    # plt1 = df.plot(x=0,y=1)
    # plt1.legend(["Execution time"])
    # plt1.set_xlabel("Data size")
    # plt1.set_ylabel("Time (s)")
