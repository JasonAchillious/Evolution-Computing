import pandas as pd


def write2csv(path, result: dict):
    df = pd.DataFrame(result)
    df.to_csv(index=False)
