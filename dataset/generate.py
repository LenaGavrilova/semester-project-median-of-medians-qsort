import subprocess
import sys
import os

DATASETS_SIZES = [100, 500, 1000, 5000, 10_000, 50_000, 100_000, 500_000, 1_000_000]
DATASETS_NAMES = ["01", "02", "03", "04", "05"]
OPERATIONS_NAMES = ["Sort"]


def make_directories(name):
    try:
        os.mkdir("data/{}".format(name))
        for i in DATASETS_NAMES:
            os.mkdir("data/{}/{}".format(name, i))
    except FileExistsError:
        print("delete old dataset before using our")


if __name__ == "__main__":
    for i in OPERATIONS_NAMES:
        make_directories(i)

    for method in OPERATIONS_NAMES:
        for dataset_name in DATASETS_NAMES:
            for dataset_size in DATASETS_SIZES:
                subprocess.Popen([sys.executable, "generate_csv_dataset.py",
                                  "data/{}/{}/{}.csv".format(method, dataset_name, dataset_size),
                                  "--samples", "{}".format(dataset_size)])
