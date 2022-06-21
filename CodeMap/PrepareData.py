import time


def CollectData(read_fn: str, write_fn: str, code_idx: str, mode: str) -> int:
    '''
    快速查看 10档行情数据
    read_fn:  需要读取的文件
    write_fn: 写出的文件
    code:     股票名称
    code_idx: 股票所在位置
    '''
    code_idx = 8
    time_st = time.time()
    lines = []
    count = 0
    with open(read_fn, "r") as f:
        line = f.readline()
        if len(line) > 0 and line[0].isalpha():
            line = f.readline()
        # 识别分隔符
        sep = '\t'
        if line.find(',') >= 0:
            sep = ','
        datestr = line[:8]
        print("{} set {} sep={}".format(datestr, read_fn, sep))
        # 逐行读取文件
        while len(line) > 0:
            count += 1
            words = line.split(sep)
            if len(words) < code_idx:
                print(line)
            else:
                lines.append(words[code_idx] + '\n')
            line = f.readline()
    # 写出数据
    with open(write_fn, mode) as f:
        f.writelines(lines)
    print("read {} lines; write {} lines to {} used:{:.3f}s.".format(count, len(lines), write_fn, time.time() - time_st))
    return count


def main():
    '''
    准备测试数据
    '''
    data_dir = "/home/wiz/data/L2_data/temp"
    order_fn = "{}/am_hq_order_spot.txt".format(data_dir)
    trade_fn = "{}/am_hq_trade_spot.txt".format(data_dir)
    write_fn = "codelist.txt"
    code_idx = 8
    num = CollectData(order_fn, write_fn, code_idx, mode="w")
    num += CollectData(trade_fn, write_fn, code_idx, mode="a")
    print("collect {} data".format(num))


if __name__ == "__main__":
    main()
